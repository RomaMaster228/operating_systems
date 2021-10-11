#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ctype.h" //to_lower
#include "string.h"
#include "unistd.h"

int main() {
        int n;
        read(0, &n, sizeof(int));
        // printf("%d", n);
        write(1, &n, sizeof(int));
        char str[n + 1];
        read(0, str, sizeof(char) * n);
        for (int i = 0; i < n; ++i) {
                if (str[i] == ' ') {
                        str[i] = '_';
                }
                //fprintf(stderr, "%c\n", str[i]);
        }
        write(1, str, sizeof(char) * n);
        return 0;
}