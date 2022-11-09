#include <stdio.h
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// функция по вычислению основания числа, в котором есть буква
int base_isalnum(char* number)
{
    int res = 11;
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] == '-' && i == 0){
            continue;
        }
        if(res < tolower(number[i])){
            res = tolower(number[i]);
        }
    }
    res = res - 'a' + 11;
    return res;
}

// функция по вычислению основания числа из цифр
int base_isdigit(char* number)
{
    int res = 1;
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] == '-' && i == 0){
            continue;
        }
        if(res < number[i]){
            res = number[i];
        }
    }
    res = res - '0' + 1;
    return res;
}

// функция по проверке наличия иных символов
int other_syms(char* number)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] == '-' && i == 0){
            continue;
        }
        if(!isalnum(number[i]) && number[i] != '\n' && number[i] != '\t' && number[i] != ' '){
            return 1;
        }
    }
    return 0;
}

// функция по наличию букв в числе
int isletter_in(char* number)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] == '-' && i == 0){
            continue;
        }
        if(isalpha(number[i])){
            return 1;
        }
    }
    return 0;
}

// функция по проверке, состоит ли число только из цифр
int isonly_digits(char* number)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] == '-' && i == 0){
            continue;
        }
        if(!isdigit(number[i])){
            return 0;
        }
    }
    return 1;
}

// функция для перевода числа в 10-ную СС из буквенной
long long int convert_letters(char* number, int base)
{
    long long int res = 0;
    int size = strlen(number);
    long long int power = 1;
    int sign = 1;
    if(number[0] == '-'){
        sign = -1;
    }
    for(int i = size - 1; i != -1; i--){
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
    return sign * res;
}

// функция для перевода числа в 10-ную из численной
long long int convert_digits(char* number, int base)
{
    long long int res = 0;
    int size = strlen(number);
    long long int power = 1;
    int sign = 1;
    if(number[0] == '-'){
        sign = -1;
    }
    for(int i = size - 1; i != -1; i--){
        if(number[i] == '-' && i == 0){
            break;
        }
        res += (number[i] - '0') * power;
        power *= base;
    }
    return sign * res;
}

//проверка числа на единственный ноль
int numiszero(char* number)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] != '0'){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[])
{
    FILE *fin, *fout;
    if(argc == 1){
        printf("No arguments!\n");
        return 0;
    }
    if(argc > 2){
        printf("Too many arguments!\n");
        return 0;
    }
    fin = fopen(argv[1], "r");
    if(!fin){
        printf("Can't open the file!\n");
        return 0;
    }
    fout = fopen("out.txt", "w");

    long long int converted = 0;
    int base = 0;
    char num[BUFSIZ];
    while(fscanf(fin, "%s", num) != EOF){

        if(other_syms(num)){
            continue;
        }

        if(numiszero(num)){
            fprintf(fout, "Input number:%s, Base:any, Converted number:%d\n", num, 0);
            continue;
        }

        if(isletter_in(num)){
            base = base_isalnum(num);
            converted = convert_letters(num, base);
            fprintf(fout, "Input number:%s, Base:%d, Converted number:%lld\n", num, base, converted);
            continue;
        }
        if(isonly_digits(num)){
            base = base_isdigit(num);
            converted = convert_digits(num, base);
            fprintf(fout, "Input number:%s, Base:%d, Converted number:%lld\n", num, base, converted);
            continue;
        }
    }

    printf("Done\n");
    fclose(fin);
    fclose(fout);
    return 0;
}
