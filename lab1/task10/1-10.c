#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

enum ERRORS{
    CORRECT = 0,
    NO_MEMORY = -1,
    NO_PRODUCT = -2,
    NO_DET = -3
};

double **generate_matrix(int row, int column, int *flag)
{
    double **matrix = (double**)malloc(sizeof(double) * row);
    if(matrix == NULL){
        *flag = NO_MEMORY;
        return NULL;
    }

    for(int i = 0; i < row; i++){
        matrix[i] = (double*)malloc(sizeof(double) * column);
        if(matrix[i] == NULL){
            *flag = NO_MEMORY;
            for(int j = 0; j < i; j++){
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }

        for(int j = 0; j < column; j++){
            matrix[i][j] = -100 + rand() % 201;
        }
    }
    return matrix;
}

double **product_of_matrix(double **matrix1, double **matrix2, int row1, int col1, int row2, int col2, int *flag)
{
    if(col1 != row2){
        *flag = NO_PRODUCT;
        return NULL;
    }

    double **res_matrix = (double**)malloc(sizeof(double) * row1);
    if(res_matrix == NULL){
        *flag = NO_MEMORY;
        return NULL;
    }

    for(int i = 0; i < row1; i++){
        res_matrix[i] = (double*)malloc(sizeof(double) * col2);
        if(res_matrix[i] == NULL){
            *flag = NO_MEMORY;
            for(int j = 0; j < i; j++){
                free(res_matrix[j]);
            }
            free(res_matrix);
            return NULL;
        }

        for(int j = 0; j < col2; j++){
            res_matrix[i][j] = 0;
            for(int k = 0; k < col1; k++){
                res_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return res_matrix;
}

void print_matrix(double **matrix, int row, int column)
{
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            printf("%9.2f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("size: %d x %d\n", row, column);
}

void row_difference(double *row_num, double *row, double coef, int size) {
	for (int i = 0; i < size; i++) {
		row[i] -= coef * row_num[i];
	}
}

void change_rows(double **matrix, int row_num, int size, double eps)
{
    int changing_row = 0;
    for(int j = 0; j < size; j++){
        if(fabs(matrix[j][row_num]) > eps){
            if(matrix[row_num][j] == 0){
                continue;
            }
            changing_row = j;
            break;
        }
    }
    double *tmp = matrix[row_num];
    matrix[row_num] = matrix[changing_row];
    matrix[changing_row] = tmp;
}

int det_eq_zero(double **matrix, int size, double eps)
{
    int flag_zero = 1;
    for(int i = 0; i < size; i++){
        flag_zero = 1;
        for(int j = 0; j < size; j++){
            if(fabs(matrix[i][j]) > eps){
                flag_zero = 0;
                break;
            }
        }
        if(flag_zero)
            return 1;
    }

    for(int i = 0; i < size; i++){
        flag_zero = 1;
        for(int j = 0; j < size; j++){
            if(fabs(matrix[j][i]) > eps){
                flag_zero = 0;
                break;
            }
        }
        if(flag_zero)
            return 1;
    }

    return flag_zero;
}

double determinant(double **matrix, int row, int col, double eps, int *flag)
{
    if(row != col){
        *flag = NO_DET;
        return NAN;
    }

    double res = 1;

    if(det_eq_zero(matrix, row, eps)){
        return 0;
    }

    for(int i = 0; i < row; i++){
        if(fabs(matrix[i][i]) < eps){
            change_rows(matrix, i, row, eps);
            res *= -1;
        }
    }

    for(int row_num = 0; row_num < row; row_num++){

        for(int row_minus = row_num + 1; row_minus < row; row_minus++){
            row_difference(matrix[row_num], matrix[row_minus], matrix[row_minus][row_num] / matrix[row_num][row_num], row);
        }
    }

    for(int i = 0; i < row; i++){
        res *= matrix[i][i];
    }

    return res;
}
// поправить сравнение с нулем
void foofree(double **matrix, int row)
{
    for(int i = 0; i < row; i++){
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{
    srand(time(NULL));
    int flag = CORRECT;

    //создаем матрицы
    int row_size1 = 1 + rand()% 10;
    int column_size1 = 1 + rand()% 10;
    int row_size2 = 1 + rand()% 10;
    int column_size2 = 1 + rand()% 10;

    double **matrix1 = generate_matrix(row_size1, column_size1, &flag);
    if(flag == NO_MEMORY){
        printf("Memory wasn't allocated!\n");
        return 0;
    }
    double **matrix2 = generate_matrix(row_size2, column_size2, &flag);
    if(flag == NO_MEMORY){
        foofree(matrix1, row_size1);
        printf("Memory wasn't allocated!\n");
        return 0;
    }

    print_matrix(matrix1, row_size1, column_size1);
    printf("\n");
    print_matrix(matrix2, row_size2, column_size2);
    printf("\n");

    //умножение
    int product_row = 0;
    int product_col = 0;
    double **matrix_product = product_of_matrix(matrix1, matrix2, row_size1, column_size1, row_size2, column_size2, &flag);
    if(flag == NO_PRODUCT){
        printf("Matrices cannot be multiplied!\n");
    } else if(flag == NO_MEMORY){
        printf("Memory wasn't allocated!\n");
        foofree(matrix1, row_size1);
        foofree(matrix2, row_size2);
        return 0;
    } else{
        product_row = row_size1;
        product_col = column_size2;
        printf("The product of matrix multiplication:\n");
        print_matrix(matrix_product, product_row, product_col);
        foofree(matrix_product, product_row);
    }
    printf("\n");
    flag = CORRECT;

    //определитель
    double det1 = 0;
    double det2 = 0;
    double epsilon = 0.0000001;

    det1 = determinant(matrix1, row_size1, column_size1, epsilon, &flag);
    if(flag == NO_DET){
        printf("Determinant doesn't exist!\n");
    } else{
        printf("det1 = %f\n", det1);
    }

    flag = CORRECT;
    det2 = determinant(matrix2, row_size2, column_size2, epsilon, &flag);
    if(flag == NO_DET){
        printf("Determinant doesn't exist!\n");
    } else{
        printf("det2 = %f\n", det2);
    }

    foofree(matrix1, row_size1);
    foofree(matrix2, row_size2);
    return 0;
}
