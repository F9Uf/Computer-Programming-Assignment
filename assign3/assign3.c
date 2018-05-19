#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//  struct //
struct data
{
    long long id;
    char field2[100];
    char field3[100];
};
typedef struct data db;
db *dataMain,*tmp;
//   struct   //

// print one data  //
void printData(db *file,int pos)
{
    printf("\n%llu\t%s\t%s",file[pos].id,file[pos].field2,file[pos].field3);
}

// load file test.csv
int loadData(db *dataMain,int *count)
{
    FILE *fp;
    int i=0;
    db x;
    if((fp=fopen("test.CSV","r"))!=NULL)
    {
        printf("\n Can open file.");
        while(fscanf(fp,"%llu,%[^,],%s",&x.id,x.field2,x.field3) == 3)
        {

            dataMain[i++]=x;  //วนรอบอ่านไฟล์แล้วนำไปเก็บไว้ที่ dataMain จนกว่าจะอ่านไม่ได้
        }

        fclose(fp);

        *count = i;
        return 1;  //ถ้าเปิดไฟล์ได้ return ๅ
    }
    else 0;  //เปิดไฟล์ไม่ได้ return 0
}

void copyData(db *data1,db *data2,int count) //คัดลอกข้อมูลจาก ตัวแปรหนึ่งไปอีกตัวแปรหนึ่ง
{
    int i;
    for(i=0; i<count; i++)
    {
        data2[i]=data1[i];
    }
}
void swap(db *data1,db *data2) //สลับข้อมูล ตัวแรกกับตัวที่ 2
{

    db x;
    x=*data1;
    *data1 = *data2;
    *data2 = x;


}
int cmpNum(const void *a,const void *b)  // function เปรียบเทียบเทียบไว้ใช้กับ qsort
{
    long long i,j;
    i=(*(db*)a).id;
    j=(*(db*)b).id;
    if((i-j)>0) return 1;
    else if((i-j)<0) return -1;
    else return 0;
}

int cmpChar(const void *a,const void *b)  // function เปรียบเทียบ ตัวอักษร ไว้ใช้กับ qsort
{
    char x[100],y[100];
    int i;
    strcpy(x,(*(db*)a).field3);
    strcpy(y,(*(db*)b).field3);
    i=strcmp(x,y);
    return i;
}

double qsortProNum(db *data,int count)  // function เรียงข้อมูลจากตัวเลข โดยใช้ qsort จาก library
{

    double start,end;
    double diff;

    start = clock();  //เริ่มจับเวลา
    qsort(data,count,sizeof(db),cmpNum);  //qsort เรียงข้อมูลจากตัวเลข
    end = clock();  //เวลาหลังทำงานเสร็จ

    diff=(end - start)/CLK_TCK;
    return diff;  //return ผลต่างระหว่างเวลาที่เริ่มกับเวลาที่ qsort ทำงานเสร็จ
}

double qsortProChar(db *data,int count) // function เรียงข้อมูลจากตัวอักษร โดยใช้ qsort จาก library
{

    double start,end;
    double diff;

    start = clock();//เริ่มจับเวลา
    qsort(data,count,sizeof(db),cmpChar); //qsort เรียงข้อมูลจากตัวอักษร
    end = clock();  //เวลาหลังทำงานเสร็จ

    diff=(end - start)/CLK_TCK;
    return diff;  //return ผลต่างระหว่างเวลาที่เริ่มกับเวลาที่ qsort ทำงานเสร็จ
}

void qsortUserNum(db *data,int first,int last)  // function เรียงข้อมูลจากตัวเลข โดยใช้วิธี quick sort
{
    int i=first,j=last;

    if(first<last)
    {
        do
        {
            while((data[i].id <= data[j].id) && (i<j))
            {
                j--;
            }
            if(data[i].id > data[j].id)
            {
                swap(&data[i],&data[j]);
                i++;
            }
            while((data[i].id <= data[j].id) && (i<j))
            {
                i++;
            }
            if(data[i].id > data[j].id)
            {
                swap(&data[i],&data[j]);
                j--;
            }

        }
        while(i<j);

        if(first < j-1) qsortUserNum(data,first,j-1);
        if(i+1 < last) qsortUserNum(data,i+1,last);
    }
}

void qsortUserChar(db *data,int first,int last)  // function เรียงข้อมูลจากตัวเลข โดยใช้วิธี quick sort
{

    int i=first,j=last;
    if(first<last)
    {
        do
        {
            while(strcmp(data[i].field3,data[j].field3)<0 && (i<j))
            {
                j--;
            }
            if(strcmp(data[i].field3,data[j].field3)>0 )
            {
                swap(&data[i],&data[j]);
                i++;
            }
            while(strcmp(data[i].field3,data[j].field3)<0  && (i<j))
            {
                i++;
            }
            if(strcmp(data[i].field3,data[j].field3)>0)
            {
                swap(&data[i],&data[j]);
                j--;
            }

        }
        while(i<j);

        if(first < j-1) qsortUserChar(data,first,j-1);
        if(i+1 < last) qsortUserChar(data,i+1,last);
    }

}

int main()
{


    dataMain = (db*)malloc(200000 * sizeof(db)); //กำหนดตัวแปร dataMain ทำงานใน heap segment
    tmp = (db*)malloc(200000 * sizeof(db)); //กำหนดตัวแปร tmp ให้ทำงานใน heap segment และไว้ใช้เป็นตัวเปรียบเทียบในการเรียง

    int count=0,i,check,j;
    double time1[10],time2[10],time3[10],time4[10];
    double start,end,start2,end2;
    double min1,min2,min3,min4;


    check=loadData(dataMain,&count);

    if(check==1 && check!=0)  //เริ่มทำการ sort ถ้าสามารถเปิดไฟล์ และ สามารถอ่านข้อมูล หรือมีข้อมูลให้ sort
    {
        printf("\n Read file succes.\n");

        for(i=0; i<3; i++) //วนรอบ sort 3 ครั้ง ทุก function เพื่อหาเวลาที่ดีที่สุด โดยก่อนเปรียบเทียบ แต่ละ function จะทำการ copy ข้อมูลหลัก ไปใส่ในอีกตัวแปร แล้ว ค่อยนำข้อมูลสำรองไป sort เพื่อกันการ sort ข้อมูลที่เรียงอยู่แล้ว
        {

            printf("\n\n Sort #%d",i+1);
            copyData(dataMain,tmp,count);  //copy ข้อมูลใหม่มาใส่ก่อน sort
            time1[i]=qsortProNum(tmp,count);  //sort ตามตัวเลขโดย qsort จาก library
            printf("\n     sort from number (qsort) #%d time: %g s.",i+1,time1[i]);

            copyData(dataMain,tmp,count); //copy ข้อมูลใหม่มาใส่ก่อน sort
            start=clock();
            qsortUserNum(tmp,0,count-1);   //sort ตามตัวเลขโดย quick sort ที่สร้างเอง
            end=clock();
            time3[i]=(end - start)/CLK_TCK;
            printf("\n     sort from number (quick sort) #%d time: %g s.",i+1,time3[i]);

            copyData(dataMain,tmp,count); //copy ข้อมูลใหม่มาใส่ก่อน sort
            time2[i]=qsortProChar(tmp,count);   //sort ตามตัวอักษรโดย qsort จาก library
            printf("\n     sort from string (qsort) #%d time: %g s.",i+1,time2[i]);


            copyData(dataMain,tmp,count); //copy ข้อมูลใหม่มาใส่ก่อน sort
            start2=clock();
            qsortUserChar(tmp,0,count-1);    //sort ตามตัวอักษรโดย quick sort ที่สร้างเอง
            end2=clock();
            time4[i]=(end2 - start2)/CLK_TCK;
            printf("\n     sort from string (quick sort) #%d time: %g s.",i+1,time4[i]);


        }
        free(tmp);  //คืนค่าความจำ
        min1=time1[0];
        min2=time2[0];
        min3=time3[0];
        min4=time4[0];
        for(j=0; j<3; j++)
        {
            if(time1[j]<=min1) min1=time1[j];  //วนรอบเปรียบเทียบเวลาทั้ง 3 ครั้งของทั้ง 4 function เพื่อหาเวลาที่ดีที่สุดของแต่ะ function
            if(time2[j]<=min2) min2=time2[j];
            if(time3[j]<=min3) min3=time3[j];
            if(time4[j]<=min4) min4=time4[j];
        }

        printf("\n\n Minimum time of Sorting from number (qsort) : %g s.",min1);  //แสดงเวลาต่างๆ
        printf("\n\n Minimum time of Sorting from number (quick sort) : %g s.",min3);
        printf("\n\n Minimum time of Sorting from string (qsort) : %g s.",min2);
        printf("\n\n Minimum time of Sorting from string (quick sort) : %g s.\n\n",min4);

    }
    else if(check==0)  //ถ้าไม่มีข้อมูล จะไม่ทำการ sort
    {
        printf("\n Error Can't Read File.\n");
    }
    else  //ถ้าอ่านไฟล์ไม่ได้ จะไม่ทำการ sort
    {
        printf("\n Can open file but can't read file.\n");
    }


    return 0;

}














