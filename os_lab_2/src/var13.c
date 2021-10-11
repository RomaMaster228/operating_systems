#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ctype.h" //to_lower
#include "string.h"
#include "unistd.h"

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
        int fd1[2], fd2[2], fd3[2];
        pipe(fd1);
        pipe(fd2);
        pipe(fd3);
        if (pipe(fd1) < 0 || pipe(fd2) < 0 || pipe(fd3) < 0) {
                perror("Ошибка при создании pipe");
                return -1;
        }
        pid_t pid1 = fork();
        if (pid1 == -1) {
                perror("Ребёнок не был создан");
                return -1;
        }
        if (pid1 == 0) { // child 1
                close(fd1[1]); // we only read this pipe
                close(fd2[0]); // we only write to this pipe
                // close(fd3[0]);
                // close(fd3[1]);
                fflush(stdout);
                // sleep(1.2);
                if (dup2(fd1[0], 0) < 0) {
                        perror("Can't redirect stdin for child process");
                }
                if (dup2(fd2[1], 1) < 0) {
                        perror("Can't redirect stdout for child process");
                }
                execl("child1", "child1", NULL);
                perror("Can't execute child process");
        }
        else {
                pid_t pid2 = fork();
                if (pid2 == -1) {
                        perror("Ребёнок не был создан");
                        return -1;
                }
                if (pid2 == 0) { //child 2
                        //waitpid(pid1, 0, 0);
                        close(fd1[0]);
                        close(fd2[1]); // clean the house after party
                        close(fd3[0]);
                        close(fd1[1]);
                        // waitpid(pid1, 0, 0);
                        // sleep(3);
                        fflush(stdout);
                        if (dup2(fd2[0], 0) < 0) {
                                perror("Can't redirect stdin for child process");
                        }
                        if (dup2(fd3[1], 1) < 0) {
                                perror("Can't redirect stdout for child process");
                        }
                        execl("child2", "child2", NULL);
                }
                else { // parent
                        close(fd2[0]);
                        close(fd3[1]);
                        close(fd2[1]);
                        close(fd1[0]);
                        //fflush(stdout);
                        int n;
                        //read(0, &n, sizeof(int));
                        char* str = get_string();
                        n = strlen(str);
                        //scanf("%s:[^ ]", str);
                        //getline(str, n, stdin);
                        //char* str;
                        //fgets(str, 3, stdin);
                        write(fd1[1], &n, sizeof(int));
                        //n = -1;
                        write(fd1[1], str, sizeof(char) * n);
                        int status;
                        if (wait(&status) == -1){
                                perror("wait");
                        }
                        if (wait(&status) == -1){
                                perror("wait");
                        }
                        if (!WIFEXITED(status) || (WIFEXITED(status) && WEXITSTATUS(status) != 0)) {
                                perror("error in children");
                        }
                        // sleep(0.2);
                        char str_cool[n + 1];
                        read(fd3[0], &n, sizeof(int));
                        read(fd3[0], str_cool, sizeof(char) * n);
                        printf("%d\n", n);
                        //printf("\n");
                        str_cool[n] = '\0';
                        printf("%s\n", str_cool);
                        close(fd3[0]);
                        close(fd1[1]);
                }
        }
        return 0;
}