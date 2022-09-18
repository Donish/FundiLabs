#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void argum_i(FILE* f1, FILE* f2)
{
    long long int counter = 0;
    char c;
    while((c = getc(f1)) != EOF){
        if(c == '\n'){
            fprintf(f2, "%lld\n", counter);
            counter = 0;
        }
        if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
            counter += 1;
        }
    }
    fprintf(f2, "%lld", counter);
}

void argum_d(FILE* f1, FILE* f2)
{
    char c;
    while((c = getc(f1)) != EOF){
        if(c < 48 || c > 57){
            putc(c, f2);
        }
    }
}

void argum_s(FILE* f1, FILE* f2)
{
    long long int counter = 0;
    char c;
    while((c = getc(f1)) != EOF){
        if(!((c > 47 && c < 58) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == ' ' || c == '\n' || c == ' ' || c == '\t')){
            counter += 1;
        }
        if(c == '\n'){
            fprintf(f2, "%lld\n", counter);
            counter = 0;
        }
    }
    fprintf(f2, "%lld", counter);
}

void argum_a(FILE* f1, FILE* f2)
{
    char c;
    int num = 0;
    while((c = getc(f1)) != EOF){
        if(c == '\n' || c == ' ' || c == '\t'){
            putc(c, f2);
            continue;
        }
        if(c < 48 || c > 57){
            num = c;
            fprintf(f2, "%d", num);
        } else{
            putc(c, f2);
        }
    }
}

void argum_f(FILE* f1, FILE* f2)
{
    char c;
    char _c;
    int num = 0;
    int counter = 0;
    while((c = getc(f1)) != EOF){
        if((c >= 65 && c <= 90 || c >= 97 && c <= 122) && !(_c >= 65 && _c <= 90 || _c >= 97 && _c <= 122)){
            counter += 1;
            if(counter % 2 == 0 && counter % 5 == 0){
                while(c >= 65 && c <= 90 || c >= 97 && c <= 122){
                    putc(tolower(c), f1);
                    num = c;
                    fprintf(f2, "%d", num);
                    _c = c;
                    c = getc(f1);
                }
                putc(c, f2);
                continue;
            }
            if(counter % 2 == 0){
                while(c >= 65 && c <= 90 || c >= 97 && c <= 122){
                    putc(tolower(c), f2);
                    _c = c;
                    c = getc(f1);
                }
                putc(c, f2);
                continue;
            } else if(counter % 5 == 0){
                while(c >= 65 && c <= 90 || c >= 97 && c <= 122){
                    num = c;
                    fprintf(f2, "%d", num);
                    _c = c;
                    c = getc(f1);
                }
                putc(c, f2);
                continue;
            }
        }
        putc(c, f2);
        _c = c;
    }
}

void copy_file(FILE* f1, FILE* f2)
{
    char c;
    while((c = getc(f2)) != EOF){
        putc(c, f1);
    }
}

int main(int argc, char* argv[])
{
    // объявление всего нужного(псевдоглобального)
    FILE *fin, *fout;
    if(argc == 1){
        printf("No arguments!\n");
        return 0;
    }
    fin = fopen(argv[2], "r");
    if(!fin){
        printf("Can't open the file!\n");
        return 0;
    }
    char first[100] = "out_";
    char* filename = strcat(first, argv[2]);
    char c;
    // выполнение флагов
    if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "/d") == 0){ // -d

        if(argc != 3){
            printf("Enter only the way to the file with flag '-d'!\n");
            return 0;
        }
        fout = fopen("tempfile.txt", "w");
        argum_d(fin, fout);
        fclose(fin);
        fclose(fout);
        fin = fopen(argv[2], "w");
        fout = fopen("tempfile.txt", "r");
        copy_file(fin, fout);
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-nd") == 0 || strcmp(argv[1], "/nd") == 0){

        if(argc == 4){
            fout = fopen(argv[3], "w");
            argum_d(fin, fout);
        } else if(argc == 3){
            fout = fopen(filename, "w");
            argum_d(fin, fout);
        } else{
            printf("You can enter extra filename with flag 'n' like this:\n'*.exe -n* file.txt extrafile.txt'!\n");
            return 0;
        }
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "/i") == 0){ // -i

        if(argc != 3){
            printf("Enter only the way to the file with flag '-i'!\n");
            return 0;
        }
        fout = fopen("out.txt", "w");
        argum_i(fin, fout);
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-ni") == 0 || strcmp(argv[1], "/ni") == 0){

        if(argc == 4){
            fout = fopen(argv[3], "w");
            argum_i(fin, fout);
        } else if(argc == 3){
            fout = fopen(filename, "w");
            argum_i(fin, fout);
        } else{
            printf("You can enter extra filename with flag 'n' like this:\n'*.exe -n* file.txt extrafile.txt'!\n");
            return 0;
        }
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "/s") == 0){

        if(argc != 3){
            printf("Enter only the way to the file with flag '-s'!\n");
            return 0;
        }
        fout = fopen("out.txt", "w");
        argum_s(fin, fout);
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-ns") == 0 || strcmp(argv[1], "/ns") == 0){

        if(argc == 4){
            fout = fopen(argv[3], "w");
            argum_s(fin, fout);
        } else if(argc == 3){
            fout = fopen(filename, "w");
            argum_s(fin, fout);
        } else{
            printf("You can enter extra filename with flag 'n' like this:\n'*.exe -n* file.txt extrafile.txt'!\n");
            return 0;
        }
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "/a") == 0){

        if(argc != 3){
            printf("Enter only the way to the file with flag '-a'!\n");
            return 0;
        }
        fout = fopen("tempfile.txt", "w");
        argum_a(fin, fout);
        fclose(fin);
        fclose(fout);
        fin = fopen(argv[2], "w");
        fout = fopen("tempfile.txt", "r");
        copy_file(fin, fout);
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-na") == 0 || strcmp(argv[1], "/na") == 0){

        if(argc == 4){
            fout = fopen(argv[3], "w");
            argum_a(fin, fout);
        } else if(argc == 3){
            fout = fopen(filename, "w");
            argum_a(fin, fout);
        } else{
            printf("You can enter extra filename with flag 'n' like this:\n'*.exe -n* file.txt extrafile.txt'!\n");
            return 0;
        }
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "/f") == 0){

        if(argc != 3){
            printf("Enter only the way to the file with flag '-f'!\n");
            return 0;
        }
        fout = fopen("out.txt", "w");
        argum_f(fin, fout);
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else if(strcmp(argv[1], "-nf") == 0 || strcmp(argv[1], "/nf") == 0){

        if(argc == 4){
            fout = fopen(argv[3], "w");
            argum_f(fin, fout);
        } else if(argc == 3){
            fout = fopen(filename, "w");
            argum_f(fin, fout);
        } else{
            printf("You can enter extra filename with flag 'n' like this:\n'*.exe -n* file.txt extrafile.txt'!\n");
            return 0;
        }
        fclose(fin);
        fclose(fout);
        printf("Done\n");
        return 0;

    } else{
        printf("Wrong flag!\n");
        return 0;
    }
}
