#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

enum ERRORS {
    CORRECT = 0,
    ARGS_ERROR = -1,
    MEMORY_ERROR = -2,
    NO_FILE = -3,
    IS_EOF = -4,
    WRONG_INFO_AMOUNT = -5,
    WRONG_NAME_SURNAME = -6,
    WRONG_COURSE = -7,
    WRONG_GROUP = -8,
    WRONG_MARKS = -9,
    WRONG_MENU_TASK = -10
};

typedef struct {
    int id;
    char *name;
    char *surname;
    int course;
    char *group;
    double *marks;
} student;

int scan_full_string(char **string, FILE *file)
{
    char c = '\0';
    char *tmp = NULL;
    int count = 2, curr_size = 0;

    *string = (char*)malloc(count * sizeof(char));
    if(*string == NULL)
        MEMORY_ERROR;
    
    while(1){
        c = getc(file);
        if(c == '\n' || c == EOF){
            break;
        }

        if(curr_size == count){
            count *= 2;
            tmp = (char*)realloc(*string, count * sizeof(char));
            
            if(!tmp){
                free(*string);
                return MEMORY_ERROR;
            }
            *string = tmp;
        }

        (*string)[curr_size] = c;
        curr_size++;
    }

    if(curr_size == count){
        count++;
        tmp = (char*)realloc(*string, count * sizeof(char));
        if(!tmp){
            free(*string);
            return MEMORY_ERROR;
        }

        *string = tmp;
    }
    (*string)[curr_size] = '\0';

    if(c == EOF){
        return IS_EOF;
    }

    return CORRECT;
}

int scan_stdin(char **string)
{
    // printf("hi\n");
    int count = 2, curr_size = 0;
    char c = '\0';
    char *tmp = NULL;

    *string = (char*)malloc(sizeof(char) * count);
    if(*string == NULL){
        return MEMORY_ERROR;
    }

    while(1){

        // printf("%c\n", c);
        c = getchar();
        if(c == '\n')
            break;
        
        if(curr_size == count){
            count *= 2;
            tmp = (char*)realloc(*string, sizeof(char) * count);
            if(!tmp){
                free(*string);
                return MEMORY_ERROR;
            }
            *string = tmp;
        }

        (*string)[curr_size] = c;
        curr_size++;
    }

    if(curr_size == count){
        count++;
        tmp = (char*)realloc(*string, sizeof(char) * count);
        if(!tmp){
            free(*string);
            return MEMORY_ERROR;
        }
        *string = tmp;
    }
    (*string)[curr_size] = '\0';

    return CORRECT;
}

void skip_spaces(char *string, int *idx)
{
    while(1){
        if(!isspace(string[*idx])){
            return;
        }
        (*idx)++;
    }
}

int split_full_string(char* full_str, student **res, int struct_size, double eps)
{
    int count = 0;

    for(int i = 0; full_str[i] != '\0'; i++){

        if(i == 0 && !isspace(full_str[i])){
            count++;
            continue;
        } else if(!isspace(full_str[i]) && isspace(full_str[i - 1])){
            count++;
            continue;
        }

    }

    if(count != 9)
        return WRONG_INFO_AMOUNT;

    char *course = NULL;
    char mark_str = '\0';
    int course_num = 0, mark = 0;
    int sur_size = 0, name_size = 0, course_size = 0, group_size = 0, marks_size = 0;
    int i = 0;

    while(1){
        if(isspace(full_str[i]) && sur_size > 0){
            break;
        }
        if(isspace(full_str[i])){
            i++;
            continue;
        }

        if(!isalpha(full_str[i])){
            return WRONG_NAME_SURNAME;
        }
        sur_size++;
        i++;
    }


    while(1){
        if(isspace(full_str[i]) && name_size > 0){
            break;
        }

        if(isspace(full_str[i])){
            i++;
            continue;
        }
        if(!isalpha(full_str[i])){
            return WRONG_NAME_SURNAME;
        }
        name_size++;
        i++;
    }

    while(1){
        if(isspace(full_str[i]) && course_size > 0){
            break;
        }
        if(isspace(full_str[i])){
            i++;
            continue;
        }

        if(!isdigit(full_str[i])){
            return WRONG_COURSE;
        }
        course_size++;
        i++;
    }

    while(1){
        if(isspace(full_str[i]) && group_size > 0){
            break;
        }
        if(isspace(full_str[i])){
            i++;
            continue;
        }

        if(!isalnum(full_str[i])){
            return WRONG_GROUP;
        }
        group_size++;
        i++;
    }

    while(1){
        if(full_str[i] == '\0'){
            break;
        }
        if(!(isspace(full_str[i]) || isdigit(full_str[i]))){
            return WRONG_MARKS;
        }
        if(isdigit(full_str[i]) && isspace(full_str[i - 1])){
            marks_size++;
        }
        i++;
    }

    (*res)[struct_size].surname = (char*)malloc(sizeof(char) * (sur_size + 1));
    if((*res)[struct_size].surname == NULL){
        return MEMORY_ERROR;
    }

    (*res)[struct_size].name = (char*)malloc(sizeof(char) * (name_size + 1));
    if((*res)[struct_size].name == NULL){
        free((*res)[struct_size].surname);
        return MEMORY_ERROR;
    }

    course = (char*)malloc(sizeof(char) * (course_size + 1));
    if(!course){
        free((*res)[struct_size].surname);
        free((*res)[struct_size].name);
        return MEMORY_ERROR;
    }

    (*res)[struct_size].group = (char*)malloc(sizeof(char) * (group_size + 1));
    if((*res)[struct_size].group == NULL){
        free((*res)[struct_size].surname);
        free((*res)[struct_size].name);
        free(course);
        return MEMORY_ERROR;
    }

    (*res)[struct_size].marks = (double*)malloc(sizeof(double) * marks_size);
    if((*res)[struct_size].marks == NULL){
        free((*res)[struct_size].surname);
        free((*res)[struct_size].name);
        free(course);
        free((*res)[struct_size].group);
        return MEMORY_ERROR;
    }

    i = 0;
    int j = 0;
    skip_spaces(full_str, &i);
    for(j = 0; j < sur_size; j++){
        (*res)[struct_size].surname[j] = full_str[i];
        i++;
    }
    (*res)[struct_size].surname[sur_size] = 0;
    skip_spaces(full_str, &i);

    for(j = 0; j < name_size; j++){
        (*res)[struct_size].name[j] = full_str[i];
        i++;
    }
    (*res)[struct_size].name[j] = '\0';
    skip_spaces(full_str, &i);

    for(j = 0; j < course_size; j++){
        course[j] = full_str[i];
        i++;
    }
    course[j] = '\0';
    skip_spaces(full_str, &i);

    for(j = 0; j < group_size; j++){
        (*res)[struct_size].group[j] = full_str[i];
        i++;
    }
    (*res)[struct_size].group[j] = '\0';
    skip_spaces(full_str, &i);

    course_num = atoi(course);
    if(course_num < 1 || course_num > 4){

        free((*res)[struct_size].surname);
        free((*res)[struct_size].name);
        free((*res)[struct_size].group);
        free(course);
        free((*res)[struct_size].marks);
        return WRONG_COURSE;

    }
    (*res)[struct_size].course = course_num;

    int num_len = 0, marks_idx = 0;
    for(int k = 0; k < marks_size; k++){

        num_len = 0;
        skip_spaces(full_str, &i);

        while(1){

            if(num_len > 1){
                free((*res)[struct_size].surname);
                free((*res)[struct_size].name);
                free((*res)[struct_size].group);
                free(course);
                free((*res)[struct_size].marks);
                return WRONG_MARKS;
            }

            if(isspace(full_str[i]) || full_str[i] == '\0'){
                break;
            }

            mark_str = full_str[i];
            num_len++;
            i++;

        }
        (*res)[struct_size].marks[k] = mark_str - '0';
        if((*res)[struct_size].marks[k] < 2 || (*res)[struct_size].marks[k] > 5){
            free((*res)[struct_size].surname);
            free((*res)[struct_size].name);
            free((*res)[struct_size].group);
            free(course);
            free((*res)[struct_size].marks);
            return WRONG_MARKS;
        }

    }
    
    free(course);
    return CORRECT;
}

void free_student(student *res, int count)
{
    for(int i = 0; i < count; i++){
        free(res[i].surname);
        free(res[i].name);
        free(res[i].group);
        free(res[i].marks);
    }
    free(res);
}

int fill_struct_student(student **res, char *filename, int *curr_size, double eps)
{
    FILE *fin = NULL;
    fin = fopen(filename, "r");
    if(!fin)
        return NO_FILE;
    
    int flag = CORRECT, eof_flag = 0;
    int count = 2;
    char *full_str = NULL;
    student *tmp;

    *res = (student*)malloc(count * sizeof(student));
    if(*res == NULL){
        fclose(fin);
        return MEMORY_ERROR;
    }

    while(1){

        if(*curr_size == count){
            count *= 2;
            tmp = (student*)realloc(*res, count * sizeof(student));

            if(!tmp){
                fclose(fin);
                free_student(*res, *curr_size);
                return MEMORY_ERROR;
            }
            *res = tmp;
        }

        flag = scan_full_string(&full_str, fin);
        if(flag == MEMORY_ERROR){
            fclose(fin);
            free_student(*res, *curr_size);
            return MEMORY_ERROR;
        } else if(flag == IS_EOF){
            eof_flag = 1;
        }

        flag = split_full_string(full_str, res, *curr_size, eps);


        if(flag != CORRECT){
            free(full_str);
            fclose(fin);
            free_student(*res, *curr_size);
            return flag;
        }
        (*res)[*curr_size].id = *curr_size + 1;

        free(full_str);

        (*curr_size)++;
        if(eof_flag){
            break;
        }
    }

    fclose(fin);
    free_student(*res, *curr_size);
    return CORRECT;
}

void print_student_avg(student *res, int size)
{
    double avg_mark = 0.0;
    double total = 0.0;  

    for(int i = 0; i < size; i++){
        for(int j = 0; j < 5; j++){
            total += res[i].marks[j];
        }
        avg_mark = total / 5;

        printf("ID:%d | SURNAME:%s | NAME:%s | YEAR:%d | GROUP:%s | AVG MARK:%.2lf\n", res[i].id, res[i].surname, res[i].name, res[i].course, res[i].group, avg_mark);
        total = 0.0;
    }
}

void print_student_just(student *res, int size)
{
    for(int i = 0; i < size; i++){
        printf("ID:%d | SURNAME:%s | NAME:%s | YEAR:%d | GROUP:%s | MARKS:", res[i].id, res[i].surname, res[i].name, res[i].course, res[i].group);
        for(int j = 0; j < 5; j++){
            printf("%.0lf ", res[i].marks[j]);
        }
        printf("\n");
    }
}

int check_sur_name(char *string)
{
    for(int i = 0; string[i] != '\0'; i++){
        if(!isalpha(string[i]))
            return WRONG_NAME_SURNAME;
    }
    return CORRECT;
}

int check_group(char *string)
{
    for(int i = 0; string[i] != '\0'; i++){
        if(!isalnum(string[i])){
            return WRONG_GROUP;
        }
    }
    return CORRECT;
}

student *search_parameter(student *res, int student_size, int parameter, int *flag, int *curr_size, char *search_word, int search_year)
{
    int count = 2;
    student *found;
    student *tmp;

    found = (student*)malloc(sizeof(student) * count);
    if(!found){
        *flag = MEMORY_ERROR;
        return NULL;
    }

    if(parameter == 1){

        *flag = check_sur_name(search_word);
        if(*flag == WRONG_NAME_SURNAME){
            free(found);
            return NULL;
        }

        for(int i = 0; i < student_size; i++){
            if(*curr_size == count){
                count *= 2;
                tmp = (student*)realloc(found, sizeof(student) * count);
                if(!tmp){
                    free(found);
                    *flag = MEMORY_ERROR;
                    return NULL;
                }
                found = tmp;
            }

            if(!strcmp(search_word, res[i].surname)){
                found[*curr_size] = res[i];
                (*curr_size)++;
            }
        }

    } else if(parameter == 2){

        if(search_year < 1 || search_year > 4){
            free(found);
            *flag = WRONG_COURSE;
            return NULL;
        }

        for(int i = 0; i < student_size; i++){
            if(*curr_size == count){
                count *= 2;
                tmp = (student*)realloc(found, sizeof(student) * count);
                if(!tmp){
                    free(found);
                    *flag = MEMORY_ERROR;
                    return NULL;
                }
                found = tmp;
            }

            if(search_year == res[i].course){
                found[*curr_size] = res[i];
                (*curr_size)++;
            }
        }

    } else if(parameter == 3){

        *flag = check_group(search_word);
        if(*flag == WRONG_GROUP){
            free(found);
            return NULL;
        }

        for(int i = 0; i < student_size; i++){
            if(*curr_size == count){
                count *= 2;
                tmp = (student*)realloc(found, sizeof(student) * count);
                if(!tmp){
                    free(found);
                    *flag = MEMORY_ERROR;
                    return NULL;
                }
                found = tmp;
            }

            if(!strcmp(search_word, res[i].group)){
                found[*curr_size] = res[i];
                (*curr_size)++;
            }
        }

    }

    return found;
}

int compare_id(const void *a, const void *b)
{
    const student *p1 = a;
    const student *p2 = b;
    return p1->id - p2->id;
}

int compare_surname(const void *a, const void *b)
{
    const student *p1 = a;
    const student *p2 = b;
    return strcmp(p1->surname, p2->surname);
}

int compare_name(const void *a, const void *b)
{
    const student *p1 = a;
    const student *p2 = b;
    return strcmp(p1->name, p2->name);
}

int compare_group(const void *a, const void *b)
{
    const student *p1 = a;
    const student *p2 = b;
    return strcmp(p1->group, p2->group);
}

int is_int(char *str)
{
    for(int i = 0; str[i] != '\0'; i++){
        if(!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}

int menu(student *res, int student_size)// не работает scan_stdin
{
    int option = 0, parameter = 0, searched_size = 0;
    int flag = CORRECT;
    int search_year = 0;
    char *word, *tmp;
    int scan = 0;
    student *searched;

    printf("\n1) Search students by parameter\n");
    printf("2) Sort students by parameter\n");
    printf("Choose the option: ");
    flag = scan_stdin(&tmp);
    if(flag == MEMORY_ERROR)
        return MEMORY_ERROR;
    if(is_int(tmp))
        option = atoi(tmp);
    free(tmp);

    if(option == 1){

        printf("By what parameter do you want to make a search?\n");
        printf("1) Surname\n");
        printf("2) Year\n");
        printf("3) Group\n");
        printf("Choose parameter: ");
        flag = scan_stdin(&tmp);
        if(flag == MEMORY_ERROR)
            return MEMORY_ERROR;
        if(is_int(tmp))
            parameter = atoi(tmp);
        free(tmp);
        

        if(parameter == 1){

            printf("Enter parameter:\n");
            flag = scan_stdin(&word);
            if(flag == MEMORY_ERROR)
                return MEMORY_ERROR;

            searched = search_parameter(res, student_size, parameter, &flag, &searched_size, word, search_year);
            if(flag != CORRECT){
                free(word);
                return flag;
            }
            if(searched_size == 0)
                printf("No such student\n");

        } else if(parameter == 2){

            printf("Enter parameter:\n");
            if(scanf("%d", &search_year) != 1){
                return WRONG_MENU_TASK;
            }

            searched = search_parameter(res, student_size, parameter, &flag, &searched_size, word, search_year);
            if(flag != CORRECT){
                return flag;
            }
            if(searched_size == 0)
                printf("No such student\n");

        } else if(parameter == 3){

            printf("Enter parameter:\n");
            flag = scan_stdin(&word);
            if(flag == MEMORY_ERROR)
                return MEMORY_ERROR;
            
            searched = search_parameter(res, student_size, parameter, &flag, &searched_size, word, search_year);
            if(flag != CORRECT){
                free(word);
                return flag;
            }
            if(searched_size == 0)
                printf("No such student\n");

        } else{
            return WRONG_MENU_TASK;
        }

        print_student_just(searched, searched_size);
        free(searched);

    } else if(option == 2){

        printf("By what parameter do you want to sort?\n");
        printf("1) ID\n");
        printf("2) Surname\n");
        printf("3) Name\n");
        printf("4) Group\n");
        printf("Choose parameter: ");
        scan = scanf("%d", &parameter);
        if(scan != 1){
            return WRONG_MENU_TASK;
        }

        if(parameter == 1){

            qsort(res, student_size, sizeof(student), compare_id);

        } else if(parameter == 2){

            qsort(res, student_size, sizeof(student), compare_surname);

        } else if(parameter == 3){

            qsort(res, student_size, sizeof(student), compare_name);

        } else if(parameter == 4){

            qsort(res, student_size, sizeof(student), compare_group);

        } else{
            return WRONG_MENU_TASK;
        }
        print_student_just(res, student_size);

    } else{

        return WRONG_MENU_TASK;

    }

    return CORRECT;
}

student **group_students(student *studs, int stud_size, int *group_sizes, int *flag)
{
    student **res;
    int idx_1 = 0, idx_2 = 0, idx_3 = 0, idx_4 = 0;
    res = (student**)malloc(sizeof(student*) * 4);
    if(!res){
        *flag = MEMORY_ERROR;
        return NULL;
    }

    for(int i = 0; i < stud_size; i++){
        if(studs[i].course == 1)
            group_sizes[0] += 1;
        else if(studs[i].course == 2)
            group_sizes[1] += 1;
        else if(studs[i].course == 3)
            group_sizes[2] += 1;
        else if(studs[i].course == 4)
            group_sizes[3] += 1;
    }

    for(int i = 0; i < 4; i++){
        res[i] = (student*)malloc(sizeof(student) * group_sizes[i]);
        if(res[i] == NULL){
            *flag = MEMORY_ERROR;
            for(int j = 0; j < i; j++){
                free(res[i]);
            }
            free(res);
            return NULL;
        }
    }

    for(int i = 0; i < stud_size; i++){

        if(studs[i].course == 1){
            res[0][idx_1] = studs[i];
            idx_1++;
        } else if(studs[i].course == 2){
            res[1][idx_2] = studs[i];
            idx_2++;
        } else if(studs[i].course == 3){
            res[2][idx_3] = studs[i];
            idx_3++;
        } else if(studs[i].course == 4){
            res[3][idx_4] = studs[i];
            idx_4++;
        }

    }

    return res;
}

void print_grouped_studs(student **res, int *sizes)
{
    printf("\n");
    for(int i = 0; i < 4; i++){
        printf("Year %d:\n", i + 1);
        for(int j = 0; j < sizes[i]; j++){
            printf("ID:%d | SURNAME:%s | NAME:%s | YEAR:%d | GROUP:%s | MARKS:", res[i][j].id, res[i][j].surname, res[i][j].name, res[i][j].course, res[i][j].group);
            for(int k = 0; k < 5; k++){
                printf("%.0lf ", res[i][j].marks[k]);
            }
            printf("\n");
        }
    }
}

void make_filename(char *res, int filenum, char *filename)
{
    strcat(res, filename);
    char *txt = ".txt\0";
    int i = 0;
    while(res[i] != '.'){
        i++;
    }
    res[i] = '_';
    res[i + 1] = 48 + filenum;
    res[i + 2] = '\0';
    strcat(res, txt);
}

int check_avg(double *marks, double eps)
{
    double total = 0.0;
    for(int i = 0; i < 5; i++){
        total += marks[i];
    }
    double res = total / 5.0;
    if(res > 3.5 && fabs(res - 3.5) > eps){
        return 1;
    }
    return 0;
}

void write_one_file(char *filename, student *res, int size, double eps)
{
    FILE *fout = NULL;
    fout = fopen(filename, "w");
    for(int i = 0; i < size; i++){
        if(!check_avg(res[i].marks, eps)){
            continue;
        }
        
        fprintf(fout, "%s %s %d %s ", res[i].surname, res[i].name, res[i].course, res[i].group);
        for(int j = 0; j < 5; j++){
            fprintf(fout, "%.0lf ", res[i].marks[j]);
        }
        fprintf(fout, "\n");
    }

    fclose(fout);
}

int output_in_files(student **grouped, char *filename, int *group_sizes, double eps)
{
    int flag = CORRECT;
    int filelen = strlen(filename) + 2;
    char *file1, *file2, *file3, *file4;
    file1 = (char*)malloc(sizeof(char) * (filelen + 1));
    if(!file1)
        return MEMORY_ERROR;
    file2 = (char*)malloc(sizeof(char) * (filelen + 1));
    if(!file2){
        free(file1);
        return MEMORY_ERROR;
    }
    file3 = (char*)malloc(sizeof(char) * (filelen + 1));
    if(!file3){
        free(file1);
        free(file2);
        return MEMORY_ERROR;
    }
    file4 = (char*)malloc(sizeof(char) * (filelen + 1));
    if(!file4){
        free(file1);
        free(file2);
        free(file3);
        return MEMORY_ERROR;
    }

    make_filename(file1, 1, filename);
    make_filename(file2, 2, filename);
    make_filename(file3, 3, filename);
    make_filename(file4, 4, filename);

    write_one_file(file1, grouped[0], group_sizes[0], eps);
    write_one_file(file2, grouped[1], group_sizes[1], eps);
    write_one_file(file3, grouped[2], group_sizes[2], eps);
    write_one_file(file4, grouped[3], group_sizes[3], eps);

    free(file1);
    free(file2);
    free(file3);
    free(file4);
    return CORRECT;
}

int main(int argc, char *argv[])
{
    if(argc == 1){
        printf("No arguments!\n");
        return ARGS_ERROR;
    } else if(argc > 2){
        printf("Enter only the file name!\n");
        return ARGS_ERROR;
    }

    double eps = 0.0000001;
    int flag = CORRECT;
    int student_size = 0;
    student *res;
    flag = fill_struct_student(&res, argv[1], &student_size, eps);
    if(flag == NO_FILE){
        printf("Couldn't open the file!\n");
        return NO_FILE;
    } else if(flag == MEMORY_ERROR){
        printf("Memory wasn't allocated!\n");
        return MEMORY_ERROR;
    } else if(flag == WRONG_INFO_AMOUNT){
        printf("Incorrect number of values in one string!(File Error)\n");
        return WRONG_INFO_AMOUNT;
    } else if(flag == WRONG_NAME_SURNAME){
        printf("Incorrect name or surname!(File Error)\n");
        return WRONG_NAME_SURNAME;
    } else if(flag == WRONG_COURSE){
        printf("Incorrect year!(File Error)\n");
        return WRONG_COURSE;
    } else if(flag == WRONG_GROUP){
        printf("Incorrect group!(File Error)\n");
        return WRONG_GROUP;
    } else if(flag == WRONG_MARKS){
        printf("Incorrect marks!(File Error)\n");
        return WRONG_MARKS;
    }

    print_student_avg(res, student_size);

    flag = menu(res, student_size);
    if(flag == MEMORY_ERROR){
        free_student(res, student_size);
        printf("Memory wasn't allocated!\n");
        return MEMORY_ERROR;
    } else if(flag == WRONG_NAME_SURNAME){
        free_student(res, student_size);
        printf("Incorrect name or surname!\n");
        return WRONG_NAME_SURNAME;
    } else if(flag == WRONG_COURSE){
        free_student(res, student_size);
        printf("Incorrect year!\n");
        return WRONG_COURSE;
    } else if(flag == WRONG_GROUP){
        free_student(res, student_size);
        printf("Incorrect group!\n");
        return WRONG_GROUP;
    } else if(flag == WRONG_MENU_TASK){
        free_student(res, student_size);
        printf("Incorrect menu task!\n");
        return WRONG_MENU_TASK;
    }

    student **grouped;
    int *group_sizes;
    group_sizes = (int*)malloc(sizeof(int) * 4);
    if(!group_sizes){
        free_student(res, student_size);
        printf("Memory wasn't allocated!\n");
        return MEMORY_ERROR;
    }
    for(int i = 0; i < 4; i++){
        group_sizes[i] = 0;
    }
    grouped = group_students(res, student_size, group_sizes, &flag);
    if(flag == MEMORY_ERROR){
        free_student(res, student_size);
        printf("Memory wasn't allocated!\n");
        return MEMORY_ERROR;
    }
    print_grouped_studs(grouped, group_sizes);
    flag = output_in_files(grouped, argv[1], group_sizes, eps);
    if(flag == MEMORY_ERROR){
        free(grouped);
        free_student(res, student_size);
        printf("Memory wasn't allocated!\n");
        return MEMORY_ERROR;
    }

    free(grouped);
    free_student(res, student_size);
    return 0;
}