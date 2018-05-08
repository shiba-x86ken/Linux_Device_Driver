#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>

#define GPIO_SW 5

MODULE_AUTHOR("shibax86ken");
MODULE_LICENSE("GPL");

 int init_module(void) {
    printk(KERN_INFO "ON/\n" );
    gpio_request(GPIO_SW, NULL);
    gpio_direction_input(GPIO_SW, 1);

    return 0;
}


void cleanup_module(void) {
    int val;

    val=gpio_get_value(GPIO_SW, 0);
    printk(KERN_INFO "state:%d\n", val);
    gpio_free(GPIO_SW);
    printk(KERN_INFO "OFF\n");
}
