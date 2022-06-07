#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

char *read_file(char *filename);
void split(char *file_contents);

int main()
{
    setlocale(LC_ALL, "Turkish");
    char filename[1024];
    printf("Dosya: ");
    scanf("%s", filename);

    char *file_contents = read_file(filename);
    if(file_contents == NULL){
        printf("Dosya okunamadi.\n");
        return 1;
    }
    printf("Dosya icerigi: \n\n%s\n", file_contents);


    split(file_contents);

    free(file_contents);

    return 0;
}

char *read_file(char *filename){
    FILE *file;

    file = fopen(filename,"r");
    if(file == NULL){
        return NULL;
        }

    fseek(file, 0 , SEEK_END);
    int length = ftell(file);
    fseek(file, 0 , SEEK_SET);

    char *string = malloc(sizeof(char)*(length+1));

    char c;
    int i= 0;
    while( (c = fgetc(file)) != EOF){
            string[i] = c;
            i++;

    }
    string[i] = '\0';
    return string;

}

void split(char *file_contents){
    int level = 0;
    char* ayrac1= "\n";
    char* ptr;
    char* forara = "for";
    char* kapanisparantez = "}";
    int icicedongusayac = 0;
    int enbuyukcdc = 0;
    char* whileara ="while";
    char* cross = "*";
    char* divide = "/";
    int cdcount = 0;
    char* ifara = "if";
    char* elseara = "else";

    ptr = strtok(file_contents,ayrac1);
    while(ptr != NULL){
       char *kapanis = strstr(ptr,kapanisparantez);
       //printf("%s\n",ptr);
       char *forvar = strstr(ptr,forara);
       char *whilevar = strstr(ptr,whileara);
       char *crossvar = strstr(ptr,cross);
       char *dividvar = strstr(ptr,divide);
       char *ifvar = strstr(ptr,ifara);
       char *elsevar= strstr(ptr,elseara);

        if(kapanis){
            if(level>0)
            level--;
            if(cdcount>0)
            cdcount--;
            }

        if(ifvar)
            level++;
        if(elsevar)
            level++;

        if(forvar){

        level++;


        if(crossvar)
            cdcount++;
        if(dividvar)
            cdcount++;
        if(level>=icicedongusayac)
            icicedongusayac=level;
        if(cdcount>=enbuyukcdc)
            enbuyukcdc=cdcount;
        }

        if(whilevar){

        level++;

        if(crossvar)
            cdcount++;
        if(dividvar)
            cdcount++;
        if(level>=icicedongusayac)
            icicedongusayac=level;
        if(cdcount>=enbuyukcdc)
            enbuyukcdc=cdcount;
        }

        ptr = strtok(NULL,ayrac1);
    }

    if(icicedongusayac==0)
    printf("Zaman Karmasýklýgý = O(1)\n");
    else if(enbuyukcdc>0){
        if(enbuyukcdc>=icicedongusayac){
            printf("Zaman Karmasýklýgý = O(logn^%d) \n",icicedongusayac);
        }
        else{
            int dif = icicedongusayac-enbuyukcdc;
            printf("Zaman Karmasýklýgý = O(logn^%d*n^%d)\n",enbuyukcdc,dif);
        }

    }
    else {
    printf("Zaman Karmasýklýgý = O(n^%d) \n",icicedongusayac);

    }

}


