#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct {
    int status; //статус ошибки
    int countfile; //колво файлов
    char **filename; //имена файлов
    int *countidx; //колво вхождений в файле
    int **index; //индексы ответов
} answer;

void free_filename(answer *res)
{
    for(int i = 0; i < res->countfile; i++){
        free(res->filename[i]);
    }
    free(res->filename);
}

void free_index(answer *res)
{
    for(int i = 0; i < res->countfile; i++){
        free(res->index[i]);
    }
    free(res->index);
}

//конвертируем va_arg в массив чаров для дальнейшего использования
void create_filename(char *string, char **filename, int idx)
{
    answer res;
    int size = strlen(string);
    filename[idx] = (char*)malloc(sizeof(char) * (size + 1));
    if(filename[idx] == NULL){
        return;
    }
    
    strcpy(filename[idx], string);
}

//поиск подстроки в файле
void search_substring(answer *res, char* substring, FILE *file, int file_num)
{
    char str[255];
    int size = strlen(substring);
    int j = 0, str_num = 0, idx_start = 0, idx_end = 0, idx = 0;
    int count_substrings = 0;
    int *tmp;
    while((fgets(str, 255, file)) != NULL){
        str_num++;
        for(int i = 0; str[i] != '\0'; i++){

            if(str[i] == substring[j] && j == 0){
                idx_start = i;
                j++;
            } else if(str[i] == substring[j] && j < size - 1){
                j++;
                continue;
            } else if(str[i] == substring[j] && j == size - 1){
                idx_end = i;
            } else{
                j = 0;
            }

            if(idx_end - idx_start == size - 1){
                count_substrings++;

                tmp = (int*)realloc(res->index[file_num], sizeof(int) * (idx + 3));
                //res->index[file_num] = (int*)malloc(sizeof(int) * 50);
                if(tmp == NULL){
                    res->status = 1;
                    return;
                } else{
                    res->index[file_num] = tmp;
                }
                res->index[file_num][idx] = str_num;
                res->index[file_num][idx + 1] = idx_start;
                res->index[file_num][idx + 2] = idx_end;
                idx += 3;
                idx_end = 0;
            }

        }
    }
    res->countidx[file_num] = count_substrings;
}

//проход по файлам
void go_files(answer *res, char* string)
{
    FILE *fin = NULL;

    for(int i = 0; i < res->countfile; i++){

        fin = fopen(res->filename[i], "r");
        if(!fin){
            res->status = 2;
            break;
        }

        if(res->status == 2){
            return;
        }
        search_substring(res, string, fin, i);
        if(res->status == 1){
            return;
        }
        fclose(fin);
    }
}

//0 - все в порядке, 1 - память не выделилась, 2 - файл не открылся
answer maketask(int count, char* string, ...)
{
    answer res;
    res.countfile = count;
    res.status = 0;
    va_list runner;
    va_start(runner, string);
    res.filename = (char**)malloc(sizeof(char*) * count);
    if(res.filename == NULL){
        res.status = 1;
        return res;
    }
    res.countidx = (int*)malloc(sizeof(int) * count);
    if(res.countidx == NULL){
        free(res.filename);
        res.status = 1;
        return res;
    }
    res.index = (int**)malloc(sizeof(int*) * count);
    if(res.index == NULL){
        free(res.filename);
        free(res.countidx);
        res.status = 1;
        return res;
    }

    for(int i = 0; i < count; i++){
        res.filename[i] = NULL;
    }

    //сохраняем имена файлов
    for(int i = 0; i < count; i++){
        res.filename[i] = NULL;
        create_filename(va_arg(runner, char*), res.filename, i);
        if(res.filename[i] == NULL){
            res.status = 1;
            break;
        }
    }
    //очищаем если не выделилась память
    if(res.status == 1){
        for(int i = 0; i < count; i++){
            if(res.filename[i] != NULL){
                free(res.filename[i]);
            }
        }
        free(res.filename);
        free(res.countidx);
        free(res.index);
        return res;
    }

    for(int i = 0; i < res.countfile; i++){
        res.index[i] = NULL;
    }
    go_files(&res, string);
    if(res.status == 2){

        free_filename(&res);
        free(res.countidx);
        free(res.index);

    } else if(res.status == 1){

        free_filename(&res);
        free(res.countidx);
        for(int i = 0; i < res.countfile; i++){
            if(res.index[i] != NULL){
                free(res.index[i]);
            }
            free(res.index);
        }

    }

    return res;
}

void print_res(answer *res)
{
    for(int i = 0; i < res->countfile; i++){
        printf("%d) %s:\n", i + 1, res->filename[i]);
        printf("\t%d occurences:\n", res->countidx[i]);
        for(int j = 0; j < res->countidx[i]; j++){
            printf("\t String #%d: %d-%d\n", res->index[i][j * 3], res->index[i][j * 3 + 1], res->index[i][j * 3 + 2]);
        }
        printf("\n");
    }
}

int main()
{
    printf("Enter the string:\n");
    char str[255];
    //scanf("%s", str);
    gets(str);
    
    answer res;
    res = maketask(3, str, (char*)"file1.txt", (char*)"file2.txt", (char*)"file3.txt");

    if(res.status == 1){
        printf("Memory wasn't allocated!\n");
        return 0;
    } else if(res.status == 2){
        printf("Can't open the file!\n");
        return 0;
    } else{
        print_res(&res);
        free_filename(&res);
        free_index(&res);
        free(res.countidx);
    }

    return 0;
}