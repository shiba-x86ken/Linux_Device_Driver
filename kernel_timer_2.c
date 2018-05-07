#include<linux/module.h>
#include<linux/timer.h>
#include<linux/jiffies.h>

MODULE_AUTHOR("shiba_x86ken");
MODULE_LICENSE("GPL");

static struct timer_list mytimer;

static void mytimer_callback(unsigned long unused) {
    static int flag = 1;
    flag = 1 - flag;
    printk(KERN_INFO "%d\n",flag,flag);
    mod_timer(&mytimer, jiffies + msecs_to_jiffies(1000));
}

int init_module(void) {
    printk(KERN_INFO "Kernel Timer 1tick = %d usec\n",jiffies_to_usecs(1));
    setup_timer(&mytimer, mytimer_callback, 0);
    mod_timer(&mytimer, jiffies + msecs_to_jiffies(1000));
    
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Bey\n");
    del_timer(&mytimer);
}
