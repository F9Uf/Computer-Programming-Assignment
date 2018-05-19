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

int cutword(char *command,char word[][40]) //ตัดคำสั่งจาก string โดยใช้เว้นวรรค
{
    char *token;
    int count=0;
    token=strtok(command," ");
    while(token!=NULL)  //วนรอบตัดคำจาก string โดยใช้เว้นวรรคแล้วเก็บใส่ array word
    {
        strcpy(word[count++],token);
        token=strtok(NULL," ");
    }
    return count;
}

void printList() //print link list
{
    linkedlist *ptr;
    int count=0;
    ptr=first;
    if(first==NULL) printf(" NULL\n"); //ถ้าไม่มีข้อมูลให้แสดงว่า NULL
    else
    {
        while(ptr!=NULL)  //ถ้ามีให้วนรอบจนกว่าจะถึงตัวสุดท้าย แล้ว print ค่าออกมา
        {
            printf("%g ",ptr->info);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void addData(double item)  //เพิ่มข้อมูลต่อจากตัวสุดท้าย
{
    linkedlist *ptr;
    ptr = (linkedlist*)malloc(sizeof(linkedlist));
    ptr->next = NULL;  //นำตัวเลขไปเก็บไว้ใน node ptr โดยให้ ptr->next จิ้มที่ NULL
    ptr->info = item;

    if(first == NULL) //ถ้าไม่มีข้อมูล ให้ เพิ่มข้อมูลเข้าไปแล้วให้ first และ last จิ้มที่ตัวนั้น
    {
        first=last=ptr;
    }
    else //ถ้าไม่ใช่ให้นำ node ใหม่จิ้มไปหลังตัวสุดท้าย และนำ last มาชี้ที่ตัวที่ถูกเพิ่มเข้าไปใหม่
    {
        last->next = ptr;
        last = ptr;
    }
}

void sortData() //เรียงจาก min to max
{
    linkedlist *ptrI,*ptrJ;
    double x;
    ptrI=first;
    while(ptrI->next != NULL) //วนรอบก่อนถึงตัวสุดท้าย
    {
        ptrJ=ptrI->next; //ให้ ptrJ คือตัว ถัดจาก ptrI
        while(ptrJ!=NULL) //ถ้ายังไม่ถึงตัวสุดท้าย
        {
            if(ptrJ->info < ptrI->info) //ถ้าตัวทางขวามากกว่าตัวทางซ้าย ให้ สลับค่ากันไปเรื่อยๆ
            {
                x=ptrI->info;
                ptrI->info=ptrJ->info;
                ptrJ->info=x;
            }
            ptrJ=ptrJ->next; //ขยับ ptrJ ไป 1 ตำแหน่ง
        }
        ptrI=ptrI->next; //ขยับ ptrI ไป 1 ตำแหน่ง
    }
}

void popData()  //นำข้อมูลตัวแรกมาแสดงแล้วลบทิ้ง
{
    double x = first->info;
    printf(" answer> %g\n",x);
    first=first->next;


}

void pushData(double num) //เพิ่มข้อมูลไว้ที่ตัวหน้าสุด
{
    linkedlist *ptr;
    ptr = (linkedlist*)malloc(sizeof(linkedlist));

    ptr->info = num;

    if(first==NULL){ //ถ้าไม่มีข้อมูล
        first=last=ptr; //ให้เพิ่มข้อมูลเข้าไปใหม่ 1 ตัว
        ptr->next=NULL;
    }else{
        ptr->next = first; //ให้ข้อมูลชุดใหม่ ชี้ที่ตัวแรกสุด

        first = ptr; //แล้วกำหนดให้ตัวแรกสุด หรือ first เป็น ข้อมูลชุดใหม่
    }

}

void peekData(int n) //แสดงข้อมูลลำกับที่ n
{
    linkedlist *ptr;
    int count=0;
    ptr = first;

    if(first==NULL) //ถ้าไม่มีข้อมูล
    {
        printf(" answer> no data\n");
    }
    else
    {
        if(n == -1) //ถ้าพิมพ์ -1 ให้แสดงช้อมูลตัวสุดท้าย
        {
            printf(" answer> %g\n",last->info);
        }
        else if(n==0)  //ถ้าพิมพ์ 0 ให้แสดงข้อมูลตัวแรก
        {
            printf(" answer> %g\n",first->info);
        }
        else //ถ้าไม่ใช่ให้วนรอบจนกว่าจะถึงตัวสุดท้าย หรือ เจอตำแหน่งตัวที่ต้องการ
        {
            while((ptr!=NULL) && count<n)
            {
                ptr=ptr->next;
                count++;
            }
            if(ptr==NULL) printf(" answer> Maximum peek = %d\n",count-1); //ถ้าวนรอบจนถึงตัวสุดท้ายแล้วไม่เจอ ให้บอกว่า peek ไม่ถึง
            else printf(" answer> %g\n",ptr->info); //ถ้าเจอ ให้ แสดงผล
        }
    }
}

int checkSort() //check ว่าข้อมูลขณะนี้เรียงอยู่ไหม
{
    linkedlist *ptr;
    ptr = first;
    int err=0;
    if(first==NULL)
    {
        return 0; //no data but can insert
    }
    else
    {
        while((ptr!=NULL) && err==0) //วนรอบจนถึงตัวสุดท้าย หรือ err !=0
        {


            if(ptr!=last) //ถ้า ptr ยังไม่ถึงตัวสุดท้าย ให้ตรวจสอบดูว่าตัวถัดไปน้อยกว่าไหม ถ้าน้อยกว่า ตัวทางซ้ายแสดงว่าไม่ได้เรียง
            {
                if((ptr->info) > (ptr->next)->info)
                {
                    err++; //ให้ err ++ เพื่อออกจาก loop
                }
            }

            ptr=ptr->next; //เลื่อนตำแหน่ง
        }

        if(ptr!=NULL)
        {
            return -1; // not sort
        }
        else
        {
            return 1;// sorted
        }
    }
}

void insertData(double item) //เพิ่มข้อมูลไปในตำแหน่งที่ถูกต้อง
{
    linkedlist *ptr,*newNode;


    newNode=(linkedlist*)malloc(sizeof(linkedlist)); //จองพื้นที่ ใน heap เพื่อใช้เพิ่มข้อมูล

    newNode->info = item;
    newNode->next = NULL;

    if(first==NULL)
    {
        first=last=newNode;  // no data ให้เพิ่มข้อมูลเข้าไปใหม่ 1 ตัว
    }
    else if(first->info > newNode->info)    // new data < first
    {
        newNode->next = first; //ให้เพิ่มข้อมูลตัวใหม่ไปไว้ที่ตัวแรกสุด
        first=newNode;
    }
    else  //หรือถ้าไม่ใช่เงื่อนไขทั้งหมด ให้วนรอบหาตำแหน่งที่ถูกต้งอ
    {
        ptr = first;
        while((ptr->next)!=NULL && ((ptr->next)->info < newNode->info ) ) //วนรอบตั้งแต่ตัวแรกจนตัวก่อนสุดท้าย หรือ จนถึงตำแหน่งที่ถูกต้อง
        {
            ptr = ptr->next; //เลื่อนไป 1 ตำแหน่ง
        }

        newNode->next = ptr->next; //นำข้อมูลชุดใหม่ไปแทรกในตำแหน่งที่ถูกต้อง
        ptr->next = newNode;

        if(ptr==last)  //ถ้าแทรกเข้าไปตำแหน่งสุดท้าย ให้ last มาชี้ที่ ข้อมูลชุดใหม่ด้วย
        {
            last = newNode;
        }
    }
}


void deleteData(double key)
{
    linkedlist *ptr,*prev;
    char ch;
    int found=0;

    ptr = first;
    prev=ptr;


    while(ptr!=NULL) //วนรอบทุกตัว
    {

        if(ptr->info == key)  //ถ้าเจอ
        {
            found++; //นับจำนวนคำที่เจอ
            printf(" answer> %g found enter Y to comfirm : ",ptr->info);
            scanf("%c",&ch);

            if(ch=='y' || ch=='Y')  //ถ้าลบ
            {
                rewind(stdin);

                if(first==last){ //ถ้ามีข้อมูลชุดเดียว ให้ลบทั้ง first และ ก็ last
                    first=NULL;
                    last=NULL;
                    ptr=NULL;
                }else { //ถ้าไม่ใช่

                    if(ptr==last){ //ลบตัวสุดท้าย

                       free(ptr); //คืนค่า ptr
                       last=prev;  //ให้ last เป็น prev
                       prev->next=NULL; //ให้ ตัวถัดไป เป็น NULL

                    }else if(ptr==first){ //หรือถ้า ลบข้อมูลตัวแรก

                        first=ptr->next; //ให้ first เป็นตัวถัดไป แล้วคืนหน่วยความจำตัวที่ถูกลบ
                        free(ptr);
                    }else{ //ถ้าไม่ใช่ทั้งตัวแรก และ ก็ ไม่ใช่ตัวเดียว
                        prev->next=ptr->next; //ให้ node ก่อนหน้า จิ้ม node ถัดไป
                        free(ptr);             // แล้วคืนหน่วยความจำตัวที่ถูกลบ
                        ptr=prev->next;         //ให้ ptr ไปจิ้มตัวถัดจาก prev
                    }



                }

            }
            else   //ถ้าไม่ลบ
            {
                rewind(stdin);
                prev=ptr;  //เลื่อนตำแหน่งถัดไป
                ptr=ptr->next;
            }

        }
        else   //ถ้าไม่เจอ
        {

            prev=ptr;  //เลื่อนตำแหน่งถัดไป
            ptr=ptr->next;
        }

    }

    if(found<=0){ //ถ้าไม่เจอข้อมูล
        printf(" answer> %g not found\n",key);
    }
}

void operatorData(char *command)
{
    linkedlist *ptr;
    double one,two,result;


    if(first==NULL) //ถ้าไม่มีข้อมูล
    {
        printf(" answer> no data\n");
    }
    else if(last==first)  //หรือข้อมูลมี 1  node ไม่สามารถคำนวณได้
    {
        printf(" answer> can't operator\n");
    }
    else
    {
        one = (first->info); //ให้ one เป็นตำแหน่งแรกสุด
        two = (first->next)->info ; //ให้ two เป็นตำแหน่งที่ 2

        if(strcmp(command,"+")==0) //ถ้าพิมพ์ว่า +
        {
            result=two+one;            //ให้บวกกันแล้วเก็บไว้ที่ result
            first=first->next;         //ขยับตำแหน่งแรกไปตำแหน่งที่ 2
            first->info = result;      //แล้วกำหนดค่าใหม่ให้เป็นค่าที่ คำนวณมาได้
            printf(" answer> %g\n",result);
        }
        else if(strcmp(command,"-")==0)
        {
            result=two-one;           //ลบกันแล้วเก็บไว้ที่ result
            first=first->next;       //ขยับตำแหน่งแรกไปตำแหน่งที่ 2
            first->info = result;   //แล้วกำหนดค่าใหม่ให้เป็นค่าที่ คำนวณมาได้
            printf(" answer> %g\n",result);
        }
        else if(strcmp(command,"*")==0)
        {
            result=two*one;            //คูณกันแล้วเก็บไว้ที  result
            first=first->next;         //ขยับตำแหน่งแรกไปตำแหน่งที่ 2
            first->info = result;     //แล้วกำหนดค่าใหม่ให้เป็นค่าที่ คำนวณมาได้
            printf(" answer> %g\n",result);
        }
        else if(strcmp(command,"/")==0)
        {
            if(one==0)
            {
                printf(" answer> can't divide by 0\n");  //ถ้าส่วนเป็นศูนย์ หารไม่ได้
            }
            else
            {
                result=two/one;             //หารกันแล้วเก็บไว้ที่ result
                first=first->next;        //ขยับตำแหน่งแรกไปตำแหน่งที่ 2
                first->info = result;     //แล้วกำหนดค่าใหม่ให้เป็นค่าที่ คำนวณมาได้
                printf(" answer> %g\n",result);
            }

        }
        else
        {
            result=pow(two,one);        //ให้เอาตำแหน่งแรกยกกำลังตัวตำแหน่งที่สอง แล้วเก็บไว้ที่   result
            first=first->next;          //ขยับตำแหน่งแรกไปตำแหน่งที่ 2
            first->info = result;      //แล้วกำหนดค่าใหม่ให้เป็นค่าที่ คำนวณมาได้
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
        if(count==1)  //มีแค่  1 คำ ไม่มี parameter
        {
            if(strcmp(word[0],"sort")==0)
            {
                if(first==NULL) printf(" answer> no data\n");  //ถ้าไม่มีข้อมูล
                else  sortData();  //ถ้ามีให้ sort
            }
            else if(strcmp(word[0],"pop")==0)
            {
                if(first==NULL) printf(" answer> no data\n");  //ถ้าไม่มีข้อมูล
                else popData();  //ถ้ามีให้ pop
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(strcmp(word[0],"delete")==0 || strcmp(word[0],"insert")==0 || strcmp(word[0],"push")==0 || strcmp(word[0],"peek")==0 )
    {
        if(count==2) //มี  2 คำ หรือ มี 1 parameter
        {
            if(sscanf(word[1],"%d%c",&num,&ch)==1 && strcmp(word[0],"peek")==0)  //เก็บค่า parameter เป็น integer ที่คำสั่ง peek ได้ ให้ peek ข้อมูล
            {
                peekData(num);
                return 1;
            }
            else if(sscanf(word[1],"%lf%c",&number[0],&ch)==1)   //ถ้าอ่านค่า paremeter เป็น จำนวนจริงได้
            {

                if(strcmp(word[0],"delete")==0)  //คำสั่ง เป็น delete
                {
                    if(first!=NULL)            //ถ้ามีข้อมูลให้ delete ข้อมูล
                        deleteData(number[0]);
                    else printf(" answer> no data\n");   //ถ้าไม่มีข้อมูล
                }
                else if(strcmp(word[0],"push")==0)
                {
                    pushData(number[0]);  //คำสั่ง push ให้ ทำ function pushData

                }
                else if(strcmp(word[0],"insert")==0)
                {
                    checksort=checkSort();  //check ว่าข้อมูลเรียงกันไหม
                    if(checksort==0)  //ถ้าไม่มีข้อมูล
                    {
                        insertData(number[0]);  //ให้ insert ข้อมูลใหม่
                    }
                    else if (checksort==1)  //ถ้าช้อมูลเรียง
                    {
                        insertData(number[0]);  //ให้  insert ข้อมูล

                    }
                    else printf(" answer> can't insert please sorted before\n");  //ถ้าข้อมูลไม่เรียง

                }

                return 1;
            }
            else
            {
                return 0;  // parameter ผิดปรเภท
            }
        }
        else
        {
            return 0;  // parameter ไม่ครบ
        }
    }
    else if(strcmp(word[0],"add")==0)  //คำสั่ง  add
    {
        if(count>=2)  //มี parameter มากกว่า  1
        {

            for(i=1,j=0; i<count; i++) //วนรอบเก็บ parameter ทุกตัว ใส่ array
            {
                if(sscanf(word[i],"%lf%c",&number[j],&ch)==1)
                {
                    j++; //ถ้าเก็บข้อมูลได้ให้ เลื่อนตำแหน่ง array
                }
                else
                {
                    err++;  //ถ้าเก็บไม่ได้ให้นับค่าที่ผิด
                }
            }

            if(err==0)  //ถ้าเ parameter ถูกทุกตัว
            {
                for(i=0; i<j; i++)
                {
                    addData(number[i]); //ให้วนรอบ addData parameter ที่เก็บใน array ทุกตัว
                }

                return 1;
            }
            else
            {
                return 0;  //มี parameter ผิด
            }

        }
        else
        {
            return 0;  //parameter ไม่ครบ
        }
    }
    else if(strcmp(word[0],"sqrt")==0 || strcmp(word[0],"rec")==0 || strcmp(word[0],"neg")==0 || strcmp(word[0],"+")==0 || strcmp(word[0],"-")==0 || strcmp(word[0],"*")==0 || strcmp(word[0],"/")==0 || strcmp(word[0],"pow")==0)
    {
        if(count==1) //ไม่มี parameter
        {
            if(strcmp(word[0],"sqrt")==0)
            {
                if(first==NULL) printf(" answer> no data\n");  //ไม่มีข้อมูล
                else
                {
                    first->info = sqrt(first->info);   //sqrt ช้อมูลชุดแรกเก็บใส่ตัวเดิม
                    printf(" answer> %g\n",first->info);
                }

            }
            else if(strcmp(word[0],"rec")==0)
            {
                if(first==NULL) printf(" answer> no data\n"); //ไม่มีข้อมล
                else
                {
                    first->info = 1/first->info;  // 1/ข้อมูลชุดแรก แล้วเก็บเข้าตัวเดิม
                    printf(" answer> %g\n",first->info);
                }

            }
            else if(strcmp(word[0],"neg")==0)  //เปลี่ยนข้อมูลชุดแรกเป็นค่าตรงข้าม จากลบเป็นบวก บวกเป็นลบ
            {
                if(first==NULL) printf(" answer> no data\n");
                else
                {
                    first->info = -(first->info) ; //เปลี่ยนค่าแล้วเก็บเข้าตัวเดิม
                    printf(" answer> %g\n",first->info);
                }

            }
            else
            {
                operatorData(word[0]); //ถ้าเป็นคำสั่งอื่นๆให้ไปทำที่ function operatorData()
            }
            return 1;
        }
        else
        {
            return 0;  //parameter ผิด
        }
    }
    else
    {
        return -1;  //คำสั่งผิด
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
            else if(strcmp(word[0],"help")==0) //ถ้าพิมพ์ ว่า help
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
        else
        {
            printf(" answer> syntax error\n");
        }

    }
    while(end!=1);

    printf("\n End program\n");
    printf(" program written by 60070501077 Charnsak Dangmanee\n");

}
