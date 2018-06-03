/* 1604861 2EP4-27 �������� */
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
// CPU�̉��x���������܂�Ă���V�X�e���t�@�C��PATH
#define CPU_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
// waching_cpu_temp-driver�̃f�o�C�X����PATH
#define CPU_ISSUE_DRIVER "/sys/class/CPU_TEMP/cpu_temp/cpu_issue"

// �g����
void usage() {
    puts("You must setting warning cpu temperature.");
    puts("Usage:");
    puts("      sudo ./warning_cpu_temp value");
    puts("      value is arbitrary number.\n");
    exit(0);
}

// STOP�V�O�i���̃v���g�^�C�v�錾
void proc_stop();

int main(int argc, char const *argv[]) { // �R�}���h���C����������ݒ艷�x���󂯎��
    int cpu_temp_fd, cpu_issue_fd; // �t�@�C���f�B�X�N���v�^
    char cpu_temp_buf[N] = {'\0'}; // cpu�̉��x���i�[����o�b�t�@
    int cpu_temp; // cpu�̉��x���i�[
    int setting_cpu_temp; // �ݒ艷�x
    char temp_buf[N] = {'\0'}; // read()�p�̃o�b�t�@

    // �ݒ艷�x���󂯎��Ȃ���Ύg�p���@��\��
    if (argc < 2) {
        usage();
    }

    setting_cpu_temp = atoi(argv[1]);

    signal(SIGTSTP,proc_stop); // STOP�V�O�i���n���h���̓o�^

    printf("setting success : %d ��\n\n", setting_cpu_temp);
    puts("-*- CPU watcher start -*-");
    puts("\e[41mSTOP : ctrl-Z\e[m\n");

    usleep(5000000); // 5�b�҂�

    while (1) {
        cpu_temp_fd = open(CPU_TEMP_FILE, O_RDONLY);

        read(cpu_temp_fd, cpu_temp_buf, N);
        cpu_temp_buf[strlen(cpu_temp_buf) - 1]='\0';
        cpu_temp = atoi(cpu_temp_buf) / 1000;

            // cpu�̉��x���ݒ艷�x���������Ȃ�����D�D�D
            if (setting_cpu_temp <= cpu_temp) {
                printf("\e[31mWarning!! : %d ��\e[m\n\n", cpu_temp);

                // waching_cpu_temp-driver�̃f�o�C�X������open
                cpu_issue_fd = open(CPU_ISSUE_DRIVER, O_RDONLY);
                    int temp_size = read(cpu_issue_fd, temp_buf, N);
                    close(cpu_issue_fd);
                }else{
                printf("CPU-TEMP : %d ��\n\n", cpu_temp);
                close(cpu_temp_fd);
            }

            close(cpu_temp_fd);
            close(cpu_issue_fd);

            usleep(500000); // 5�b�҂�
        }

    return 0;
}

// ctrl-Z��STOP�V�O�i���𑗐M
void proc_stop() {
  	printf("\n");
    puts("End...\n");

   	exit(0);
}
