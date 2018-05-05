#include<linux/slab.h>

MODULE_AUTHOR("shiba_x86ken");
MODULE_LICENSE("GPL");

char* p;

int init_module(void) {
    p=(char *)kmalloc(PAGE_SIZE*130,GFP_KERNEL); // 520KB
    printk(KERN_INFO "Hello %d , [%p]\n", PAGE_SIZE, p);

    return 0;
}

void cleanup_module(void) {
    kfree(p);
    printk(KERN_INFO "Bye\n");
}
