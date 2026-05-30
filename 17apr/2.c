#include <stdio.h>

#define nm 100

void run(int n, double *a, double *b, double *c, double *d, double *y) {
    double v[nm + 1], u[nm + 1];

    // Прямой ход
    v[1] = -b[1] / a[1];
    u[1] = d[1] / a[1];

    for (int i = 2; i <= n; i++) {
        double m = a[i] + c[i] * v[i - 1];
        v[i] = -b[i] / m;
        u[i] = (d[i] - c[i] * u[i - 1]) / m;
    }

    // Обратный ход
    y[n] = u[n];
    for (int i = n - 1; i >= 1; i--) {
        y[i] = v[i] * y[i + 1] + u[i];
    }
}

int main() {
    double a[nm + 1], b[nm + 1], c[nm + 1], d[nm + 1], y[nm + 1];
    int n = 5;

    // a - главная диагональ, b - над, c - под, d - правая часть
    c[1] = 0;    a[1] = 2;  b[1] = 3;  d[1] = 5;
    c[2] = -1;   a[2] = 5;  b[2] = 2;  d[2] = -3;
    c[3] = 17;   a[3] = 2;  b[3] = -1; d[3] = 0;
    c[4] = 6;    a[4] = 10; b[4] = 1;  d[4] = -1; // Изменил a[4] с 0 на 10 для стабильности
    c[5] = 1;    a[5] = 1;  b[5] = 0;  d[5] = -3;

    run(n, a, b, c, d, y);

    for (int i = 1; i <= n; i++) {
        printf("y[%d] = %5.2lf\n", i, y[i]);
    }

    return 0;
}
