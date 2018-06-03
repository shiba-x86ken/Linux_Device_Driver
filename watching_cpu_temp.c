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
// CPUの温度が書き込まれているシステムファイルPATH
#define CPU_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
// waching_cpu_temp-driverのデバイス属性PATH
#define CPU_ISSUE_DRIVER "/sys/class/CPU_TEMP/cpu_temp/cpu_issue"

// 使い方
void usage() {
    puts("You must setting warning cpu temperature.");
    puts("Usage:");
    puts("      sudo ./warning_cpu_temp value");
    puts("      value is arbitrary number.\n");
    exit(0);
}

// STOPシグナルのプロトタイプ宣言
void proc_stop();

int main(int argc, char const *argv[]) { // コマンドライン引数から設定温度を受け取る
    int cpu_temp_fd, cpu_issue_fd; // ファイルディスクリプタ
    char cpu_temp_buf[N] = {'\0'}; // cpuの温度を格納するバッファ
    int cpu_temp; // cpuの温度を格納
    int setting_cpu_temp; // 設定温度
    char temp_buf[N] = {'\0'}; // read()用のバッファ

    // 設定温度を受け取れなければ使用方法を表示
    if (argc < 2) {
        usage();
    }

    setting_cpu_temp = atoi(argv[1]);

    signal(SIGTSTP,proc_stop); // STOPシグナルハンドラの登録

    printf("setting success : %d ℃\n\n", setting_cpu_temp);
    puts("-*- CPU watcher start -*-");
    puts("\e[41mSTOP : ctrl-Z\e[m\n");

    usleep(5000000); // 5秒待つ

    while (1) {
        cpu_temp_fd = open(CPU_TEMP_FILE, O_RDONLY);

        read(cpu_temp_fd, cpu_temp_buf, N);
        cpu_temp_buf[strlen(cpu_temp_buf) - 1]='\0';
        cpu_temp = atoi(cpu_temp_buf) / 1000;

            // cpuの温度が設定温度よりも高くなったら．．．
            if (setting_cpu_temp <= cpu_temp) {
                printf("\e[31mWarning!! : %d ℃\e[m\n\n", cpu_temp);

                // waching_cpu_temp-driverのデバイス属性をopen
                cpu_issue_fd = open(CPU_ISSUE_DRIVER, O_RDONLY);
                    int temp_size = read(cpu_issue_fd, temp_buf, N);
                    close(cpu_issue_fd);
                }else{
                printf("CPU-TEMP : %d ℃\n\n", cpu_temp);
                close(cpu_temp_fd);
            }

            close(cpu_temp_fd);
            close(cpu_issue_fd);

            usleep(500000); // 5秒待つ
        }

    return 0;
}

// ctrl-ZでSTOPシグナルを送信
void proc_stop() {
  	printf("\n");
    puts("End...\n");

   	exit(0);
}
