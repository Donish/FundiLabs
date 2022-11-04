#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

//побитовое возведение двойки в степень r
int bitpow(int r)
{
    int res;
    res = 1 << r;
    return res;
}

//побитовое сложение
int bitplus(int a, int b) {
    int res = 0, carry = 0;
    res = a ^ b;
    carry = (a & b) << 1;
    while (carry) {
        int tmp = res;
        res = res ^ carry;
        carry = (tmp & carry) << 1;
    }
    return res;
}

//побитовое вычитание
int negative(int num)
{
    return bitplus(~num, 1);
}

int bitminus(int a, int b)
{
    return bitplus(a, negative(b));
}

//побитовое умножение
int getSign(int n)
{
    return n >> 31;
}

int bitmultiply(int a, int b)
{
    int isNegative = 0;
    if(getSign(a) ^ getSign(b))
        isNegative = 1;
    a = abs(a);
    b = abs(b);
    int res = 0;
    while (b | 0) {
        if(b & 1)
            res = bitplus(res, a);
        a = a << 1;
        b = b >> 1;
    }
    return isNegative ? negative(res) : res;
}

// побитовое деление на степень двойки
int bitdivide(int a, int b)
{
    return a >> b;
}

//побитовый остаток от деления на степень двойки
int bitmod(int a, int b)
{
    b = bitminus(b, 1);
    return a & b;
}

//функция для перевода из 10-ной СС в другую
char* convert_from_ten(int number, int r, int *flag)
{
    if(r < 1 || r > 5){
        *flag = 1;
        return NULL;
    }
    int base = bitpow(r);
    char *res = NULL, *tmpc;
    int *ost_arr = NULL, *tmpint = NULL;
    int size = 0;
    int ostatok;
    int sign = 1;

    if(number == 0){
        res = (char*)malloc(bitmultiply(sizeof(char), 2));
        if(res == NULL){
            *flag = 2;
            return NULL;
        }
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    if(number < 0){
        number = bitmultiply(number, negative(1));
        sign = 0; //0 - число отриц
    }
    //заполнение массива остатков
    while(number != 0){
        tmpint = (int*)realloc(ost_arr, bitmultiply(sizeof(int), bitplus(size, 1)));
        if(tmpint == NULL){
            *flag = 2;
            if(size != 0)
                free(ost_arr);
            return NULL;
        }
        ost_arr = tmpint;

        ostatok = bitmod(number, base);
        number = bitdivide(number, r);
        if(*flag == 2){
            free(ost_arr);
            return NULL;
        }
        ost_arr[size] = ostatok;
        size = bitplus(size, 1);
    }

    int j = 0;
    if(!sign){
        res = (char*)malloc(sizeof(char));
        if(res == NULL){
            *flag = 2;
            free(ost_arr);
            return NULL;
        }
        res[0] = '-';
        j = 1;
    }

    for(int i = bitminus(size, 1); i >= 0; i = bitminus(i, 1), j = bitplus(j, 1)){
        tmpc = (char*)realloc(res, bitmultiply(sizeof(char), bitplus(j, 1)));
        if(tmpc == NULL){
            *flag = 2;
            free(ost_arr);
            if(j != 0)
                free(res);
            return NULL;
        }
        res = tmpc;
        if(ost_arr[i] < 10){
            res[j] = bitplus('0', ost_arr[i]);
        } else{
            res[j] = bitplus('A', (bitminus(ost_arr[i], 10)));
        }
    }


    tmpc = (char*)realloc(res, bitmultiply(sizeof(char), bitplus(j, 1)));
    if(tmpc == NULL){
        *flag = 2;
        free(ost_arr);
        free(res);
        return NULL;
    }
    res = tmpc;
    res[j] = '\0';
    free(ost_arr);
    return res;
}

//1 - неверная степень, 2 - не выделилась память
int main()
{
    int num, flag = 0, r;
    char* res;

    printf("Enter the number:\n");
    if(!scanf("%d", &num)){
        printf("Enter only integer number!\n");
        return 0;
    }
    printf("Enter the degree:\n");
    if(!scanf("%d", &r)){
        printf("Enter only integer number!\n");
        return 0;
    }

    res = convert_from_ten(num, r, &flag);
    if(flag == 1){
        printf("Wrong degree! Enter the number between 1 and 5.\n");
    } else if(flag == 2){
        printf("Memory wasn't allocated!\n");
    } else{
        printf("Converted number: %s", res);
        free(res);
    }

    return 0;
}
