#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct node_type
{
    double info;
    struct node_type *next;
} linkedlist;

linkedlist *first=NULL,*last=NULL;

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

void printList()
{
    linkedlist *ptr;
    int count=0;
    ptr=first;
    if(first==NULL) printf(" NULL\n");
    else
    {
        while(ptr!=NULL)
        {
            printf("%g ",ptr->info);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void addData(double item)
{
    linkedlist *ptr;
    ptr = (linkedlist*)malloc(sizeof(linkedlist));
    ptr->next = NULL;
    ptr->info = item;

    if(first == NULL)
    {
        first=last=ptr;
    }
    else
    {
        last->next = ptr;
        last = ptr;
    }
}

void sortData()
{
    linkedlist *ptrI,*ptrJ;
    double x;
    ptrI=first;
    while(ptrI->next != NULL)
    {
        ptrJ=ptrI->next;
        while(ptrJ!=NULL)
        {
            if(ptrJ->info < ptrI->info)
            {
                x=ptrI->info;
                ptrI->info=ptrJ->info;
                ptrJ->info=x;
            }
            ptrJ=ptrJ->next;
        }
        ptrI=ptrI->next;
    }
}

void popData()
{
    double x = first->info;
    printf(" answer> %g\n",x);
    first=first->next;

}

void pushData(double num)
{
    linkedlist *ptr;
    ptr = (linkedlist*)malloc(sizeof(linkedlist));

    ptr->info = num;
    ptr->next = first;
    first = ptr;
}

void peekData(int n)
{
    linkedlist *ptr;
    int count=0;
    ptr = first;

    if(first==NULL){
        printf(" answer> no data\n");
    }else{
        if(n == -1){
            printf(" answer> %g\n",last->info);
        }else if(n==0){
            printf(" answer> %g\n",first->info);
        }
        else{
            while((ptr!=NULL) && count<n){
                    ptr=ptr->next;
                    count++;
            }
            if(ptr==NULL) printf(" answer> Maximum peek = %d\n",count-1);
            else printf(" answer> %g\n",ptr->info);
        }
    }
}

int checkSort(){
	linkedlist *ptr;
	ptr = first;
	int err=0;
	if(first==NULL){
		return 0; //no data but can insert
	}else{
		while((ptr!=NULL) && err==0){


			if(ptr!=last){
				if((ptr->info) > (ptr->next)->info){
					err++;
				}
			}

			ptr=ptr->next;
		}

		if(ptr!=NULL){
			return -1; // not sort
		}else{
			return 1;// sorted
		}
	}
}

void insertData(double item){
	linkedlist *ptr,*newNode;


	newNode=(linkedlist*)malloc(sizeof(linkedlist));

	newNode->info = item;
	newNode->next = NULL;

	if(first==NULL){
		first=last=newNode;  // no data
	}else if(first->info > newNode->info){  // new data < first
		newNode->next = first;
		first=newNode;
	}else{
		ptr = first;
		while((ptr->next)!=NULL && ((ptr->next)->info < newNode->info ) ){
			ptr = ptr->next;
		}

		newNode->next = ptr->next;
		ptr->next = newNode;

		if(ptr==last){
			last = newNode;
		}
	}
}

void deleteData(double item){
	linkedlist *ptr,*nxt;
	char ch;
	int found=0;

	ptr = first;
	nxt = ptr->next;

	if(first->info == item){
		printf(" answer> %g found enter Y to comfirm ",item);
		scanf("%c",&ch);
		if(ch=='Y' || ch=='y'){
			first=first->next;
			rewind(stdin);
		}

		deleteData(item);


	}else{
		while(nxt!=NULL){
			rewind(stdin);
			if(nxt->info == item){
				printf(" answer> %g found enter Y to comfirm ",item);
				scanf("%c",&ch);
				found++;

				if(ch=='Y'||ch=='y'){
					if(nxt==last){
						last=ptr;

					}
					ptr->next = nxt->next;
				}

			}else{
                nxt=nxt->next;
                ptr=ptr->next;
			}



		}

//		if(nxt!=NULL){
//			if(nxt==last){
//				last=ptr;
//			}
//			ptr->next = nxt->next;
//		}else{
//			printf(" answer> not found\n");
//		}

	}

	if(found<=0) printf(" answer> %g not found\n",item);
}

void deleteData2(double item){
    linkedlist *ptr,*nxt;
	char ch;
	int found=0;

	ptr = first;
	nxt = ptr->next;

	if(last==first){
        if(ptr->info == item){
            printf(" answer> %g found enter Y to comfirm ",item);
            scanf("%c",&ch);
            found++;
            if(ch=='Y' || ch=='y'){
                first=first->next;

            }
            rewind(stdin);
        }
	}else{
	while(nxt!=NULL){
        if(first->info == item){
            printf(" answer> %g found enter Y to comfirm ",item);
            scanf("%c",&ch);
            found++;
            if(ch=='Y' || ch=='y'){
                first=first->next;

            }
            rewind(stdin);
        }else{
            if(nxt->info == item){
                found++;
                printf(" answer> %g found enter Y to comfirm ",item);
                scanf("%c",&ch);
                if(ch=='y'||ch=='Y'){
                    if(nxt==last){
                        last=ptr;
                    }
                    ptr->next = nxt->next;


                }
                rewind(stdin);
            }
        }
        ptr=nxt;
        nxt=nxt->next;
	}
	}
	if(found<=0) printf(" answer> not found\n");
}

void operatorData(char *command){
    linkedlist *ptr;
    double one,two,result;


    if(first==NULL){
        printf(" answer> no data\n");
    }else if(last==first){
        printf(" answer> can't operator\n");
    }else{
        one = (first->info);
        two = (first->next)->info ;

        if(strcmp(command,"+")==0){
            result=two+one;
            first=first->next;
            first->info = result;
            printf(" answer> %g\n",result);
        }else if(strcmp(command,"-")==0){
            result=two-one;
            first=first->next;
            first->info = result;
            printf(" answer> %g\n",result);
        }else if(strcmp(command,"*")==0){
            result=two*one;
            first=first->next;
            first->info = result;
            printf(" answer> %g\n",result);
        }else if(strcmp(command,"/")==0){
            if(one==0){
                printf(" answer> can't divide by 0\n");
            }else{
                result=two/one;
                first=first->next;
                first->info = result;
                printf(" answer> %g\n",result);
            }

        }else{
            result=pow(two,one);
            first=first->next;
            first->info = result;
            printf(" answer> %g\n",result);
        }
    }
}

int checkcommand(char *command,char word[][40])
{
    int count,i,j,err=0;
    double number[10];
    char ch;
    int num,checksort;
    count=cutword(command,word);

    if(strcmp(word[0],"list")==0 || strcmp(word[0],"sort")==0 || strcmp(word[0],"pop")==0 || strcmp(word[0],"end")==0 ||  strcmp(word[0],"help")==0)
    {
        if(count==1)
        {
            if(strcmp(word[0],"sort")==0)
            {
                if(first==NULL) printf(" answer> no data\n");
                else  sortData();
            }
            else if(strcmp(word[0],"pop")==0)
            {
                if(first==NULL) printf(" answer> no data\n");
                else popData();
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(strcmp(word[0],"delete")==0 || strcmp(word[0],"insert")==0 || strcmp(word[0],"search")==0 || strcmp(word[0],"push")==0 || strcmp(word[0],"peek")==0 )
    {
        if(count==2)
        {
            if(sscanf(word[1],"%d%c",&num,&ch)==1 && strcmp(word[0],"peek")==0)
            {
                peekData(num);
                return 1;
            }
            else if(sscanf(word[1],"%lf%c",&number[0],&ch)==1)
            {


                if(strcmp(word[0],"delete")==0)
                {
                	if(first!=NULL)
						deleteData2(number[0]);
					else printf(" answer> no data\n");
                }
                else if(strcmp(word[0],"push")==0)
                {
                    pushData(number[0]);

                }else if(strcmp(word[0],"insert")==0){
                	checksort=checkSort();
                	if(checksort==0) {
//                		printf(" answer> no data\n");
						insertData(number[0]);
					}
                	else if (checksort==1){
                		insertData(number[0]);

                	}else printf(" answer> can't insert please sorted before\n");

				}else if(strcmp(word[0],"delete")==0){

				}

                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else if(strcmp(word[0],"add")==0)
    {
        if(count>=2)
        {

            for(i=1,j=0; i<count; i++)
            {
                if(sscanf(word[i],"%lf%c",&number[j],&ch)==1)
                {
                    j++;
                }
                else
                {
                    err++;
                }
            }

            if(err==0)
            {
                for(i=0; i<j; i++)
                {
                    addData(number[i]);
                }

                return 1;
            }
            else
            {
                return 0;
            }

        }
        else
        {
            return 0;
        }
    }
    else if(strcmp(word[0],"sqrt")==0 || strcmp(word[0],"rec")==0 || strcmp(word[0],"neg")==0 || strcmp(word[0],"+")==0 || strcmp(word[0],"-")==0 || strcmp(word[0],"*")==0 || strcmp(word[0],"/")==0 || strcmp(word[0],"pow")==0){
        if(count==1){
                if(strcmp(word[0],"sqrt")==0){
                    if(first==NULL) printf(" answer> no data\n");
                    else {
                            first->info = sqrt(first->info);
                            printf(" answer> %g\n",first->info);
                    }

                }else if(strcmp(word[0],"rec")==0){
                    if(first==NULL) printf(" answer> no data\n");
                    else {
                            first->info = 1/first->info;
                            printf(" answer> %g\n",first->info);
                    }

                }else if(strcmp(word[0],"neg")==0){
                    if(first==NULL) printf(" answer> no data\n");
                    else {
                            first->info = -(first->info) ;
                            printf(" answer> %g\n",first->info);
                    }

                }else{
                    operatorData(word[0]);
                }
            return 1;
        }else{
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

        printf(" list> ");
        printList();
        printf(" command> ");
        gets(command);
        strlwr(command);
        check=checkcommand(command,word);

        if(check==0)
        {
            printf(" answer> parameter error\n");
        }
        else if(check==1)
        {
            //printf(" answer> ok\n");
            if(strcmp(word[0],"end")==0) end=1;
            else if(strcmp(word[0],"help")==0)
            {
                printf("\n  command :\n\n\n");
                printf("\t add [double] [double] [double]...     Add number as you want to link list at last position\n");
                printf("\t peek [number]                         View data in your number position (0 at first,-1 at last)\n");
                printf("\t delete [double]                       Delete data that equal to your input\n");
                printf("\t push [double]                         Push number at first position\n");
                printf("\t pop [double]                          Pop first data\n");
                printf("\t sqrt,reg,neg                          Use first data to calculate\n");
                printf("\t + , - , * , / , pow                   User first and second data to calculate\n");
                printf("\t insert [double]                       Insert data in best position (linkedlist is sorted)\n");
                printf("\t sort                                  Sort data min to max\n");
                printf("\t end                                   End program\n\n\n");

            }

        }
        else if(strcmp(word[0],"cls")==0 || strcmp(word[0],"clear")==0) system("cls");
        else
        {
            printf(" answer> syntax error\n");
        }

    }
    while(end!=1);

    printf("\n End program\n");
    printf(" program written by 60070501077 Charnsak Dangmanee\n");

}
