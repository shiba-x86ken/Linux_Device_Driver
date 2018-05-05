#include<linux/module.h>

MODULE_AUTHOR("shiba_x86ken");
MODULE_LICENSE("GPL");

int init_module(void) {
    printk(KERN_INFO "Hello <%lu>\n", jiffies);
    
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Bye <%lu>\n", jiffies);
}
