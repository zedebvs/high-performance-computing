#include <cmath>
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <omp.h>

double f(int x) {
    double chisl = 7 * pow(x, 12) + 2 * pow(x, 11) + 18 * pow(x, 10) + 121;
    double znamenatel = 2 * pow(x, 13) + 3 * pow(x, 7) + 5 * pow(x, 3) + 7;

    return chisl / znamenatel;
}

double one_theard(int n) {

    double S = 0;

    for (int i = 1; i <= n; i++) {
        S = S + f(i);
    }

    return S;
}

double multi(int n) {

    double S = 0;

    #pragma omp parallel for reduction(+:S)
    for (int i = 1; i <= n; i++) {
        S = S + f(i);
    }
    return S;
 }

void main() {
    setlocale(LC_ALL, "Russian");
    
    //int S = 0;
    int n = 0;

    printf_s("Введите количество итераций: ");
    scanf_s("%d", &n);

    double start = omp_get_wtime();
    double one = one_theard(n);
    double end = omp_get_wtime();
    double time_single = end - start;

    printf_s("Результат суммы ряда в однопотоке: %f\nЗа %f милисекунд\n", one, time_single);

    start = omp_get_wtime();
    double multi_ = multi(n);
    end = omp_get_wtime();
    double time_multi = end - start;

    printf_s("Результат суммы ряда в многопотоке: %f\nЗа %f милисекунд\n", multi_, time_multi);

    if (time_multi > 0) {
        printf("Ускорение в: %.2f раз(а)\n", time_single / time_multi);
    }
}