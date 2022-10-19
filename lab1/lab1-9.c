#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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

long long int strtoint(char* number)
{
    long long int res = 0;
    int sign = 1;
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] == 45 && i == 0){
            sign = -1;
            continue;
        }
        res += number[i] - 48;
        res *= 10;
    }
    res /= 10;
    res *= sign;
    return res;
}

int symbol_in_int(char* number)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] == 45 && i == 0){
            continue;
        }
        if(number[i] > 57 || number[i] < 48){
            return 1;
        }
    }
    return 0;
}

int symbol_in_intandlet(char* number)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] == 45 && i == 0){
            continue;
        }
        if(!(isdigit(number[i]) || isalpha(number[i]))){
            return 1;
        }
    }
    return 0;
}

// функция для перевода числа в 10-ную СС из буквенной
long long int convert_letters_to_ten(char* number, int base)
{
    long long int res = 0;
    int size = strlen(number);
    long long int power = 1;
    int sign = 1;
    if(number[0] == '-'){
        sign = -1;
    }
    for(int i = size - 1, j = 0; i != -1; i--, j++){
        if(number[i] == '-' && i == 0){
            break;
        }
        if(isdigit(number[i])){
            res += (number[i] - '0') * power;
        }
        if(isalpha(number[i])){
            res += (tolower(number[i]) - 'a' + 10) * power;
        }
        power *= base;
    }
    return res * sign;
}

// функция для перевода числа в 10-ную из численной
long long int convert_digits_to_ten(char* number, int base)
{
    long long int res = 0;
    int size = strlen(number);
    long long int power = 1;
    int sign = 1;
    if(number[0] == '-'){
        sign = -1;
    }
    for(int i = size - 1, j = 0; i != -1; i--, j++){
        if(number[i] == '-' && i == 0){
            break;
        }
        res += (number[i] - '0') * power;
        power *= base;
    }
    return res * sign;
}

void convert_from_ten(long long int number, int base)
{
    char res[100];
    int ost_arr[100];
    int size = 0;
    int ostatok;
    int sign = 1;
    if(number < 0){
        number *= -1;
        sign = -1;
    }
    while(number != 0){
        ostatok = number % base;
        number /= base;
        ost_arr[size] = ostatok;
        size++;
    }
    res[size] = '\0';
    if(number == 0){
        res[0] = '0';
        res[1] = '\0';
    }
    for(int i = size - 1, j = 0; i != -1; i--, j++){
        if(sign == -1 && j == 0){
            res[j] = '-';
            res[size + 1] = '\0';
            j++;
        }
        if(ost_arr[i] < 10){
            res[j] = '0' + ost_arr[i];
        } else{
            res[j] = 'A' + (ost_arr[i] - 10);
        }
    }
    printf("%d: %s\n", base, res);
}

int main()
{
    printf("Enter the base of the number system!\n");
    int base;
    scanf("%d", &base);
    if(base < 2 || base > 36){
        printf("Enter only the number between 2 and 36!\n");
        return 0;
    }

    char num_str[20];
    long long int num = 0;
    long long int max_num = 0;
    while(1){
        scanf("%s", num_str);
        if(strcmp(num_str, "Stop") == 0 || strcmp(num_str, "stop") == 0){
            break;
        }
        if(base < 11){
            if(symbol_in_int(num_str)){
                printf("Only numbers!\n");
                continue;
            }
        } else{
            if(symbol_in_intandlet(num_str)){
                printf("Only numbers including digits and letters!\n");
                continue;
            }
        }
        if(check_base_num(num_str, base)){
            printf("Number doesn't match to the base!\n");
            continue;
        }
        num = convert_letters_to_ten(num_str, base);
        if(abs(num) > abs(max_num)){
            max_num = num;
        }
    }

    convert_from_ten(max_num, 9);
    convert_from_ten(max_num, 18);
    convert_from_ten(max_num, 27);
    convert_from_ten(max_num, 36);
    return 0;
}
