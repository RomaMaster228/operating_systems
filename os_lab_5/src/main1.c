#include <stdio.h>
#include "libs.h"

int main() {
    int cmd = 0;
    float A = 0.0, B = 0.0, step = 0.0;
    float a = 0.0, b = 0.0;
    printf("1 a b c --> count integral of sin(x) on [a, b] with step c\n");
    printf("2 a b --> the square of a flat figure\n");
    while (scanf("%d", &cmd) != EOF) {
        switch(cmd) {
        case 0:
            printf("This is not program 2\n");
            break;
        case 1:
            scanf("%f%f%f", &A, &B, &step);
            printf("Result: %f\n", sinintegral(A, B, step));
            break;
        case 2:
            scanf("%f%f", &a, &b);
            printf("Result: %f\n", square(a, b));
            break;
        }
    }
    return 0;
}