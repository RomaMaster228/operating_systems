#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define LIBNAME_FIRST "lib1.so"
#define LIBNAME_SECOND "lib2.so"

int main() {
    float (*sinintegral) (float, float, float) = NULL;
    float (*square) (float, float) = NULL;
    void *handle1 = dlopen(LIBNAME_FIRST, RTLD_LAZY);
    if (!handle1) {
        printf("%s\n", dlerror());
        exit(1);
    }
    void *handle2 = dlopen(LIBNAME_SECOND, RTLD_LAZY);
    if (!handle2) {
        printf("%s\n", dlerror());
        exit(2);
    }
    int lib = 1;
    int cmd = 0;
    float A = 0.0, B = 0.0, step = 0.0;
    float a = 0.0, b = 0.0;
    char *error;
    printf("1 a b c --> count integral of sin(x) on [a, b] with step c\n");
    printf("2 a b --> the square of a flat figure\n");
    while (scanf("%d", &cmd) != EOF) {
        switch(cmd) {
        case 0:
            lib = (lib == 1) ? 2 : 1;
            printf("Library was changed to %d \n", lib);
            break;
        case 1:
            if (lib == 1) {
                sinintegral = dlsym(handle1, "sinintegral");
            }
            else {
                sinintegral = dlsym(handle2, "sinintegral");
            }

            if ((error = dlerror()) != NULL) {
                printf("Dlsym error\n");
                exit(3);
            }

            scanf("%f%f%f", &A, &B, &step);
            printf("Result: %f\n", sinintegral(A, B, step));
            break;
        case 2:
            if (lib == 1) {
                square = dlsym(handle1, "square");
            }
            else {
                square = dlsym(handle2, "square");
            }

            if ((error = dlerror()) != NULL) {
                printf("Dlsym error\n");
                exit(4);
            }
            scanf("%f %f", &a, &b);
            printf("Result: %f\n", square(a, b));
            break;
        }
    }

    if (dlclose(handle1) != 0) {
        perror("Dlclose error");
        exit(5);
    }
    if (dlclose(handle2) != 0) {
        perror("Dlclose error");
        exit(6);
    }

    return 0;
}