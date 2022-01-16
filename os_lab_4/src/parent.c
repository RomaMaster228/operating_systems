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

// files for mapping
char* file1_name = "file1_mapped";

// empty string as a signal
char empty = 1;
char* empty_string = &empty;

char* get_string() {
    int len = 0, capacity = 10;
    char* s = (char*)malloc(10 * sizeof(char));
    if (s == NULL) {
        perror("Can't read a string");
        exit(6);
    }

    char c;
    read(0, &c, sizeof(char));
    while (c != '\n') {
        s[len++] = c;
        if (c == EOF) {
            break;
        }
        if (len == capacity) {
            capacity *= 2;
            s = (char*)realloc(s, capacity * sizeof(char));
            if (s == NULL) {
                perror("Can't read a string");
                exit(6);
            }
        }
        read(0, &c, sizeof(char));
    };
    s[len] = '\0';
    return s;
}


int main() {
        // create a file for mapping
        int fd1 = open(file1_name, O_RDWR | O_CREAT, S_IWRITE | S_IREAD);
        if (fd1 < 0) {
                perror("Can't open file");
                return -1;
        }
        // we should write smth to the file
        if (write(fd1, empty_string, sizeof(empty_string)) < 0) {
                perror("Can't write to file");
                return -1;
        }
        char* file1 = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
        if (file1 == MAP_FAILED) {
                perror("Can't map a file");
                return -1;
        }
        pid_t pid1 = fork();
        if (pid1 == -1) {
                perror("Child 1 wasn't created");
                return -1;
        }
        if (pid1 == 0) { // child 1
                execl("child1", "child1", NULL);
                perror("Can't execute child process");
        }
        else {
                pid_t pid2 = fork();
                if (pid2 == -1) {
                        perror("Child 2 wasn't created");
                        return -1;
                }
                if (pid2 == 0) { //child 2
                        execl("child2", "child2", NULL);
                }
                else { // parent
                        int n;
                        //read(0, &n, sizeof(int));
                        char* str = get_string();
                        n = strlen(str);
                        strcpy(file1, str);
                        int status;
                        if (wait(&status) == -1){
                                perror("wait");
                        }
                        if (wait(&status) == -1){
                                perror("wait");
                        }
                        if (!WIFEXITED(status) || (WIFEXITED(status) && WEXITSTATUS(status) != 0)) {
                                perror("Error in children");
                        }
                        // while (strcmp(file1, empty_string) != 0) {}
                        char* string = (char*)malloc(n * sizeof(char));
                        strcpy(string, file1);
                        printf("%s\n", string);
                        free(string);
                        if (munmap(file1, MAP_SIZE) < 0) {
                                perror("Can't unmap files");
                                return -1;
                        }
                        if (close(fd1) < 0) {
                                perror("Can't close files");
                                return -1;
                        }
                        if (remove(file1_name) < 0) {
                                perror("Can't delete files");
                                return -1;
                        }
                }
        }
        return 0;
}