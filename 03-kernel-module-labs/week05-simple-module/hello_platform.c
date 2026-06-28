// hello_platform.c

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Hello Platform Kernel Module");
MODULE_VERSION("1.0");

/* Module parameter */
static char* name = "World";
module_param(name, charp, 0644);
MODULE_PARM_DESC(name, "Name to greet");

static int __init hello_platform_init(void) {
    pr_info("hello_platform: Module loaded\n");
    pr_info("hello_platform: Hello, %s!\n", name);
    return 0;
}

static void __exit hello_platform_exit(void) {
    pr_info("hello_platform: Goodbye, %s!\n", name);
    pr_info("hello_platform: Module unloaded\n");
}

module_init(hello_platform_init);
module_exit(hello_platform_exit);
