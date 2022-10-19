#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fin, *fout;
    char str1[100], str2[100], str3[100];
    if(argc == 1){
        printf("No arguments!\n");
        return 0;
    } else if(argc > 2){
        printf("Too many arguments!\n");
        return 0;
    }

    fin = fopen(argv[1], "r");
    if(!fin){
        printf("Can't open the file!\n");
        return 0;
    }
    fout = fopen("tempfile.txt", "w");

    while(fscanf(fin, "%s%s%s", str1, str2, str3) != EOF){
        fprintf(fout, "%s %s %s\n", str3, str1, str2);
    }

    fclose(fin);
    fclose(fout);
    fin = fopen(argv[1], "w");
    fout = fopen("tempfile.txt", "r");
    fclose(fin);
    fclose(fout);
    remove(argv[1]);
    rename("tempfile.txt", argv[1]);
    printf("Done\n");
    return 0;
}
