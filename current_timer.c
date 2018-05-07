#include<linux/module.h>
#include<linux/time.h>

MODULE_AUTHOR("shiba_x86ken");
MODULE_LICENSE("GPL");

struct timeval t0;

int init_module(void) {
    do_gettimeofday(&t0);
    printk(KERN_INFO "Hello\n");

    return 0;
}

void cleanup_module(void) {
    struct timeval t1;
    long long tmp1, tmp0;

    do_gettimeofday(&t1);

    tmp1=(unsigned long long)(t1.tv_sec) * 1000000 + t1.tv_usec;
    tmp0=(unsigned long long)(t0.tv_sec) * 1000000 + t0.tv_usec;

    printk(KERN_INFO "Bey %lld\n", tmp1 - tmp0);
}
