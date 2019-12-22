#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void insert();
void list();
void sort();
void del();
void s_num();

struct daegu
{
 char name[30]; // �̸�
 int s_num; // �й�
 int s_score;  // ���м���
 int m_score; // ��������
 int c_score; // ��ǻ�ͼ���
}info[3];

void main()
{
 int a;
 while (1)
 {
  printf("----------------------\n");
  printf("1.Insert   2.List   3.Sort\n");
  printf("4.Delete   5.Exit\n");
  printf("----------------------\n");
  scanf_s("%d",&a);
  if (a == 1)
  {
   insert();
   main();
  }
  else if (a == 2)
  {
   list();
   return;
  }
  else if (a == 3)
  {
   sort();
    main();
  }
  else if (a == 4)
  {
    del();
    main();
  }
  else if (a == 5)
  {
   printf("��� �����ϰڽ��ϴ�.");
   exit(1);
  }
  else
  {
   printf("�ȵ�, �� �ٲ���, �ٲ� ���� ����, ���ư�\n");
    main();
  }
 }
}

void insert()
{
 int i = 0;
 for(i;i<3;i++)
 {
 printf("�̸��� �Է��Ͻÿ� : ");
 scanf_s("%s", &info[i].name,20);
 printf("�й��� �Է��Ͻÿ� : ");
 scanf_s("%d", &info[i].s_num);
 printf("���м����� �Է��Ͻÿ� : ");
 scanf_s("%d", &info[i].s_score);
 printf("���������� �Է��Ͻÿ� : ");
 scanf_s("%d", &info[i].m_score);
 printf("��ǻ�ͼ����� �Է��Ͻÿ� : ");
 scanf_s("%d", &info[i].c_score);
 }
 return;
}

void list()
{
 int i = 0;
 for (i; i < 3;i++)
 {
 printf("�̸�:%s  �й�%d  ����%d  ����%d  ��ǻ��%d\n", info[i].name, info[i].s_num, info[i].s_score, info[i].m_score, info[i].c_score);
 }
 return;
}

void sort()
{
  int i=0;
  int p = 0;
  int hap = 0;
  int temp,j=0;
  for(i;i<3;i++)
  {
  hap = (info[i].s_score + info[i].m_score + info[i].c_score);
  p = (info[i].s_score + info[i].m_score + info[i].c_score) / 3;
  printf("���� �� �հ�%d    ",hap);
  printf("��հ�%d\n",p);
  }
  printf("�й������� ����\n");
	s_num();
 return;
}


void sort_s_num()
{
	int i=0;
	int temp,j=0;
	for(i=0; i<3; i++)
 {
  for(j=0; j<3-i; j++)
  {
	  if(info[j].s_num<info[j+1].s_num)
   {
	   temp=info[j].s_num;
	   info[j].s_num=info[j+1].s_num;
   info[j+1].s_num=temp;
   }
  }
 }
 for(i=0; i<3; i++)
 {
	 printf("�й�%d\n",info[i].s_num);
 }
}
void del()
{
 int i=0;
 char b[20];
 for(i;i<3;i++)
 {
 printf("�̸�:%s  �й�%d  ����%d  ����%d  ��ǻ��%d\n", info[i].name, info[i].s_num, info[i].s_score, info[i].m_score, info[i].c_score);
 }
 printf("�����Ͻ� �̸� : ");
 scanf_s("%s",&b,20);

 for(i=0;i<3;i++)
 {
 if(strcmp(info[i].name,b)==0)
  {
  strcpy(info[i].name,"0");
  info[i].s_num=0;
  info[i].s_score=0;
  info[i].m_score=0;
  info[i].c_score=0;
  }
 }
 
 for(i=0;i<3;i++)
 {
 printf("�̸�:%s  �й�%d  ����%d  ����%d  ��ǻ��%d\n", info[i].name, info[i].s_num, info[i].s_score, info[i].m_score, info[i].c_score);
 }
 return;
} 
