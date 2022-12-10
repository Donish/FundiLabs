#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

enum ERRORS{
    CORRECT = 0,
    NO_MEMORY = -1
};

enum REPRESENTATION{
    VALID = 1,
    INVALID = 2
};

typedef struct{
    long long int numerator;
    long long int denominator;
} fraction;

typedef struct{
    int *status; //1 - memory trouble
    double *decimal; //десятичные дроби
} arrays;

void make_simple_frac(fraction *res, double num, double eps)
{
    res->denominator = 1;
    while((num * res->denominator - floor(num * res->denominator)) > eps){
        res->denominator *= 10;
    }
    res->numerator = num * res->denominator;
}

int maketask(arrays *res, double eps, int base, int count, ...)
{
    va_list runner;
    va_start(runner, count);

    res->decimal = (double*)malloc(sizeof(double) * count);
    if(res->decimal == NULL){
        return NO_MEMORY;
    }

    res->status = (int*)malloc(sizeof(int) * count);
    if(res->status == NULL){
        free(res->decimal);
        return NO_MEMORY;
    }

    for(int i = 0; i < count; i++){
        res->decimal[i] = va_arg(runner, double);
    }

    fraction frac;
    for(int i = 0; i < count; i++){
        make_simple_frac(&frac, res->decimal[i], eps);
        // printf("%d/%d\n", frac.numerator, frac.denominator);
        
    }
    


}

int main()
{
    int flag = CORRECT;
    arrays res;
    double eps = 0.0000001;
    flag = maketask(&res, eps, 2, 2, (double)0.12345678, (double)0.12);
    

    return 0;
}