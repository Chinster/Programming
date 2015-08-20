#include <linux/module.h>

int init_module()
{
    printk("Hello World!\n");

    return 0;
}

void cleanup_module()
{
    return;
}
