#include <stdio.h>
#include <stdlib.h>

void func1(int **arr, int *sz, int k, int l, int *flag)
{
    if(l < 0 || k < 0){
        *flag = 1;
        return;
    }
    if(l > k){
        *flag = 2;
        return;
    }

    int count_1 = 0;
    int num = 1 << (k - 1);
    int num_cp;
    int *tmp;
    for(int i = num; i < num * 2; i++){
        num_cp = i;
        while(num_cp != 0){
            if((num_cp & 1) == 1)
                count_1++;
            
            num_cp >>= 1;
        }
        if(count_1 == l){
            tmp = (int*)realloc(*arr, sizeof(int) * (*sz + 1));
            if(tmp == NULL){
                *flag = 3;
                if(*sz != 0)
                    free(arr);
                return;
            }
            *arr = tmp;
            (*arr)[*sz] = i;
            (*sz)++;
        }
        count_1 = 0;
    }
}

void func2(int **arr, int *sz, int k, int l, int *flag)
{
    if(l < 0 || k < 0){
        *flag = 1;
        return;
    }
    if(l > k){
        *flag = 2;
        return;
    }

    int num = 1 << (k - 1);
    if(k == l){
        *sz = 1;
        *arr = (int*)malloc(sizeof(int));
        (*arr)[0] = num * 2 - 1;
        return;
    } else if(l == 1){
        *sz = 1;
        *arr = (int*)malloc(sizeof(int));
        (*arr)[0] = num;
        return;
    }

    int count_1, num_cp;
    int *tmp;
    for(int i = num + 1; i < num * 2 - 1; i++){
        num_cp = i;
        while(num_cp != 0){
            if((num_cp & 1) == 0)
                count_1 = 0;
            else
                count_1++;
            
            if(count_1 == l && ((num_cp >> 1) & 1) == 0){
                tmp = (int*)realloc(*arr, sizeof(int) * (*sz + 1));
                if(tmp == NULL){
                    *flag = 3;
                    if(*sz != 0)
                        free(arr);
                    return;
                }
                *arr = tmp;
                (*arr)[*sz] = i;
                (*sz)++;
                break;
            }
            num_cp >>= 1;
        }
        count_1 = 0;
    }

}

void printarr(int *arr, int size)
{
    for(int i = 0; i < size; i++){
        printf("[%d] ", arr[i]);
    }
    printf("\n");
}

// 0 - все норм; 1 - введены отриц числа; 2 - l больше, чем k; 3 - не выделилась память; 
int main()
{
    int *res1 = NULL, *res2 = NULL;
    int sz1 = 0, sz2 = 0;
    int k, l, flag = 0;
    printf("Enter the number of bits:\n");
    if(!scanf("%d", &k)){
        printf("Enter only integer number!\n");
        return 0;
    }
    printf("Enter the number of units:\n");
    if(!scanf("%d", &l)){
        printf("Enter only integer number\n");
        return 0;
    }

    func1(&res1, &sz1, k, l, &flag);
    if(flag == 1){
        printf("Enter only positive numbers!\n");
        return 0;
    } else if(flag == 2){
        printf("The number of units can't be greater than the number of bits!\n");
        return 0;
    } else if(flag == 3){
        printf("Memory wasn't allocated!\n");
        return 0;
    } else{
        printf("There are %d %d-bit numbers with %d units in binary notation:\n", sz1, k, l);
        printarr(res1, sz1);
        printf("\n");
        free(res1);
    }

    func2(&res2, &sz2, k, l, &flag);
    if(flag == 1){
        printf("Enter only positive numbers!\n");
        return 0;
    } else if(flag == 2){
        printf("The number of units can't be greater than the number of bits!\n");
        return 0;
    } else if(flag == 3){
        printf("Memory wasn't allocated!\n");
        return 0;
    } else{
        printf("There are %d %d-bit numbers with %d consecutive units in binary notation:\n", sz2, k, l);
        printarr(res2, sz2);
        free(res2);
    }

    return 0; 
}