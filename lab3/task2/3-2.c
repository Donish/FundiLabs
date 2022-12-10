#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum ERROR {
    CORRECT = 0,
    ONLY_POSITIVE = 1,
    L_MORE = 2,
    MEMORY = 3
};

double combination(double m, double k, double eps)
{
    double res = 1.0;
    if(fabs(k) < eps || fabs(k - m) < eps){
        return 1.0;
    } else if(fabs(k - 1.0) < eps || fabs((k + 1) - m) < eps){
        return m;
    }
    for(; k > eps; m--, k--){
        res *= m / k;
    }
    return res;
}

void func1(int **arr, int *size, int k, int l, int *flag, double eps)
{
    if(l <= 0 || k <= 0){
        *flag = ONLY_POSITIVE;
        return;
    }
    if(l > k){
        *flag = L_MORE;
        return;
    }

    int num;
    if(k == l){ // если кол-во бит и единиц совпадает

        *size = 1;
        *arr = (int*)malloc(sizeof(int));
        if(*arr == NULL){
            *flag = MEMORY;
            return;
        }
        (*arr)[0] = (1 << l) - 1;

    } else if(l == 1){ // если кол-во единиц равно одному

        *size = k;
        *arr = (int*)malloc(sizeof(int) * *size);
        if(*arr == NULL){
            *flag = MEMORY;
            return;
        }
        num = 1;
        for(int i = 0; i < *size; i++){
            (*arr)[i] = num;
            num <<= 1;
        }

    } else if(l == k - 1){ // если l на 1 меньше, чем k

        *size = k;
        *arr = (int*)malloc(sizeof(int) * *size);
        num = (1 << k) - 2;
        int step = 1;
        for(int i = k - 1; i >= 0; i--){
            (*arr)[i] = num;
            num = num - (step);
            step <<= 1;
        }

    } else{ // в ином случае

        num = (1 << l) - 1;
        int num_border = (1 << k) - 2;
        *size = combination(k, l, eps);
        *arr = (int*)malloc(sizeof(int) * (*size + 1));
        if(*arr == NULL){
            *flag = MEMORY;
            return;
        }

        int num_cp, count_1 = 0, j = 1;
        (*arr)[0] = num;
        for(int i = num + 1; i < num_border; i++){
            num_cp = i;
            while(num_cp != 0){
                if(num_cp & 1)
                    count_1++;

                num_cp >>= 1;
            }
            if(count_1 == l){
                (*arr)[j] = i;
                j++;
            }
            count_1 = 0;
        }

    }

}

void func2(int **arr, int *size, int k, int l, int *flag)
{
    if(l <= 0 || k <= 0){
        *flag = ONLY_POSITIVE;
        return;
    }
    if(l > k){
        *flag = L_MORE;
        return;
    }


    int num;
    if(k == l){

        *size = 1;
        *arr = (int*)malloc(sizeof(int));
        if(*arr == NULL){
            *flag = MEMORY;
            return;
        }
        (*arr)[0] = (1 << l) - 1;

    } else if(l == 1){

        *size = k;
        *arr = (int*)malloc(sizeof(int) * *size);
        if(*arr == NULL){
            *flag = MEMORY;
            return;
        }
        num = 1;
        for(int i = 0; i < *size; i++){
            (*arr)[i] = num;
            num <<= 1;
        }

    } else if(l == k - 1){

        *size = 2;
        *arr = (int*)malloc(sizeof(int) * *size);
        if(*arr == NULL){
            *flag = MEMORY;
            return;
        }
        num = (1 << l) - 1;
        (*arr)[0] = num;
        num <<= 1;
        (*arr)[1] = num;

    } else{

        int num_cp, count_1 = 0;
        num = (1 << l) - 1;
        int num_border = (1 << k) - 2;
        *arr = (int*)malloc(sizeof(int) * (num_border - num));
        if(*arr == NULL){
            *flag = MEMORY;
            return;
        }
        (*arr)[0] = num;
        num++;
        (*size)++;
        for(int i = num; i < num_border; i++){
            num_cp = i;
            while(num_cp != 0){
                if((num_cp & 1) == 0)
                    count_1 = 0;
                else
                    count_1++;

                if(count_1 == l && ((num_cp >> 1) & 1) == 0){
                    (*arr)[*size] = i;
                    (*size)++;
                    break;
                }
                num_cp >>= 1;
            }
            count_1 = 0;

        }

    }
}

void printarr(int *arr, int size)
{
    for(int i = 0; i < size; i++){
        printf("[%d] ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int *res1 = NULL, *res2 = NULL;
    int size1 = 0, size2 = 0;
    int k, l, flag = CORRECT;
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

    double eps = 0.000000001;
    func1(&res1, &size1, k, l, &flag, eps);
    if(flag == ONLY_POSITIVE){
        printf("Enter only positive numbers!\n");
        return ONLY_POSITIVE;
    } else if(flag == L_MORE){
        printf("The number of units can't be greater than the number of bits!\n");
        return L_MORE;
    } else if(flag == MEMORY){
        printf("Memory wasn't allocated!\n");
        return MEMORY;
    } else{
        printf("There are %d %d-bit numbers with %d units in binary notation:\n", size1, k, l);
        printarr(res1, size1);
        printf("\n");
        free(res1);
    }

    func2(&res2, &size2, k, l, &flag);
    if(flag == ONLY_POSITIVE){
        printf("Enter only positive numbers!\n");
        return ONLY_POSITIVE;
    } else if(flag == L_MORE){
        printf("The number of units can't be greater than the number of bits!\n");
        return L_MORE;
    } else if(flag == MEMORY){
        printf("Memory wasn't allocated!\n");
        return MEMORY;
    } else{
        printf("There are %d %d-bit numbers with %d consecutive units in binary notation:\n", size2, k, l);
        printarr(res2, size2);
        printf("\n");
        free(res2);
    }

    return 0; 
}
