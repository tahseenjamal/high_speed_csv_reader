#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char **argv)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t length;
    bool header = true;
    char delim[] = "|";
    struct tm tm;

    memset(&tm, 0, sizeof(struct tm));

    char *token = NULL;

    fp = fopen(argv[1], "r");

    if (fp == NULL)

        exit(EXIT_FAILURE);

    while ((length = getline(&line, &len, fp)) != -1) {
    
        token = strtok(line,delim);

        char data[10][32];

        unsigned char column = 0;

        while(token != NULL && !header ) {

            char *p = strchr(token,'\n');

            if(p) *p = '\0';

            switch(column) {

                case 0:

                    strptime(token, "%Y-%m-%d %H:%M:%S", &tm);

                    sprintf(data[column],"timestamp of colum 1: %lld",mktime(&tm)*1000LL);

                    break;


                case 1:
                    
                    sprintf(data[column],"data of column 2: %s",token);

                    break;


                default:
                    
                    sprintf(data[column],"%s",token);
            }



            column++;


            /*printf("%s\n",token);*/

            token = strtok(NULL,delim);
        }

        printf("%s,%s\n",data[1],data[0]);

        /*if(!header) printf("\n");*/

        header = false;          

    }

    fclose(fp);

    if (line)

        free(line);

    exit(EXIT_SUCCESS);
}


