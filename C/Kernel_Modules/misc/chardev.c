/* Creates a read-only char device that says how many times it has been
 * read.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/version.h>

#include <asm/uaccess.h>

#define DEV_NAME "chardev"    // Name as it appears in /proc/devices
#define BUF_LEN 80
#define DEVICE_CNT 1

static dev_t dev;
static struct class *cl;
static struct cdev c_dev;


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

    printk(KERN_INFO "chardev: registered %d device\n", MAJOR(dev));
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
void cleanup_module(void)
{
    cdev_del(&c_dev);
    device_destroy(cl, dev);
    class_destroy(cl);
    unregister_chrdev_region(dev, DEVICE_CNT);
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
    sprintf(msg, "I already told you %d times chardev world!\n", counter++);
    msg_ptr = msg;
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
 * As in "echo hi > /dev/chardev"
 */
static ssize_t device_write(struct file* file_ptr, const char *buff,
                            size_t len, loff_t *off)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EINVAL;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christopher Chin");
