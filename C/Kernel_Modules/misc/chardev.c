/* Creates a read-only char device that says how many times it has been
 * read.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define SUCCESS 0
#define DEV_NAME "chardev"    // Name as it appears in /proc/devices
#define BUF_LEN 80

static int Major;
static int Device_Open = 0;

static char msg[BUF_LEN];
static char *msg_ptr;


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

/* Called when module is loaded.
 */
int init_module(void)
{
    Major = register_chrdev(0, DEV_NAME, &fops);

    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed: %d\n", Major);
        return Major;
    }

    printk(KERN_INFO "Char-dev assigned major number %d. To talk to "
                     "the driver, create a dev file with\n", Major);
    printk(KERN_INFO "'mknod /dev/%s c %d 0'\n", DEV_NAME, Major);
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to "
                     "the device file.\n Remove the device file "
                     "and module when done.\n");

    return SUCCESS;
}

/* Called when module is unloaded.
 */
void cleanup_module(void)
{
    unregister_chrdev(Major, DEV_NAME);
}

/* Called when a process tries to open the device file.
 * As is "cat /dev/mycharfile"
 */
static int device_open(struct inode *inode, struct file *file)
{
    static int counter = 0;

    if (Device_Open)
        return -EBUSY;

    Device_Open++;
    sprintf(msg, "I already told you %d times Hello world!\n", counter++);
    msg_ptr = msg;
    try_module_get(THIS_MODULE);

    return SUCCESS;
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
    int bytes_read =0;
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
 * As in "echo hi > /dev/hello"
 */
static ssize_t device_write(struct file* file_ptr, const char *buff,
                            size_t len, loff_t *off)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EINVAL;
}
