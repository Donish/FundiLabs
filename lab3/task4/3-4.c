#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum ERROR{
    CORRECT = 0,
    NO_MEMORY = 1,
    NO_FILE = 2
};

typedef struct{
    int id;
    char *text;
    int len;
}message;

char *generate_filename()
{
    char *res = NULL;
    char c;
    int size = 1 + rand() % 10;
    int flag;

    res = (char*)malloc(sizeof(char) * (size + 5));
    res[size + 4] = '\0';
    for(int i = 0; i < size; i++){
        flag = rand() % 2; // 1 - буква, если 2 - цифра
        if(flag == 1){
            c = 97 + rand() % 26;
        } else{
            c = 48 + rand() % 10;
        }
        res[i] = c;
    }
    res[size] = '.';
    res[size + 1] = 'c';
    res[size + 2] = 's';
    res[size + 3] = 'v';
    return res;
}

//считывание сообщения
void scanmsg(message *msg, int *flag)
{
    char *tmp_msg, *coma_input;
    msg->text = NULL;
    int count = 2, coma_avail = 0;
    msg->len = 0;
    char c;

    tmp_msg = (char*)realloc(msg->text, count * sizeof(char));
    if(!tmp_msg){
        *flag = NO_MEMORY;
        return;
    }
    msg->text = tmp_msg;

    //считывание через tmp_msg
    while((c = getchar()) != '\n'){
        if(msg->len >= count){
            count *= 2;
            tmp_msg = (char*)realloc(msg->text, count * sizeof(char));
            if(!tmp_msg){
                *flag = NO_MEMORY;
                free(msg->text);
                return;
            }
            msg->text = tmp_msg;
        }

        if(c == ',' || c == ';'){
            coma_avail = 1;
        }
        msg->text[msg->len] = c;
        msg->len++;
    }

    //в случае наличия знаков, добавление кавычек через coma_input
    if(coma_avail){
        coma_input = (char*)malloc(sizeof(char) * (msg->len + 3));
        if(!coma_input){
            *flag = NO_MEMORY;
            free(msg->text);
            return;
        }

        coma_input[0] = '"';
        for(int i = 0; i < msg->len; i++){
            coma_input[i + 1] = msg->text[i];
        }
        coma_input[msg->len + 1] = '"';
        coma_input[msg->len + 2] = '\0';
        msg->text = coma_input;
        free(tmp_msg);
        return;
    }
    
    if(msg->len >= count){
        count *= 2;
        tmp_msg = (char*)realloc(msg->text, count * sizeof(char));
        if(!tmp_msg){
            *flag = NO_MEMORY;
            free(msg->text);
            return;
        }
    }
    msg->text[msg->len] = '\0';
}

//заполнение файла
void filefill(message *msg, FILE *file)
{
    fprintf(file, "%d;", msg->id);
    fprintf(file, "%s;", msg->text);
    fprintf(file, "%d\n", msg->len);
}

//заполнение структуры
void structfill(message *res, char *stop_word, int *flag, char *filename)
{
    FILE *fout;
    fout = fopen(filename, "w");
    res->id = 0;

    while(1){
        printf("Enter the message:\n");

        scanmsg(res, flag);
        if(*flag == NO_MEMORY){
            fclose(fout);
            return;
        }
        if(!strcmp(res->text, stop_word)){
            free(res->text);
            fclose(fout);
            return;
        }
        //check input message (if it's only spaces, tabs, \0, no letters or digits)
        res->id++;
        filefill(res, fout);
        free(res->text);
    }
}

// message *res_struct_fill(char *filename, int *flag)
// {
//     FILE *fin;
//     fin = fopen(filename, "r");
//     if(!fin){
//         *flag = NO_FILE;
//         return NULL;
//     }


// }


int main(int argc, char *argv[])
{
    srand(time(NULL));
    if(argc > 2){
        printf("Enter only one word!\n");
        return 0;
    } else if(argc == 1){
        printf("No arguments!\n");
        return 0;
    }

    char *filename = generate_filename();
    message msg;
    int flag = CORRECT;

    structfill(&msg, argv[1], &flag, filename);
    if(flag == NO_MEMORY){
        printf("Memory wasn't allocated!\n");
        return 0;
    }

    // message *res;
    // res = res_struct_fill(filename, &flag);

}