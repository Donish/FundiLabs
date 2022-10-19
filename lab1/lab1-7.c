#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int strtoint(char* number)
{
    int res = 0;
    for(int i = 0; number[i] != '\0'; i++){
        res += number[i] - 48;
        res *= 10;
    }
    res /= 10;
    return res;
}

int symbol_in_int(char* number)
{
    for(int i = 0; number[i] != '\0'; i++){
        if(number[i] > 57 || number[i] < 48){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if(argc == 1){
        printf("No arguments!\n");
        return 0;
    } else if(argc > 2){
        printf("Enter only the size of array!\n");
        return 0;
    }
    if(symbol_in_int(argv[1])){
        printf("There is a symbol in your number!\n");
        return 0;
    }
    // создание массива
    int size = strtoint(argv[1]);
    int arr[size];
    printf("Array: ");
    for(int i = 0; i < size; i++){
        arr[i] = rand();
        printf("[%d] ", arr[i]);
    }
    printf("\n");

    // вычисление макса, мина и индексов
    int max_el = arr[0];
    int min_el = arr[0];
    int max_idx = 0;
    int min_idx = 0;
    for(int i = 1; i < size; i++){
        if(arr[i] > max_el){
            max_el = arr[i];
            max_idx = i;
        }
        if(arr[i] < min_el){
            min_el = arr[i];
            min_idx = i;
        }
    }

    printf("Maximum element:%d\nMinimum element:%d\n", max_el, min_el);
    // смена местами
    arr[max_idx] = min_el;
    arr[min_idx] = max_el;
    printf("New array: ");
    for(int i = 0; i < size; i++){
        printf("[%d] ", arr[i]);
    }
    printf("\n");
    return 0;
}
