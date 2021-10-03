#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ctype.h" //to_lower
#include "string.h"
#include "unistd.h"

int main() {
        int n;
        scanf("%d", &n);
        printf("%d", n);
        char str[n + 1];
        /*for (int i = 0; i < n; ++i) {
                scanf("%c", &str[i]);
                if (str[i] == '_') {
                        str[i] = '*';
                }
                printf("%c", str[i]);
        }*/
        close(1);
        close(0);
        return 0;
}