#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

double **generate_matrix(int row, int column)
{
    double **matrix = (double**)malloc(sizeof(double) * row);
    for(int i = 0; i < row; i++){
        matrix[i] = (double*)malloc(sizeof(double) * column);
        for(int j = 0; j < column; j++){
            matrix[i][j] = -100 + rand() % (100 - (-100) + 1);
        }
    }
    return matrix;
}

double **product_of_matrix(double **matrix1, double **matrix2, int row1, int col1, int row2, int col2)
{
    double **res_matrix = (double**)malloc(sizeof(double) * row1);
    for(int i = 0; i < row1; i++){
        res_matrix[i] = (double*)malloc(sizeof(double) * col2);
        for(int j = 0; j < col2; j++){
            res_matrix[i][j] = 0;
            for(int k = 0; k < col1; k++){
                res_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return res_matrix;
}

double determinant(double **matrix, int row, int column)
{

    double eps = 0.00000001;
    double res = 1;
    int row_num = 0;
    double tmp = 0;
    int flag = 1;
    for(int k = 0; k < row - 1; k++){

        for(int i = row_num; i < row; i++){
            if(fabs(matrix[i][row_num]) < eps){
                continue;
            }
            tmp = matrix[i][row_num];
            res *= tmp;
            for(int j = row_num; j < column; j++){
                matrix[i][j] /= tmp;
            }
        }

        for(int i = row_num + 1; i < row; i++){
            if(fabs(matrix[i][row_num]) < eps){
                continue;
            }
            for(int j = row_num; j < column; j++){
                matrix[i][j] = matrix[i][j] - matrix[row_num][j];
            }
        }
        row_num++;
    }
    res *= matrix[row - 1][column - 1];
    return res;
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

    //создаем матрицы
    int row_size1 = 1 + rand()%(10);
    int column_size1 = 1 + rand()%(10);
    int row_size2 = 1 + rand()%(10);
    int column_size2 = 1 + rand()%(10);

    double **matrix1 = generate_matrix(row_size1, column_size1);
    double **matrix2 = generate_matrix(row_size2, column_size2);
    print_matrix(matrix1, row_size1, column_size1);
    printf("\n");
    print_matrix(matrix2, row_size2, column_size2);
    printf("\n");

    //умножение
    int product_row = 0;
    int product_col = 0;
    if(column_size1 == row_size2){
        double **matrix_product = product_of_matrix(matrix1, matrix2, row_size1, column_size1, row_size2, column_size2);
        product_row = row_size1;
        product_col = column_size2;
        printf("The product of matrix multiplication:\n");
        print_matrix(matrix_product, product_row, product_col);
        foofree(matrix_product, product_row);
    } else{
        printf("Matrices cannot be multiplied!\n");
    }
    printf("\n");

    //определитель
    double det1 = 0;
    double det2 = 0;
    if(row_size1 == column_size1){
        det1 = determinant(matrix1, row_size1, column_size1);
        printf("det1 = %f\n", det1);
    } else{
        printf("First matrix doesn't have determinant!\n");
    }
    if(row_size2 == column_size2){
        det2 = determinant(matrix2, row_size2, column_size2);
        printf("det2 = %f\n", det2);
    } else{
        printf("Second matrix doesn't have determinant!\n");
    }

    foofree(matrix1, row_size1);
    foofree(matrix2, row_size2);
    return 0;
}