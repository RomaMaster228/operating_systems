#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ctype.h" //to_lower
#include "string.h"
#include "unistd.h"

int main() {
        int n;
        scanf("%d", &n);
        fprintf(stdout, "%d\n", n);
        printf("%d", n + 1);
        char str[n + 1];
        /*for (int i = 0; i < n; ++i) {
                scanf("%c", &str[i]);
                str[i] = tolower(str[i]);
                printf("%c", str[i]);
        }*/
        close(0);
        close(1);
        return 0;
}