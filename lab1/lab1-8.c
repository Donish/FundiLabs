#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int fartherst_el(int* array, int element, int size)
{
    int res = 0;
    int difference = abs(element - array[0]);
    for(int i = 1; i < size; i++){
        if(abs(element - array[i]) > difference){
            difference = abs(element - array[i]);
            res = array[i];
        }
    }
    return res;
}

int prevs_sum(int* array, int index)
{
    int res = 0;
    for(int i = 0; i < index; i++){
        res += array[i];
    }
    return res;
}

int smallers_sum(int* array, int element, int size)
{
    int res = 0;
    for(int i = 0; i < size; i++){
        if(array[i] < element){
            res += array[i];
        }
    }
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

int strtoint(char* number)
{
    int res = 0, sign = 1;
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

void print_arr(int* array, int size)
{
    printf("New array: ");
    for(int i = 0; i < size; i++){
        printf("[%d] ", array[i]);
    }
    printf("\n");
}

int scan_idx(int size)
{
    printf("Enter the index\n");
    int index;
    scanf("%d", &index);
    if(index < 0){
        printf("Index must be positive!\n");
        return -1;
    }
    if(index > size - 1){
        printf("Index exceeds the size!\n");
        return -1;
    }
    return index;
}

int main(int argc, char* argv[])
{
    if(argc == 1){
        printf("No arguments!\n");
        return 0;
    } else if(argc > 3){
        printf("Too many arguments!\n");
        return 0;
    } else if(argc == 2){
        printf("Need more arguments!\n");
        return 0;
    }
    FILE *fin;
    fin = fopen(argv[1], "r");
    if(!fin){
        printf("Can't open the file!\n");
        return 0;
    }

    int arr[128];
    int new_arr[128];
    int new_size = 0;
    char num[100];
    int size = 0;
    printf("Array: ");
    while(fscanf(fin, "%s", num) != EOF){
        if(symbol_in_int(num)){
            continue;
        }
        arr[size] = strtoint(num);
        printf("[%d] ", arr[size]);
        size++;
    }
    printf("\n");
    fclose(fin);

    if(strcmp(argv[2], "-a") == 0){

        for(int i = 0; i < size; i++){
            if(i % 2 == 0){
                new_arr[new_size] = arr[i];
                new_size++;
            }
        }
        print_arr(new_arr, new_size);
        return 0;

    } else if(strcmp(argv[2], "-b") == 0){

        for(int i = 0; i < size; i++){
            if(arr[i] % 2 == 0){
                new_arr[new_size] = arr[i];
                new_size++;
            }
        }
        print_arr(new_arr, new_size);
        return 0;

    } else if(strcmp(argv[2], "-c") == 0){

        int idx = scan_idx(size);
        if(idx == -1){
            return 0;
        }
        new_size = 1;
        int res = fartherst_el(arr, arr[idx], size);
        new_arr[0] = res;
        print_arr(new_arr, new_size);
        return 0;

    } else if(strcmp(argv[2], "-d") == 0){

        int idx = scan_idx(size);
        if(idx == -1){
            return 0;
        }
        new_size = 1;
        int res = prevs_sum(arr, idx);
        new_arr[0] = res;
        print_arr(new_arr, new_size);
        return 0;

    } else if(strcmp(argv[2], "-e") == 0){

        int idx = scan_idx(size);
        if(idx == -1){
            return 0;
        }
        new_size = 1;
        int res = smallers_sum(arr, arr[idx], size);
        new_arr[0] = res;
        print_arr(new_arr, new_size);
        return 0;
        
    } else{
        printf("Wrong flag!\n");
        return 0;
    }
}