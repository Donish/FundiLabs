#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

enum ERRORS{
    CORRECT = 0,
    NO_MEMORY = -1,
    WRONG_DOUBLE = -2,
    WRONG_BASE = -3
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
} frac_repres;

void make_simple_frac(fraction *res, double num, double eps)
{
    res->denominator = 1;
    while((num * res->denominator - floor(num * res->denominator)) > eps){
        res->denominator *= 10;
    }
    res->numerator = num * res->denominator;
}

void frac_reduction(fraction *res, int base)
{
    if(res->denominator % res->numerator == 0){
        res->denominator /= res->numerator;
        res->numerator /= res->numerator;

        while(res->denominator < base){
            res->numerator *= 2;
            res->denominator *= 2;
        }

        return;
    }

    long long int num_cp = res->numerator, denom_cp = res->denominator;
    long long int ostatok = 0;
    long long int nod = 0;
    while(1){
        ostatok = denom_cp % num_cp;
        if(ostatok == 0){
            nod = num_cp;
            break;
        }

        denom_cp = num_cp;
        num_cp = ostatok;
    }

    res->numerator /= nod;
    res->denominator /= nod;

    while(res->denominator < base){
        res->numerator *= 2;
        res->denominator *= 2;
    }
}

int representation_available(frac_repres *res, double eps, int base, int count, ...)
{
    if(base < 2 || base > 36 || base == 10){
        return WRONG_BASE;
    }
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
        if(res->decimal[i] < eps || (res->decimal[i] - 1.0) > eps){
            free(res->decimal);
            free(res->status);
            return WRONG_DOUBLE;
        }
    }

    fraction frac;
    for(int i = 0; i < count; i++){
        make_simple_frac(&frac, res->decimal[i], eps);
        printf("%d/%d\n", frac.numerator, frac.denominator);
        frac_reduction(&frac, base);
        printf("%d/%d\n", frac.numerator, frac.denominator);

        res->status[i] = VALID;
        
        while(frac.denominator > 1){
            if(frac.denominator % base != 0){
                res->status[i] = INVALID;
                break;
            }
            frac.denominator /= base;
        }

    }

    return CORRECT;
}

void print_arrays(frac_repres res, int count, int base)
{
    for(int i = 0; i < count; i++){
        if(res.status[i] == VALID){
            printf("The number %lf has a finite representation in %d notation\n", res.decimal[i], base);
        } else if(res.status[i] == INVALID){
            printf("The number %lf doesn't have a finite representation in %d notation\n", res.decimal[i], base);
        }
    }
}

int main()
{
    int flag = CORRECT;
    frac_repres res;
    double eps = 0.0000001;
    int base = 8, count = 2;
    flag = representation_available(&res, eps, base, count, (double)0.5, (double)0.125);
    if(flag == WRONG_BASE){
        printf("Enter the base between 2 and 36 except 10!\n");
        return WRONG_BASE;
    } else if(flag == WRONG_DOUBLE){
        printf("Enter the numbers from segment (0;1)!\n");
        return WRONG_DOUBLE;
    } else if(flag == NO_MEMORY){
        printf("Memory wasn't allocated!\n");
        return NO_MEMORY;
    }

    print_arrays(res, count, base);

    return 0;
}
