#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool files_opened(bool *opened, int size)
{
    for(int i = 0; i < size; i++){
        if(opened[i] == true){
            return true;
        }
    }
    return false;
}

void filenames_fi(FILE* file, char (*filenames)[100], int* size)
{
    while(fscanf(file, "%s", filenames[*size]) != EOF){
        (*size)++;
    }
    fclose(file);
}

void filenames_cin(char (*filenames)[100], int* size)
{
    printf("To stop entering print 'stop'\n");
    while(scanf("%s", filenames[*size]) != EOF && strcmp(filenames[*size], "stop") != 0){
        (*size)++;
    }
}

void filenames_arg(char* argv[], char (*filenames)[100], int size)
{
    int end_number = 0;
    for(int i = 2; i < size + 2; i++){
        for(int j = 0; argv[i][j] != '\0'; j++){
            filenames[i - 2][j] = argv[i][j];
            end_number = j;
        }
        filenames[i][end_number] = '\0';
    }
}

void res_file(FILE* resf, char (*filenames)[100], int size)
{
    FILE* files[100];
    bool opened[size];
    resf = fopen("out.txt", "w");
    char c;
    int flag = 0;

    for(int i= 0; i < size; i++){
        opened[i] = true;
        files[i] = NULL;
    }

    while(files_opened(opened, size)){
        for(int i = 0; i < size; i++){

            if(files[i] == NULL){
                files[i] = fopen(filenames[i], "r");
                if(!files[i]){ //проверяем файлы на открытие: если не открылось, то ставим флаг 1 и удаляем результирующий файл
                    flag = 1;
                    fclose(resf);
                    remove("out.txt");
                    break;
                }
            }

            c = getc(files[i]);
            if(c == EOF){
                fclose(files[i]);
                opened[i] = false;
            } else{
                putc(c, resf);
            }

        }
        if(flag){ //в случае неоткрытия файлов, закрываем все файлы и завершаем цикл
            for(int j = 0; j < size; j++){
                fclose(files[j]);
            }
            printf("Can't open some files!\n");
            break;
        }
    }
    if(flag == 0){
        printf("Done\n");
    }
    fclose(resf);
}

int main(int argc, char* argv[])
{
    FILE *fin, *fout;
    char c;
    char filenames[100][100];
    int size = 0;
    if(argc == 1){
        printf("No arguments\n");
        return 0;
    }
    if(strcmp(argv[1], "-fi") == 0){
        if(argc == 2){
            printf("Enter the file name!\n");
            return 0;
        }
        if(argc > 3){
            printf("Too many arguments!\n");
            return 0;
        }
        fin = fopen(argv[2], "r");
        if(!fin){
            printf("Can't open the file!\n");
            return 0;
        }
        filenames_fi(fin, filenames, &size);
        res_file(fout, filenames, size);
        return 0;

    } else if(strcmp(argv[1], "-cin") == 0){
        if(argc != 2){
            printf("Don't enter any arguments with this flag!\n");
            return 0;
        }
        printf("Enter file names:\n");
        filenames_cin(filenames, &size);
        if(size == 0){
            printf("You didn't enter any files!\n");
            remove("out.txt");
            return 0;
        }
        res_file(fout, filenames, size);
        return 0;

    } else if(strcmp(argv[1], "-arg") == 0){
        if(argc == 2){
            printf("Enter file names with this flag\n");
            return 0;
        }
        size = argc - 2;
        filenames_arg(argv, filenames, size);
        res_file(fout, filenames, size);
        return 0;

    } else{
        printf("Wrong arguments!\n");
        return 0;
    }
}
