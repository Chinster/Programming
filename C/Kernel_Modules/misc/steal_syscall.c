/* Replace kernel open syscall in sys_call_table with my own. Unfortunately
 * does not work on most kernels since sys_call_table is no longer exported.
 */
#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <asm/uaccess.h>

extern void *sys_call_table[];

asmlinkage int (*original_call) (const char *, int, int);

static int uid;
module_param(uid, int, 0644);

/* Replace sys_open with this function. Prints a message of things root opens.
 */
asmlinkage int my_sys_open(const char *filename, int flags, int mode)
{
    int i = 0;
    char ch;

    if (uid == current->cred->uid.val) {
        printk("Opened file by %d: ", uid);
        do {
            get_user(ch, filename + i);
            i++;
            printk(KERN_ALERT "%c", ch);
        } while (ch != 0);
        printk(KERN_ALERT "\n");
    }

    return original_call(filename, flags, mode);
}

static int __init steal_init(void)
{
    original_call = sys_call_table[__NR_open];
    sys_call_table[__NR_open] = my_sys_open;

    return 0;
}

static void __exit steal_exit(void)
{
    if (sys_call_table[__NR_open] != my_sys_open) {
        printk(KERN_ALERT "Somebody else played with the open sys call\n"
                          "The system may be left in an unstable state.\n");
    }

    sys_call_table[__NR_open] = original_call;
}

module_init(steal_init);
module_exit(steal_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christopher Chin");
MODULE_DESCRIPTION("Prints hello world");
