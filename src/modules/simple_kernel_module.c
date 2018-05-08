#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* This function is called when the module is loaded. */

int simple_init(void)
{
	printk(KERN_INFO "Loading module");
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	printk(KERN_INFO "Removing module");
}

/* Macros for registering module entry and exit points */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple kernel module");
MODULE_AUTHOR("Akshay");