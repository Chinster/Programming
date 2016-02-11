/* hello_proc - An example usage of procfs.
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h> // For copy_from_user

#define PROCFS_NAME "helloworld"
#define MAX_BUFF 1023

struct proc_dir_entry *proc_file;
static char procfs_buffer[MAX_BUFF + 1];
static unsigned long buff_size = 0;

static int procfile_show(struct seq_file *m, void *v)
{
    seq_printf(m, "%s", procfs_buffer);
    return 0;
}

static int procfile_open(struct inode *inode, struct file *file)
{
    return single_open(file, procfile_show, NULL);
}

static ssize_t procfile_write(struct file *file, const char *buff,
                              size_t len, loff_t *off)
{
    buff_size = len;
    if (buff_size > MAX_BUFF)
        buff_size = MAX_BUFF;

    if (copy_from_user(procfs_buffer, buff, buff_size))
        return -EFAULT;

    procfs_buffer[buff_size] = '\0';
    return buff_size;
}

static struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .open = procfile_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
    .write = procfile_write,
};

int init_module(void)
{
    procfs_buffer[0] = '\0';

    proc_create(PROCFS_NAME, 0666, NULL, &proc_fops);
    printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);
    return 0;
}

void cleanup_module(void)
{
    remove_proc_entry(PROCFS_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}
