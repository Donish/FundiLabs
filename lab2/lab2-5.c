#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int* create_array(int size, int r1, int r2)
{
    int *res = (int*)malloc(sizeof(int) * size);
    if(res == NULL){
        return NULL;
    }

    for(int i = 0; i < size; i++){
        res[i] = r1 + rand() % (r2 - r1 + 1);
    }
    return res;
}

int search_max_idx(int *array, int size)
{
    int el = array[0];
    int idx = 0;
    for(int i = 1; i < size; i++){
        if(array[i] > el){
            el = array[i];
            idx = i;
        }
    }
    return idx;
}

int search_min_idx(int *array, int size)
{
    int el = array[0];
    int idx = 0;
    for(int i = 1; i < size; i++){
        if(array[i] < el){
            el = array[i];
            idx = i;
        }
    }
    return idx;
}

void swap(int *min, int *max)
{
    int tmp = *max;
    *max = *min;
    *min = tmp;
}

int* unique_arr(int *array, int size, int *new_size)
{
    int *new_arr = (int*)malloc(sizeof(int) * size);
    if(new_arr == NULL){
        return NULL;
    }

    int flag = 1;
    new_arr[0] = array[0];
    for(int i = 1; i < size; i++){
        flag = 1;
        for(int j = 0; j < *new_size; j++){
            if(array[i] == new_arr[j]){
                flag = 0;
                break;
            }
        }
        if(flag){
            new_arr[*new_size] = array[i];
            *new_size = *new_size + 1;
        }

    }
    return new_arr;
}

void print_arr(int *arr, int size)
{
    for(int i = 0; i < size; i++){
        printf("[%d] ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if(argc != 2){
        printf("Enter only the flag!\n");
        return 0;
    }

    int *arr, size, range1, range2;
    printf("Enter the size of your array:\n");
    scanf("%d", &size);
    printf("Enter the range:\n");
    scanf("%d%d", &range1, &range2);

    arr = create_array(size, range1, range2);
    if(arr == NULL){
        printf("Memory wasn't allocated!\n");
        return 0;
    }
    printf("Array: ");
    print_arr(arr, size);

    if(strcmp(argv[1], "-a") == 0){

        int max = search_max_idx(arr, size);
        int min = search_min_idx(arr, size);
        swap(&arr[min], &arr[max]);
        printf("Changed array: ");
        print_arr(arr, size);

    } else if(strcmp(argv[1], "-b") == 0){

        int res_size = 1;
        int *res = unique_arr(arr, size, &res_size);
        if(res == NULL){
            printf("Memory wasn't allocated!\n");
            free(arr);
            return 0;
        }
        printf("New array: ");
        print_arr(res, res_size);
        free(res);

    } else{

        printf("Wrong flag!\n");

    }
    
    free(arr);
    return 0;
}