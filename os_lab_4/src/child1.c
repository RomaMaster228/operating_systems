#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ctype.h" //to_lower
#include "string.h"
#include "unistd.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAP_SIZE 4096

char empty = 1;
char* empty_string = &empty;

int main() {
        char* file_name = "file1_mapped";
        int fd = open(file_name, O_RDWR | O_CREAT, S_IWRITE | S_IREAD);
        if (fd < 0) {
                perror("Can't open file");
                return -1;
        }
        char* file = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (file == MAP_FAILED) {
                perror("Can't map a file");
                return -1;
        }
        while (strcmp(file, empty_string) == 0) {}
        char* string = (char*)malloc(strlen(file) * sizeof(char));
        strcpy(string, file);
        for (int i = 0; i < strlen(string); ++i) {
                string[i] = tolower(string[i]);
                // fprintf(stderr, "%c\n", str[i]);
        }
        // string[0] = 2;
        strcpy(file, string);
        free(string);
        return 0;
}