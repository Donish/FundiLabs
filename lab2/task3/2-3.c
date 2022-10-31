#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define M_PI 3.14159265358979323846

double epsilon(int pre)
{
    if(pre <= 0){
        return NAN;
    }
    return pow(10, -pre);
}

double factorial(double n)
{
    double res = 1;
    if(n < 2){
        return 1.0;
    }
    for(double i = 1; i <= n; i++){
        res *= i;
    }
    return res;
}

double combination(int m, int k)
{
    double res;
    double numerator = 1.0;
    for(double i = k + 1.0; i <= m; i++){
        numerator *= i;
    }
    double denominator = factorial(m - k);
    res = numerator / denominator;
    return res;
    //return factorial(m) / (factorial(k) * factorial(m - k));
}

int isprime(int num)
{
    if(num > 1){
        for(int i = 2; i <= sqrt(num); i++){
            if(num % i == 0){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

double dichotomy(double F(double),double a, double b, double eps)
{
    if(a > b){
        double tmp = a;
        a = b;
        b = tmp;
    }

    double x;
    while (b - a > eps){
        x = (a + b) / 2;
        if(F(b) * F(x) < eps){
            a = x;
        } else{
            b = x;
        }
    }
    return x;
}

//e
double e_lim(double eps)
{
    double res = 1.0;
    double prev = 0.0;
    //double power = 1.0;
    for(double n = 1;; n++){
        prev = res;
        res = pow(1.0 + (1.0 / n), n);
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return res;
}

double e_row(double eps)//done
{
    double res = 0;
    double prev = 0.0;
    double fact = 1.0;
    for(double n = 1;; n++){
        res += 1.0 / fact;
        fact *= n;
        if(fabs(res - prev) < eps){
            break;
        }
        prev = res;
    }
    return res;
}

double e_eq(double x)
{
    return log(x) - 1;
}

//pi
double pi_lim(double eps)//done
{
    double res = 4.0;
    double prev = 0;
    for(double n = 1;; n++){
        prev = res;
        res *= (4 * n * (n + 1)) / ((4 * n * (n + 1)) + 1);
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return res;
}

double pi_row(double eps) //done
{
    double res = 0;
    double prev = 0;
    for(int n = 1;; n++){
        prev = res;
        if((n - 1) % 2 == 0){
            res += 1.0 / (2.0 * n - 1.0);
        } else{
            res += -1.0 / (2.0 * n - 1.0);
        }
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return 4 * res;
}

double pi_eq(double x)
{
    return sin(x);
}

//ln2
double ln2_lim(double eps)
{
    double res = 0;
    double prev = 0;
    for(double n = 1;; n++){
        prev = res;
        res = n * (pow(2, 1 / n) - 1);
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return res;
}

double ln2_row(double eps)//done
{
    double res = 0;
    double prev = 0;
    for(int n = 1;; n++){
        prev = res;
        if((n - 1) % 2 == 0){
            res += 1.0 / n;
        } else{
            res += -1.0 / n;
        }
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return res;
}

double ln2_eq(double x)
{
    return exp(x) - 2;
}

//sqrt2
double sqrt2_lim(double eps)//done
{
    double res = 0;
    double prev = -0.5;
    for(int n = 1;; n++){
        res = prev - (prev * prev) / 2.0 + 1;
        if(fabs(res - prev) < eps){
            break;
        }
        prev = res;
    }
    return res;
}

double sqrt2_row(double eps)//done
{
    double res = 1.0;
    double prev = 1.0;
    double power = 1.0 / 4.0;
    for(int k = 2;; k++){
        prev = res;
        res *= pow(2, power);
        power *= (1.0 / 2.0);
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return res;
}

double sqrt2_eq(double x)
{
    return pow(x, 2) - 2;
}

//gamma
double gamma_lim(double eps)//done
{
    double res = 0.0;
    double prev = 0.0;
    double fact = 1.0;
    for(int m = 2;; m++){
        prev = res;
        res = 0.0;
        for(int k = 1; k <= m; k++){
            fact *= k;
            if(k % 2 == 0){
                res += combination(m, k) * log(fact) / k;
            } else{
                res += combination(m, k) * (-1) * log(fact) / k;
            }
        }
        fact = 1.0;
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return res;
}

double gamma_row(double eps)
{
    double res = 0.0;
    double prev = 0.0;
    double tmp = 0.0;
    for(double k = 2;; k++){
        prev = res;
        tmp = (1 / pow(floor(sqrt(k)), 2)) - (1.0 / k);
        if(fabs(tmp) < 0.00000000001){
            prev = 0.0;
            continue;
        }
        res += tmp;
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return res - pow(M_PI, 2) / 6;
}

double lim_for_gamma(double eps)
{
    double res = 1.0;
    double prev = 0.0;
    double tmp = 1.0;
    for(int t = 1;; t++){
        prev = res;
        for(int p = 2; p <= t; p++){
            if(isprime(p)){
                tmp *= (1.0 - 1.0 / p);
            }
        }
        res = log(t) * tmp;
        tmp = 1.0;
        if(fabs(res - prev) < eps){
            break;
        }
    }
    return res;
}

double gamma_eq(double x)
{
    double eps = 0.0001;
    return exp(-x) - lim_for_gamma(eps);
}

int main()
{
    int precision;
    printf("Enter the precision:\n");
    scanf("%d", &precision);
    double eps = epsilon(precision);
    if(isnan(eps)){
        printf("Enter only positive number!\n");
        return 0;
    }
    
    printf("e with limit = %lf\n", e_lim(eps));
    printf("e with row = %lf\n", e_row(eps));
    printf("e with equation = %lf\n", dichotomy(e_eq, 0, 5, eps));
    printf("pi with limit = %lf\n", pi_lim(eps));
    printf("pi with row = %lf\n", pi_row(epsilon(6)));
    printf("pi with equation = %lf\n", dichotomy(pi_eq, 0, 5, eps));
    printf("ln(2) with limit = %lf\n", ln2_lim(eps));
    printf("ln(2) with row = %lf\n", ln2_row(epsilon(6)));
    printf("ln(2) with equation = %lf\n", dichotomy(ln2_eq, 0, 5, eps));
    printf("sqrt(2) with limit = %lf\n", sqrt2_lim(eps));
    printf("sqrt(2) with row = %lf\n", sqrt2_row(eps));
    printf("sqrt(2) with equation = %lf\n", dichotomy(sqrt2_eq, 0, 5, eps));
    printf("gamma with limit = %lf\n", gamma_lim(epsilon(4)));
    printf("gamma with row = %lf\n", gamma_row(epsilon(9)));
    printf("gamma with equation = %lf\n", dichotomy(gamma_eq, 0, 5, epsilon(9)));

    return 0;
}
