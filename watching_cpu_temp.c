/* 1604861 2EP4-27 Äú±¤è */
// coding:shift JIS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <errno.h>

#define N 100
// CPUÌ·xª«ÜêÄ¢éVXet@CPATH
#define CPU_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
// waching_cpu_temp-driverÌfoCX®«PATH
#define CPU_ISSUE_DRIVER "/sys/class/CPU_TEMP/cpu_temp/cpu_issue"

// g¢û
void usage() {
    puts("You must setting warning cpu temperature.");
    puts("Usage:");
    puts("      sudo ./warning_cpu_temp value");
    puts("      value is arbitrary number.\n");
    exit(0);
}

// STOPVOiÌvg^Cvé¾
void proc_stop();

int main(int argc, char const *argv[]) { // R}hCø©çÝè·xðó¯æé
    int cpu_temp_fd, cpu_issue_fd; // t@CfBXNv^
    char cpu_temp_buf[N] = {'\0'}; // cpuÌ·xði[·éobt@
    int cpu_temp; // cpuÌ·xði[
    int setting_cpu_temp; // Ýè·x
    char temp_buf[N] = {'\0'}; // read()pÌobt@

    // Ýè·xðó¯æêÈ¯êÎgpû@ð\¦
    if (argc < 2) {
        usage();
    }

    setting_cpu_temp = atoi(argv[1]);

    signal(SIGTSTP,proc_stop); // STOPVOinhÌo^

    printf("setting success : %d \n\n", setting_cpu_temp);
    puts("-*- CPU watcher start -*-");
    puts("\e[41mSTOP : ctrl-Z\e[m\n");

    usleep(5000000); // 5bÒÂ

    while (1) {
        cpu_temp_fd = open(CPU_TEMP_FILE, O_RDONLY);

        read(cpu_temp_fd, cpu_temp_buf, N);
        cpu_temp_buf[strlen(cpu_temp_buf) - 1]='\0';
        cpu_temp = atoi(cpu_temp_buf) / 1000;

            // cpuÌ·xªÝè·xæèà­ÈÁ½çDDD
            if (setting_cpu_temp <= cpu_temp) {
                printf("\e[31mWarning!! : %d \e[m\n\n", cpu_temp);

                // waching_cpu_temp-driverÌfoCX®«ðopen
                cpu_issue_fd = open(CPU_ISSUE_DRIVER, O_RDONLY);
                    int temp_size = read(cpu_issue_fd, temp_buf, N);
                    close(cpu_issue_fd);
                }else{
                printf("CPU-TEMP : %d \n\n", cpu_temp);
                close(cpu_temp_fd);
            }

            close(cpu_temp_fd);
            close(cpu_issue_fd);

            usleep(500000); // 5bÒÂ
        }

    return 0;
}

// ctrl-ZÅSTOPVOiðM
void proc_stop() {
  	printf("\n");
    puts("End...\n");

   	exit(0);
}
