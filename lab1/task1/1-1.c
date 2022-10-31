#include <stdlib.h
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

void argum_h(int number)  //аргумент -h, числа кратные введенному
{
    printf("Multiples of your number: ");
    for(int i = number; i < 101; i++){
        if(i % number == 0){
            printf("%d ", i);
        }
    }
}

long long int factorial(long long int number)  //факториал с проверкой на переполнение
{
    long long int res = 1;
    if(number == 0 || number == 1){
        return 1;
    } else{
        for(int i = 1; i <= number; i++){
            if(LLONG_MAX / res > i){
                res *= i;
            } else{
                return 0;
            }
        }
        return res;
    }
}


int main(int argc, char* argv[])
{
    if(argc == 1){
        printf("No arguments!\n");
        return 0;
    } else if(argc == 2){
        printf("You wrote only one argument!\n");
        return 0;
    } else if(argc > 3){
        printf("Too many arguments!\n");
        return 0;
    } else{

    
        for(int i = 0; argv[2][i] != '\0'; i++){ //проверка того, что число стоит на первом месте, а затем аргумент
            if((argv[2][i] > 47 && argv[2][i] < 58) && ((argv[1][0] == 45 || argv[1][0] == 47) && (argv[1][1] == 97 || argv[1][1] == 101 ||
            argv[1][1] == 102 || argv[1][1] == 104 || argv[1][1] == 112 || argv[1][1] == 115))){  
                printf("The number must be the first, then the flag!\n");
                return 0;
            }
        }

        int num = 0;
        if(argv[1][0] == 45){ //проверка входящего числа
            printf("Your number must be positive!\n"); //проверка на знак
            return 0;
        } else {
            for(int i = 0; argv[1][i] != '\0'; i++){ //проверка на наличие символа в числе
                if(argv[1][i] < 48 || argv[1][i] > 57){
                    printf("There is a symbol in your number!\n");
                    return 0;
                }
            }
        }

        for(int i = 0; argv[1][i] != '\0'; i++){ //перевод из строки в инт
            num += argv[1][i] - 48;
            num *= 10;
        }
        num /= 10;

        if(argv[2][0] != 45 && argv[2][0] != 47){  //проверка аргумента на наличие минуса или дроби
            printf("There must be symbol '-' or '/' before the flag!\n");
            return 0;
        }

        if(strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "/h") == 0){    //аргумент -h
            if(num > 100){
                printf("No multiples of your number!\n");
            } else if(num == 0){
                printf("You can't divide by zero!\n");
            } else{
                argum_h(num);
            }
            return 0;
        } else if(strcmp(argv[2], "-p") == 0 || strcmp(argv[2], "/p") == 0){    //аргумент -p
            if(num == 1 || num == 0){
                printf("Enter the number other than one or zero!\n");
                return 0;
            } else{
                for(int i = 2; i < floor(sqrt(num)); i++){
                    if(num % i == 0){
                        printf("Your number is composite!\n");
                        return 0;
                    }
                }
                printf("Your number is prime!\n");
                return 0;
            }
        } else if(strcmp(argv[2], "-s") == 0 || strcmp(argv[2], "/s") == 0){  //аргумент -s
            for(int i = 0; argv[1][i] != '\0'; i++){
                printf("%c ", argv[1][i]);
            }
        } else if(strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "/e") == 0){   //аргумент -e
            if(num == 0){
                printf("Enter number more than 0!\n");
                return 0;
            } else if(num > 10){
                printf("Enter number less than 11!\n");
                return 0;
            } else{
                long long int res = 0;
                for(int i = 1; i < 11; i++){
                    res = i;
                    printf("%d: ", i);
                    for(int j = 1; j <= num; j++){
                        for(int k = 1; k < j; k++){
                            res *= i;
                        }
                        printf("%lld ", res);
                        res = i;
                    }
                    printf("\n");
                }
                return 0;
            }                           
        } else if(strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "/a") == 0){   //аргумент -a
            if(num == 0){
                printf("Enter number more than 0!\n");
                return 0;
            } else{
                int res = 0;
                res = (num * (num + 1)) / 2;
                printf("%d\n", res);
                return 0;
            }
        } else if(strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "/f") == 0){  //аргумент -f
            long long int num_copy = num;
            num_copy = factorial(num_copy);
            if(num_copy == 0){
                printf("Overflow!\n");
                return 0;
            }
            printf("%lld\n", num_copy);
            return 0;
        } else{
            printf("Wrong arguments!\n");
            return 0;
        }
    }
}
