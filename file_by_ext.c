#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#define MAX_PATH 1024

void create_directory(const char *dir_name) {
    struct stat st = {0};
    if (stat(dir_name, &st) == -1) {
        if (mkdir(dir_name, 0755) != 0) {
            perror("mkdir");
            exit(EXIT_FAILURE);
        }
    }
}

void move_file(const char *file_name, const char *extension) {
    char new_dir[MAX_PATH];
    snprintf(new_dir, sizeof(new_dir), "%s_files", extension);
    create_directory(new_dir);

    char new_path[MAX_PATH];
    snprintf(new_path, sizeof(new_path), "%s/%s", new_dir, file_name);

    if (rename(file_name, new_path) != 0) {
        perror("rename");
    }
}

void organize_files() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                char *ext = strrchr(dir->d_name, '.');
                if (ext) {
                    ext++;
                    move_file(dir->d_name, ext);
                }
            }
        }
        closedir(d);
    } else {
        perror("opendir");
    }
}

int main() {
    organize_files();
    return 0;
}
