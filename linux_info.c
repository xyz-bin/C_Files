#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_kernel_version() {
    FILE *file = fopen("/proc/version", "r");
    if (file == NULL) {
        perror("Failed to open /proc/version");
        return;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file)) {
        printf("Kernel Version: %s\n", buffer);
    }

    fclose(file);
}

void display_uptime() {
    FILE *file = fopen("/proc/uptime", "r");
    if (file == NULL) {
        perror("Failed to open /proc/uptime");
        return;
    }

    double uptime;
    if (fscanf(file, "%lf", &uptime) == 1) {
        int hours = (int)uptime / 3600;
        int minutes = ((int)uptime % 3600) / 60;
        int seconds = (int)uptime % 60;
        printf("Uptime: %d hours, %d minutes, %d seconds\n", hours, minutes, seconds);
    }

    fclose(file);
}

void display_cpu_info() {
    FILE *file = fopen("/proc/cpuinfo", "r");
    if (file == NULL) {
        perror("Failed to open /proc/cpuinfo");
        return;
    }

    char buffer[256];
    int model_name_printed = 0;
    int cpu_cores_printed = 0;
    printf("CPU Information:\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        if (!model_name_printed && strncmp(buffer, "model name", 10) == 0) {
            printf("%s", buffer);
            model_name_printed = 1;
        }
        if (!cpu_cores_printed && strncmp(buffer, "cpu cores", 9) == 0) {
            printf("%s", buffer);
            cpu_cores_printed = 1;
        }

        if (model_name_printed && cpu_cores_printed) {
            break; // Exit early after printing the necessary information
        }
    }

    fclose(file);
}

void display_memory_info() {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Failed to open /proc/meminfo");
        return;
    }

    char buffer[256];
    printf("Memory Information:\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "MemTotal", 8) == 0 || strncmp(buffer, "MemFree", 7) == 0) {
            printf("%s", buffer);
        }
    }

    fclose(file);
}

int main() {
    printf("System Information:\n");
    printf("===================\n");

    display_kernel_version();
    printf("\n");

    display_uptime();
    printf("\n");

    display_cpu_info();
    printf("\n");

    display_memory_info();

    return 0;
}
