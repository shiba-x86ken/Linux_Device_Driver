#include<linux/module.h>

MODULE_AUTHOR("shiba_x86ken");
MODULE_LICENSE("GPL");

int init_module(void) {
    printk(KERN_INFO "Hello\n");
    
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Bye\n");
}
