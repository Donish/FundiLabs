#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int nearest_el(int *array, int element, int size)
{
    int res = array[0];
    int difference = abs(element - array[0]);
    for(int i = 1; i < size; i++){
        if(abs(element - array[i]) < difference){
            difference = abs(element - array[i]);
            res = array[i];
        }
    }
    return res;
}

int *generate_array(int size)
{
    int *array = (int*)malloc(sizeof(int) * size);
    if(array == NULL){
        return NULL;
    }
    for(int i = 0; i < size; i++){
        array[i] = rand();
    }
    return array;
}

int *complete_task(int *arr1, int *arr2, int size1, int size2)
{
    int *res = (int*)malloc(sizeof(int) * size1);
    if(res == NULL){
        return NULL;
    }
    for(int i = 0; i < size1; i++){
        res[i] = arr1[i] + nearest_el(arr2, arr1[i], size2);
    }
    return res;
}

void print_arr(int *array, int size)
{
    for(int i = 0; i < size; i++){
        printf("[%d] ", array[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    printf("Enter arrays sizes:\n");
    int size1, size2;
    scanf("%d%d", &size1, &size2);
    
    int *arr1 = generate_array(size1);
    if(arr1 == NULL){
        printf("Memory wasn't allocated!\n");
        return 0;
    }
    int *arr2 = generate_array(size2);
    if(arr1 == NULL || arr2 == NULL){
        printf("Memory wasn't allocated!\n");
        free(arr1);
        return 0;
    }
    int *res = complete_task(arr1, arr2, size1, size2);
    if(res == NULL){
        printf("Memory wasn't allocated!\n");
        free(arr1);
        free(arr2);
        return 0;
    }

    printf("A: ");
    print_arr(arr1, size1);
    printf("B: ");
    print_arr(arr2, size2);
    printf("C: ");
    print_arr(res, size1);

    free(arr1);
    free(arr2);
    free(res);
    return 0;
}
