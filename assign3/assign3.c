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

            dataMain[i++]=x;  //ǹ�ͺ��ҹ������ǹ��������� dataMain �����Ҩ���ҹ�����
        }

        fclose(fp);

        *count = i;
        return 1;  //����Դ����� return �
    }
    else 0;  //�Դ�������� return 0
}

void copyData(db *data1,db *data2,int count) //�Ѵ�͡�����Ũҡ �����˹����ա�����˹��
{
    int i;
    for(i=0; i<count; i++)
    {
        data2[i]=data1[i];
    }
}
void swap(db *data1,db *data2) //��Ѻ������ ����á�Ѻ��Ƿ�� 2
{

    db x;
    x=*data1;
    *data1 = *data2;
    *data2 = x;


}
int cmpNum(const void *a,const void *b)  // function ���º��º��º�����Ѻ qsort
{
    long long i,j;
    i=(*(db*)a).id;
    j=(*(db*)b).id;
    if((i-j)>0) return 1;
    else if((i-j)<0) return -1;
    else return 0;
}

int cmpChar(const void *a,const void *b)  // function ���º��º ����ѡ�� �����Ѻ qsort
{
    char x[100],y[100];
    int i;
    strcpy(x,(*(db*)a).field3);
    strcpy(y,(*(db*)b).field3);
    i=strcmp(x,y);
    return i;
}

double qsortProNum(db *data,int count)  // function ���§�����Ũҡ����Ţ ���� qsort �ҡ library
{

    double start,end;
    double diff;

    start = clock();  //������Ѻ����
    qsort(data,count,sizeof(db),cmpNum);  //qsort ���§�����Ũҡ����Ţ
    end = clock();  //������ѧ�ӧҹ����

    diff=(end - start)/CLK_TCK;
    return diff;  //return �ŵ�ҧ�����ҧ���ҷ��������Ѻ���ҷ�� qsort �ӧҹ����
}

double qsortProChar(db *data,int count) // function ���§�����Ũҡ����ѡ�� ���� qsort �ҡ library
{

    double start,end;
    double diff;

    start = clock();//������Ѻ����
    qsort(data,count,sizeof(db),cmpChar); //qsort ���§�����Ũҡ����ѡ��
    end = clock();  //������ѧ�ӧҹ����

    diff=(end - start)/CLK_TCK;
    return diff;  //return �ŵ�ҧ�����ҧ���ҷ��������Ѻ���ҷ�� qsort �ӧҹ����
}

void qsortUserNum(db *data,int first,int last)  // function ���§�����Ũҡ����Ţ �����Ը� quick sort
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

void qsortUserChar(db *data,int first,int last)  // function ���§�����Ũҡ����Ţ �����Ը� quick sort
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


    dataMain = (db*)malloc(200000 * sizeof(db)); //��˹������ dataMain �ӧҹ� heap segment
    tmp = (db*)malloc(200000 * sizeof(db)); //��˹������ tmp ���ӧҹ� heap segment ���������繵�����º��º㹡�����§

    int count=0,i,check,j;
    double time1[10],time2[10],time3[10],time4[10];
    double start,end,start2,end2;
    double min1,min2,min3,min4;


    check=loadData(dataMain,&count);

    if(check==1 && check!=0)  //������ӡ�� sort �������ö�Դ��� ��� ����ö��ҹ������ �����բ�������� sort
    {
        printf("\n Read file succes.\n");

        for(i=0; i<3; i++) //ǹ�ͺ sort 3 ���� �ء function ���������ҷ��շ���ش �¡�͹���º��º ���� function �зӡ�� copy ��������ѡ ������ա����� ���� ���¹Ӣ��������ͧ� sort ���͡ѹ��� sort �����ŷ�����§��������
        {

            printf("\n\n Sort #%d",i+1);
            copyData(dataMain,tmp,count);  //copy ����������������͹ sort
            time1[i]=qsortProNum(tmp,count);  //sort �������Ţ�� qsort �ҡ library
            printf("\n     sort from number (qsort) #%d time: %g s.",i+1,time1[i]);

            copyData(dataMain,tmp,count); //copy ����������������͹ sort
            start=clock();
            qsortUserNum(tmp,0,count-1);   //sort �������Ţ�� quick sort ������ҧ�ͧ
            end=clock();
            time3[i]=(end - start)/CLK_TCK;
            printf("\n     sort from number (quick sort) #%d time: %g s.",i+1,time3[i]);

            copyData(dataMain,tmp,count); //copy ����������������͹ sort
            time2[i]=qsortProChar(tmp,count);   //sort �������ѡ���� qsort �ҡ library
            printf("\n     sort from string (qsort) #%d time: %g s.",i+1,time2[i]);


            copyData(dataMain,tmp,count); //copy ����������������͹ sort
            start2=clock();
            qsortUserChar(tmp,0,count-1);    //sort �������ѡ���� quick sort ������ҧ�ͧ
            end2=clock();
            time4[i]=(end2 - start2)/CLK_TCK;
            printf("\n     sort from string (quick sort) #%d time: %g s.",i+1,time4[i]);


        }
        free(tmp);  //�׹��Ҥ�����
        min1=time1[0];
        min2=time2[0];
        min3=time3[0];
        min4=time4[0];
        for(j=0; j<3; j++)
        {
            if(time1[j]<=min1) min1=time1[j];  //ǹ�ͺ���º��º���ҷ�� 3 ���駢ͧ��� 4 function ���������ҷ��շ���ش�ͧ��� function
            if(time2[j]<=min2) min2=time2[j];
            if(time3[j]<=min3) min3=time3[j];
            if(time4[j]<=min4) min4=time4[j];
        }

        printf("\n\n Minimum time of Sorting from number (qsort) : %g s.",min1);  //�ʴ����ҵ�ҧ�
        printf("\n\n Minimum time of Sorting from number (quick sort) : %g s.",min3);
        printf("\n\n Minimum time of Sorting from string (qsort) : %g s.",min2);
        printf("\n\n Minimum time of Sorting from string (quick sort) : %g s.\n\n",min4);

    }
    else if(check==0)  //�������բ����� �����ӡ�� sort
    {
        printf("\n Error Can't Read File.\n");
    }
    else  //�����ҹ�������� �����ӡ�� sort
    {
        printf("\n Can open file but can't read file.\n");
    }


    return 0;

}














