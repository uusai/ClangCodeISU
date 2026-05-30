#include <stdio.h>
#include <math.h>

int main() {
    FILE *fp = fopen("graph.dat", "w");
    if (fp == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    double start = 0.0;
    double end = 10.0;
    double step = 0.1;

    // Запись данных в файл
    for (double x = start; x <= end; x += step) {
        double y = sin(x); // Функция: sin(x)
        fprintf(fp, "%lf %lf\n", x, y);
    }

    fclose(fp);
    printf("Файл graph.dat успешно создан с точками функции sin(x).\n");

    return 0;
}
