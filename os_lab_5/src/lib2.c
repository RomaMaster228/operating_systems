#include <math.h>

// Метод трапеций
float sinintegral(float a, float b, float e) {
    int n = (b - a) / e;
    float integral = 0.0;
    float c = 0.0;
    if (n < 0) {
        n = -n;
    }
    if (a < b) {
        c = a;
    }
    else {
        c = b;
    }
    for (int i = 0; i < n; i++) {
        integral += (sinf(c) + sinf(c + e)) / 2.0 * e;
        c += e;
    }
    return integral;
}


// Площадь прямоугольного треугольника
float square(float a, float b) {
    return 0.5 * a * b;
}