#include <stdio.h
#include <stdlib.h>
#include <math.h>

double eq(double x)
{
    return sin(x) - (sqrt(3) / 2);
}

double dichotomy(double a, double b, double pre)
{
    if(a > b){
        double tmp = a;
        a = b;
        b = tmp;
    }
    if(pre <= 0){
        return NAN;
    }

    double x;
    double eps = pow(10, -pre);
    while (b - a > eps){
        x = (a + b) / 2;
        if(eq(b) * eq(x) < eps){
            a = x;
        } else{
            b = x;
        }
    }
    return x;
}

int main()
{
    double precision;
    printf("Enter the precision:\n");
    scanf("%lf", &precision);

    double res = dichotomy(0, 10, precision);
    if(isnan(res)){
        printf("Enter positive precision!\n");
        return 0;
    }
    printf("The root of equation: %lf\n", res);

    return 0;
}
