#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    int fd;
    int n = 10;

    fd = open("/sys/class/gpio/gpio4/value", O_RDWR);
    
    while(n--){
        write(fd,"1",1);
        lseek(fd, SEEK_SET, 0);
        printf("Hello\n");
        sleep(1);
        write(fd,"0",1);
        lseek(fd, SEEK_SET, 0);
        printf("Bye\n");
        sleep(1);
    }

    close(fd);

    return 0;
}
