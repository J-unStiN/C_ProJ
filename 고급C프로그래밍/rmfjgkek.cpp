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
 char name[30]; // 이름
 int s_num; // 학번
 int s_score;  // 수학성적
 int m_score; // 물리성적
 int c_score; // 컴퓨터성적
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
   printf("장비를 정지하겠습니다.");
   exit(1);
  }
  else
  {
   printf("안돼, 안 바꿔줘, 바꿀 생각 없어, 돌아가\n");
    main();
  }
 }
}

void insert()
{
 int i = 0;
 for(i;i<3;i++)
 {
 printf("이름을 입력하시오 : ");
 scanf_s("%s", &info[i].name,20);
 printf("학번을 입력하시오 : ");
 scanf_s("%d", &info[i].s_num);
 printf("수학성적을 입력하시오 : ");
 scanf_s("%d", &info[i].s_score);
 printf("물리성적을 입력하시오 : ");
 scanf_s("%d", &info[i].m_score);
 printf("컴퓨터성적을 입력하시오 : ");
 scanf_s("%d", &info[i].c_score);
 }
 return;
}

void list()
{
 int i = 0;
 for (i; i < 3;i++)
 {
 printf("이름:%s  학번%d  수학%d  물리%d  컴퓨터%d\n", info[i].name, info[i].s_num, info[i].s_score, info[i].m_score, info[i].c_score);
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
  printf("점수 총 합계%d    ",hap);
  printf("평균값%d\n",p);
  }
  printf("학번순으로 정렬\n");
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
	 printf("학번%d\n",info[i].s_num);
 }
}
void del()
{
 int i=0;
 char b[20];
 for(i;i<3;i++)
 {
 printf("이름:%s  학번%d  수학%d  물리%d  컴퓨터%d\n", info[i].name, info[i].s_num, info[i].s_score, info[i].m_score, info[i].c_score);
 }
 printf("삭제하실 이름 : ");
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
 printf("이름:%s  학번%d  수학%d  물리%d  컴퓨터%d\n", info[i].name, info[i].s_num, info[i].s_score, info[i].m_score, info[i].c_score);
 }
 return;
} 
