#include <linux/module.h>

int init_module(void)
{
	pr_debug("Hello World!\n");

	return 0;
}

void cleanup_module(void)
{
}
