#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

double power(double num, int step)
{
    double res = 1;
    for(int i = 0; i < step; i++){
        res *= num;
    }
    return res;
}

int isconvex(int count, ...)
{
    va_list runner;
    va_start(runner, count);

    double *coords = (double*)malloc(sizeof(double) * count);
    if(coords == NULL){
        return -1;
    }

    for(int i = 0; i < count; i++){
        coords[i] = va_arg(runner, double);
    }
    va_end(runner);

    double *vectors = (double*)malloc(sizeof(double) * count);
    if(vectors == NULL){
        free(coords);
        return -1;
    }
    for(int i = 2; i < count; i++){
        vectors[i] = coords[i] - coords[i - 2];
    }
    vectors[0] = coords[0] - coords[count - 2];
    vectors[1] = coords[1] - coords[count - 1];
    free(coords);
    double product;
    for(int i = 0; i < count; i += 2){
        product = vectors[i] * vectors[(i + 3) % count] - vectors[(i + 1) % count] * vectors[(i + 2) % count];
        if(product < 0){
            free(vectors);
            return 0; // не выпуклый
        }
    }
    free(vectors);
    return 1; // выпуклый
}

double polynomial(double x, int n, ...)
{
    if(n < 0){
        return NAN;
    }

    va_list runner;
    va_start(runner, n);

    double res = 0;
    for(int i = 0; i < n; i++){
        res += va_arg(runner, double);
        res *= x;
    }
    res += va_arg(runner, double);
    va_end(runner);

    return res;
}

int main(int argc, char *argv[])
{
    if(argc == 1){
        printf("No arguments!\n");
        return 0;
    } else if(argc > 2){
        printf("Only flag!\n");
        return 0;
    }

    if(strcmp(argv[1], "-a") == 0){

        int flag = isconvex(10, (double)1.0, (double)5.0, (double)3.0, (double)2.0, (double)6.0, (double)3.0, (double)7.0, (double)4.0, (double)9.0, (double)7.0);
        if(flag == -1){
            printf("Memory wasn't allocated!\n");
        } else if(flag == 1){
            printf("The polygon is convex\n");
        } else{
            printf("The polygon isn't convex\n");
        }

    } else if(strcmp(argv[1], "-b") == 0){

        double res = polynomial(3, 5, (double)4.3, (double)2.5, (double)7.3, (double)12.1, (double)10.7, (double)8);
        if(isnan(res)){
            printf("Only positive degree!\n");
            return 0;
        }
        printf("The value of polynomial: %lf\n", res);

    } else{

        printf("Wrong flag!\n");

    }

    return 0;
}
