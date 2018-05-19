#include<stdio.h>
#include<string.h>

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
int checkcommand(char *command,char word[][40])
{
    int count,i,j,err=0;
    int number[10];
    char ch;
    count=cutword(command,word);

    if(strcmp(word[0],"list")==0 || strcmp(word[0],"sort")==0 || strcmp(word[0],"pop")==0 || strcmp(word[0],"end")==0){
        if(count==1)
        {
            return 1;
        }else
        {
            return 0;
        }
    }else if(strcmp(word[0],"delete")==0 || strcmp(word[0],"insert")==0 || strcmp(word[0],"search")==0 || strcmp(word[0],"push")==0 || strcmp(word[0],"peek")==0 )
    {
        if(count==2)
        {
            if(sscanf(word[1],"%d%c",&number[0],&ch)==1) {
               return 1;
            }else
            {
                return 0;
            }



        }else
        {
            return 0;
        }
    }else if(strcmp(word[0],"add")==0)
    {
        if(count>=2)
        {

            for(i=1,j=0;i<count; )
            {
                if(sscanf(word[i],"%d%c",&number[j],&ch)==1)
                {
                        i++;
                }else
                {
                        err++;
                        i++;
                }
            }

            if(err==0)
            {
                return 1;
            }else
            {
                return 0;
            }

        }else
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }

}

int main()
{
    int end=0;
    do
    {
        rewind(stdin);
        int check=0;
        char command[1000];
        char word[10][40];
        printf(" command> ");
        gets(command);
        strlwr(command);
        check=checkcommand(command,word);

        if(check==0)
        {
            printf(" answer> parameter error\n");
        }else if(check==1)
        {
            printf(" answer> ok\n");
            if(strcmp(word[0],"end")==0) end=1;
        }else
        {
            printf(" answer> syntax error\n");
        }

    }while(end!=1);

    printf("\n End program\n");
    printf(" program written by 60070501077 Charnsak Dangmanee\n");

}
