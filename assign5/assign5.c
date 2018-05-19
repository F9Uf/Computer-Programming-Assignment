#include<stdio.h>
#include<string.h>

void AddSpace(char *str)
{
    char buff[255] = "", old[255]="";
    int i, j;

    for(i=0,j=strlen(str); i<j; i++)
    {
        if(strchr("!+-*/^()",str[i])!=NULL)
        {
            sprintf(buff,"%s %c ",old,str[i]);
        }
        else
        {
            sprintf(buff,"%s%c",old,str[i]);
        }
        strcpy(old,buff);
    }
    strcpy(str,buff);
}


int CutWord(char word[][10],char *str)
{
    char *token;
    int count=0;
    token=strtok(str," ");
    while(token!=NULL)
    {
        strcpy(word[count++],token);
        token=strtok(NULL," ");
    }
    return count;
}
int checkNum(char *s)
{
    double num;
    char ch;

    if(sscanf(s,"%lf%c",&num,&ch)==1)
    {
        return num;
    }
    else
    {
        return -1;
    }
}
int checkFuction(char *st){
    if(strcmp(st,"sin")==0) return 6;
    else if(strcmp(st,"cos")==0) return 7;
    else if(strcmp(st,"tan")==0) return 8;
    else if(strcmp(st,"asin")==0) return 9;
    else if(strcmp(st,"acos")==0) return 10;
    else if(strcmp(st,"atan")==0) return 11;
    else if(strcmp(st,"sqrt")==0) return 12;
    else if(strcmp(st,"log")==0) return 13;
    else if(strcmp(st,"exp")==0) return 14;
    else if(strcmp(st,"abs")==0) return 15;
    else  return 0;
}
int checkType(char *st)
{
    if(checkNum(st)>=0){
        return 1;
    }else if(strcmp(st,"-")==0){
        return 2;
    }else if(strcmp(st,"+")==0 || strcmp(st,"*")==0 || strcmp(st,"/")==0 || strcmp(st,"^")==0){
        return 3;
    }else if(strcmp(st,")")==0){
        return 4;
    }else if(strcmp(st,"(")==0){
        return 5;
    }else if(checkFuction(st)>=6){
        return checkFuction(st);
    }else return 0;
}
int checkInfix(char word[][40],int count)
{

    int i,check=-1;

    for(i=0; i<count && check<=0; i++)
    {
        if(checkType(word[i])==1){
            check=checkType(word[i]);
            printf("%d\n",check);
        }

    }

    return check;


}
int main()
{
    char text[100],str[100];
    char word[100][10];
    double num[100];
    int count,end=0,i,check;

    do
    {
        printf(" command> ");
        gets(str);
        if(strcmp(str,"end")==0)
        {
            end++;
        }
        else
        {
            strlwr(str);
            AddSpace(str);
            count=CutWord(word,str);

            check = checkInfix(word,count);
           //printf("check: %d\n",check);

            printf(" answer> ");
            for(i=0;i<count;i++){
                printf("%s ",word[i]);
            }

            printf("\n\n");
        }



        //printf(" %d\n",count);
    }
    while(end==0);


}
