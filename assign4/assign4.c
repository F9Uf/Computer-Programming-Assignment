#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int cutword(char *command,char word[][40])
{
    char *token;
    int count=0;
    token=strtok(command," ");
    while(token!=NULL)
    {
        strcpy(word[count++],token);
        token=strtok(NULL," ");
    }
    return count;
}

int main(){

    int end =0;
    do{
            rewind(stdin);
            int count=0;
            char command[100];
            char word[10][10];

            printf("\n command> ");
            gets(command);
            strlwr(command); //แปลงเป็นตัวเล็ก
            count=cutword(command,word); //ตัดคำ

            if(strcmp(word[0],"peek")==0 || strcmp(word[0],"delete")==0 || strcmp(word[0],"push")==0 || strcmp(word[0],"pop")==0){

                //ทำ function 1 พารา
            }else if( strcmp(word[0],"pop")==0 || strcmp(word[0],"help")==0 || strcmp(word[0],"end")==0 ){

            }else if( strcmp(word[0],"add")==0 ){

            }else if( strcmp(word[0],"sqrt")==0 || strcmp(word[0],"rec")==0 || strcmp(word[0],"neg")==0){

            }else if( strcmp(word[0],"+")==0 || strcmp(word[0],"-")==0 || strcmp(word[0],"*")==0 || strcmp(word[0],"/")==0 || strcmp(word[0],"pow")==0){

            }else {
                printf("\n answer> ");
            }

    }while(end==0);
    return 0;
}




