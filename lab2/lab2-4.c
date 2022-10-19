#include <stdio.h
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

double geom_avg(int size, ...)
{
    double res = 1;
    va_list runner;
    va_start(runner, size);

    for(int i = 0; i < size; i++){
        res *= va_arg(runner, double);
    }

    if(res < 0 && (size % 2 == 0)){
        return NAN;
    }

    va_end(runner);
    return pow(res, 1.0 / size);
}

double rec_pow(double number, int power)
{
    double res = 1;
    if (power > 0){
        res = number * rec_pow(number, power - 1);
    } else if(power < 0){
        res = 1.0 / (number * rec_pow(number, abs(power) - 1));
    }

    return res;
}

int main()
{
    int degree;
    double num, powered;

    double avg = geom_avg(3, (double)5, (double)7, (double)9);
    if(isnan(avg)){
        printf("Wrong numbers!\n");
        return 0;
    } else{
        printf("Geometric mean: %f\n", avg);
    }

    printf("Enter the number and the degree:\n");
    scanf("%lf%d", &num, &degree);
    int copy_deg = degree;
    powered = rec_pow(num, degree);
    printf("Your raised number: %f\n", powered);

    return 0;
}
