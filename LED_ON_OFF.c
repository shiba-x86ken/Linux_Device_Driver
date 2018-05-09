#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>

#define GPIO_LED 4

MODULE_AUTHOR("shibax86ken");
MODULE_LICENSE("GPL");

 int init_module(void) {
    printk(KERN_INFO "ON\n");
    gpio_request(GPIO_LED, NULL);
    gpio_direction_output(GPIO_LED, 1);
    gpio_export(GPIO_LED, 1);

    return 0;
}


void cleanup_module(void) {
    gpio_unexport(GPIO_LED);
    gpio_set_value(GPIO_LED, 0);
    gpio_free(GPIO_LED);
    printk(KERN_INFO "OFF\n");
}
