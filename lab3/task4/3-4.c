#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

enum ERROR{
    CORRECT = 0,
    NO_MEMORY = 1,
    NO_FILE = 2,
    WRONG_MESSAGE = 3
};

typedef struct{
    int id;
    char *text;
    int len;
}message;

char *generate_filename(int *flag)
{
    char *res = NULL;
    char c;
    int size = 1 + rand() % 10;
    int letornum;

    res = (char*)malloc(sizeof(char) * (size + 5));
    if(!res){
        *flag = NO_MEMORY;
        return NULL;
    }
    res[size + 4] = '\0';
    for(int i = 0; i < size; i++){
        letornum = rand() % 2; // 1 - буква, если 2 - цифра
        if(letornum == 1){
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

    tmp_msg = (char*)malloc(count * sizeof(char));
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

        if(c == ','){
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

//проверка введенного сообщения
int check_input(char *string, int len)
{
    int flag = WRONG_MESSAGE;
    if(string[0] == '"' && string[len + 1] == '"'){
        for(int i = 1; i < len + 1; i++){
            if(isalnum(string[i]))
                flag = CORRECT;

            if(string[i] == ';')
                return WRONG_MESSAGE;
            
        }
    } else{
        for(int i = 0; i < len; i++){
            if(isalnum(string[i]))
                flag = CORRECT;
            
            if(string[i] == ';')
                return WRONG_MESSAGE;
        }
    }
    return flag;
}

//заполнение файла
void filefill(message *msg, FILE *file)
{
    fprintf(file, "%d;", msg->id);
    fprintf(file, "%s;", msg->text);
    fprintf(file, "%d\n", msg->len);
}

//заполнение структуры
void input_struct_fill(message *res, char *stop_word, int *flag, char *filename)
{
    FILE *fout;
    fout = fopen(filename, "w");
    res->id = 0;
    int count_errors = 0;

    while(1){
        printf("Enter the message:\n");

        scanmsg(res, flag);

        if(*flag == NO_MEMORY){
            fclose(fout);
            return;
        }
        if(!strcmp(res->text, stop_word)){
            fclose(fout);
            return;
        }
        if(check_input(res->text, res->len) == WRONG_MESSAGE){
            count_errors++;
            free(res->text);
            if(count_errors == 3){
                *flag = WRONG_MESSAGE;
                fclose(fout);
                return;
            }
            printf("Message must include letters or digits and mustn't include ';'!\n");
            continue;
        }
        res->id++;
        filefill(res, fout);
        free(res->text);
    }
    fclose(fout);
}

//удаление кавычек при чтении из файла
void delete_quotes(char **string, int len, int *flag)
{
    char *res;
    res = (char*)malloc(sizeof(char) * (len + 1));
    if(!res){
        *flag = NO_MEMORY;
        return;
    }

    for(int i = 0; i < len; i++){
        res[i] = (*string)[i + 1];
    }
    res[len] = '\0';

    strcpy(*string, res);
    free(res);
}

message *res_struct_fill(char *filename, int *flag, int *res_size)
{
    FILE *fin;
    fin = fopen(filename, "r");
    if(!fin){
        *flag = NO_FILE;
        return NULL;
    }

    message *res = NULL;
    message *tmp;
    char buff[BUFSIZ];
    int buff_len = 0;
    char c;
    int count = 2;
    int msg_objects = 0;

    res = (message*)realloc(res, count * sizeof(message));
    if(!res){
        *flag = NO_MEMORY;
        fclose(fin);
        return NULL;
    }

    while((c = getc(fin)) != EOF){
        if(*res_size >= count){
            count *= 2;
            tmp = (message*)realloc(res, sizeof(message) * count);
            if(!tmp){
                *flag = NO_MEMORY;
                for(int i = 0; i < *res_size; i++){
                    free(res[i].text);
                }
                fclose(fin);
                free(res);
            }
            res = tmp;
        }

        if(c == ';' || c == '\n'){
            msg_objects++;
            if(msg_objects % 3 == 1){

                buff[buff_len] = '\0';
                res[*res_size].id = atoi(buff);
                
            } else if(msg_objects % 3 == 2){

                buff[buff_len] = '\0';
                res[*res_size].text = (char*)malloc(sizeof(char) * (buff_len + 1));
                if(!(res[*res_size].text)){
                    *flag = NO_MEMORY;
                    for(int i = 0; i < *res_size; i++){
                        free(res[i].text);
                    }
                    fclose(fin);
                    free(res);
                    return NULL;
                }
                strcpy(res[*res_size].text, buff);

            } else if(msg_objects % 3 == 0){

                buff[buff_len] = '\0';
                res[*res_size].len = atoi(buff);
                if(res[*res_size].text[0] == '"' && res[*res_size].text[res[*res_size].len + 1] == '"'){
                    delete_quotes(&(res[*res_size].text), res[*res_size].len, flag);
                    if(*flag == NO_MEMORY){
                        for(int i = 0; i < *res_size; i++){
                            free(res[i].text);
                        }        
                        free(res);
                        fclose(fin);                
                    }
                }
                (*res_size)++;

            }
            buff_len = 0;
            continue;
        }
        buff[buff_len] = c;
        buff_len++;
    }

    fclose(fin);
    return res;
}

void print_struct(message *res, int res_size)
{   
    for(int i = 0; i < res_size; i++){
        printf("ID:%d | ", res[i].id);
        printf("MESSAGE:%s | ", res[i].text);
        printf("LENGTH:%d\n", res[i].len);
    }
}

void free_struct(message *res, int res_size)
{
    for(int i = 0; i < res_size; i++){
        free(res[i].text);
    }
    free(res);
}

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

    int flag = CORRECT;
    char *filename = generate_filename(&flag);
    if(flag == NO_MEMORY){
        printf("Memory wasn't allocated!\n");
        return 0;
    }
    message msg;

    input_struct_fill(&msg, argv[1], &flag, filename);
    if(flag == NO_MEMORY){
        free(filename);
        printf("Memory wasn't allocated!\n");
        return 0;
    } else if(flag == WRONG_MESSAGE){
        free(filename);
        printf("You have entered wrong message 3 times in a row!\n");
        return 0;
    }
    free(msg.text);

    message *res;
    int res_size = 0;
    res = res_struct_fill(filename, &flag, &res_size);
    if(flag == NO_FILE){
        free(filename);
        printf("Couldn't open the file!\n");
        return 0;
    } else if(flag == NO_MEMORY){
        free(filename);
        printf("Memory wasn't allocated!\n");
        return 0;
    }

    print_struct(res, res_size);
    free_struct(res, res_size);
    free(filename);

    return 0;
}
