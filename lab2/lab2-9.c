#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>

//проверка на соотвествие числа основанию
int check_base_num(char* number, int base)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(isdigit(number[i])){
            if((number[i] - '0') >= base){
                return 1;
            }
        }
        if(isalpha(number[i])){
            if((toupper(number[i]) - 'A' + 10) >= base){
                return 1;
            }
        }
    }
    return 0;
}

// проверка на наличие лишнего символа в строке
int symbol_in_num(char* number)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(!(isdigit(number[i]) || isalpha(number[i]))){
            return 1;
        }
    }
    return 0;
}

char* nozero(char* string)
{
    int size = strlen(string);
    int count = 0;
    while(string[count] == '0'){
        count++;
    }
    int res_size = size - count;
    char* res = (char*)malloc(sizeof(char) * (size - count + 1));
    if(res == NULL){
        return NULL;
    }
    for(int i = 0; i < res_size; i++){
        res[i] = string[count + i];
    }
    res[res_size] = '\0';

    return res;
}

char* summing(char* str1, char* str2, int base)
{
    // создаем результирующую строку
    if(base < 2 || base > 36){
        return NULL;
    }
    int s1 = strlen(str1);
    int s2 = strlen(str2);
    int size;
    if(s1 > s2){
        size = s1 + 1;
    } else{
        size = s2 + 1;
    }
    char* result = (char*)malloc(sizeof(char) * size + 1);
    if(result == NULL){
        return NULL;
    }
    result[size] = '\0';

    // создаем две строки одинакового размера, чтобы было удобно складывать
    char* string1 = (char*)malloc(sizeof(char) * (size + 1));
    if(string1 == NULL){
        free(result);
        return NULL;
    }
    char* string2 = (char*)malloc(sizeof(char) * (size + 1));
    if(string2 == NULL){
        free(result);
        free(string1);
        return NULL;
    }
    string1[size] = '\0';
    string2[size] = '\0';
    for(int i = 0, j = 0; i < size; i++){
        if(i < size - s1){
            string1[i] = '0';
        } else{
            string1[i] = str1[j];
            j++;
        }
    }
    for(int i = 0, j = 0; i < size; i++){
        if(i < size - s2){
            string2[i] = '0';
        } else{
            string2[i] = str2[j];
            j++;
        }
    }

    // само складывание
    int summand1, summand2, sum, ost = 0;
    for(int i = size - 1; i >= 0; i--){
        //1 слагаемое
        if(isdigit(string1[i])){
            summand1 = string1[i] - '0';
        } else{
            summand1 = toupper(string1[i]) - 'A' + 10;
        }
        //2 слагаемое
        if(isdigit(string2[i])){
            summand2 = string2[i] - '0';
        } else{
            summand2 = toupper(string2[i]) - 'A' + 10;
        }
        
        sum = summand1 + summand2 + ost;
        if(sum >= base){
            ost = 1;
        } else{
            ost = 0;
        }
        sum %= base;
        if(sum < 10){
            result[i] = '0' + sum;
        } else{
            result[i] = 'A' + (sum % 10);
        }
        
    }
    free(string1);
    free(string2);
    return result;
}
// 1 - несоответствие числа системе счисления, 2 - лишний символ в числе
char* mysum(int* flag, int count, int base, ...)
{
    char* res;
    char* adding;
    va_list runner;
    va_start(runner, base);
    res = nozero(va_arg(runner, char*));
    if(res == NULL){
        return NULL;
    }
    if(check_base_num(res, base)){
        *flag = 1;
        free(res);
        return NULL;
    }
    if(symbol_in_num(res)){
        *flag = 2;
        free(res);
        return NULL;
    }

    //int size = strlen(res);
    for(int i = 0; i < count - 1; i++){

        adding = nozero(va_arg(runner, char*));
        if(adding == NULL){
            free(res);
            return NULL;
        }
        if(check_base_num(adding, base)){
            *flag = 1;
            free(res);
            free(adding);
            return NULL;
        }
        if(symbol_in_num(adding)){
            *flag = 2;
            free(res);
            free(adding);
            return NULL;
        }

        res = summing(res, adding, base);
        if(res == NULL){
            free(adding);
            return NULL;
        }

        free(adding);
    }
    va_end(runner);
    
    char* result = nozero(res);
    free(res);
    return result;
}

int main()
{
    int flag = 0;
    char *res;
    res = mysum(&flag, 2, 3, (char*)"1", (char*)"000000001");
    if(flag == 1){
        printf("The number doesn't match the base!\n");
        return 0;
    } else if(flag == 2){
        printf("There is a symbol in your number!\n");
        return 0;
    }
    if(res == NULL){
        printf("Memory wasn't allocated!\n");
        return 0;
    }
    printf("%s\n", res);
    free(res);

    return 0;
}
