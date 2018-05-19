#include<stdio.h>

int getint()
{
    int n;
    char ch;
    printf("\n        Enter n = ");
    while((scanf("%d%c",&n,&ch))!=2 || ch!='\n' || n>15 || n<0 )
    {
        printf("        Input error,please enter number between 0-15");
        printf("\n\n        Enter n = ");
        rewind(stdin);

    }

    return n;
}

int fact(int n,int count)
{
    int ans;
    if(n!=0)
    {
        printf("\n          %d! is recursive case.Answer = %d * recursion of %d!\n",n,n,n-1);
        printf("\n                  Recursion to calculate %d!",n-1);
        ans = n*fact(n-1,count);
        if(n!=count)
        {
            printf("\n\n          Calculate %d! complete.\n",n);
            printf("\n              Return answer from %d! = %d to calculate %d! = [%d * %d!] = %d * %d = %d",n,ans,n+1,n+1,n,n+1,ans,(n+1)*ans);
        }
        return ans;

    }
    else
    {
        printf("\n          %d! is base case return answer %d! = 1",n,n);
        printf("\n\n          Calculate %d! complete.\n",n);
        printf("\n              Return answer from %d! = %d to calculate %d! = [%d * %d!] = %d * %d = %d",n,1,n+1,n+1,n,n+1,1,(n+1)*1);
        return 1;
    }
}

int main()
{
    int n,ans;
    char con;

    do
    {
        system("cls");
        rewind(stdin);
        printf("\n     :: My Recursion Program. ::\n");
        printf("\n     :: Program calculate n! by recursion (n<=15) ::\n");

        n=getint();

        ans=fact(n,n);
        printf("\n\n        Complete calculate of %d!,answer is %d",n,ans);

        printf("\n\n        press [y] to continue, other to exit.");
        scanf("%c",&con);

    }
    while(con=='y');

    printf("\n\n      End Program.");
    printf("\n      Program written by 60070501077 Charnsak Dangmanee\n\n");

}


