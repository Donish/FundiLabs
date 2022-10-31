#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int check_argc(int argc, char *flag)
{
    if(strcmp(flag, "-c") == 0){
        if(argc != 4){
            printf("Enter two strings with this flag!\n");
            return 1;
        }
    } else{
        if(argc != 3){
            printf("Enter one string with this flag!\n");
            return 1;
        }
    }
    return 0;
}

int str_length(char *string)
{
    int res = 0;
    while(string[res] != '\0'){
        res++;
    }
    return res;
}

char *reverse_str(char *string, int size)
{
    char *res = (char*)malloc(sizeof(char) * size);
    if(res == NULL){
        return NULL;
    }
    for(int i = 0; i < size; i++){
        res[i] = string[size - 1 - i];
    }
    return res;
}

void uppercase(char *string, int size)
{
    for(int i = 0; i < size; i++){
        if(i % 2 == 0){
            string[i] = toupper(string[i]);
        }
    }
}

void sort_syms(char *string, int size, char *res)
{
    char digits[size];
    char letters[size];
    char others[size];
    int digitsize = 0;
    int lettersize = 0;
    int othersize = 0;
    for(int i = 0; i < size; i++){
        if(isdigit(string[i])){
            digits[digitsize] = string[i];
            digitsize++;
        } else if(isalpha(string[i])){
            letters[lettersize] = string[i];
            lettersize++;
        } else{
            others[othersize] = string[i];
            othersize++;
        }
    }

    for(int i = 0; i < digitsize; i++){
        res[i] = digits[i];
    }
    for(int i = 0; i < lettersize; i++){
        res[i + digitsize] = letters[i];
    }
    for(int i = 0; i < othersize; i++){
        res[i + digitsize + lettersize] = others[i];
    }
}

char *concatenation(char *str1, char *str2, int size1, int size2)
{
    int size = size1 + size2;
    char *res = (char*)malloc(sizeof(char) * size);
    if(res == NULL){
        return NULL;
    }
    for(int i = 0; i < size1; i++){
        res[i] = str1[i];
    }
    for(int i = 0; i < size2; i++){
        res[i + size1] = str2[i];
    }
    res[size] = '\0';
    return res;
}

int main(int argc, char *argv[])
{
    if(argc == 1){
        printf("No arguments!\n");
        return 0;
    } else if(argc > 4){
        printf("Too many arguments!\n");
        return 0;
    }

    if(strcmp(argv[1], "-l") == 0){

        if(check_argc(argc, argv[1])){
            return 0;
        }

        int len = str_length(argv[2]);
        printf("Length of your string: %d\n", len);
        return 0;

    } else if(strcmp(argv[1], "-r") == 0){

        if(check_argc(argc, argv[1])){
            return 0;
        }

        int len = str_length(argv[2]);
        char *rev_str = reverse_str(argv[2], len);
        if(rev_str == NULL){
            printf("Memory wasn't allocated!\n");
            return 0;
        }
        printf("Reverse string: %s\n", rev_str);
        free(rev_str);
        return 0;

    } else if(strcmp(argv[1], "-u") == 0){

        if(check_argc(argc, argv[1])){
            return 0;
        }

        int len = (str_length(argv[2]));
        uppercase(argv[2], len);
        printf("Uppercase string: %s\n", argv[2]);
        return 0;

    } else if(strcmp(argv[1], "-n") == 0){

        if(check_argc(argc, argv[1])){
            return 0;
        }

        int len = str_length(argv[2]);
        char res[len];
        sort_syms(argv[2], len, res);
        printf("Sorted string: %s\n", res);
        return 0;

    } else if(strcmp(argv[1], "-c") == 0){

        if(check_argc(argc, argv[1])){
            return 0;
        }

        int len1 = str_length(argv[2]), len2 = str_length(argv[3]);
        char *res = concatenation(argv[2], argv[3], len1, len2);
        if(res == NULL){
            printf("Memory wasn't allocated!\n");
            return 0;
        }
        printf("New string: %s\n", res);
        free(res);
        return 0;

    } else{
        printf("Wrong flag!\n");
        return 0;
    }
}
