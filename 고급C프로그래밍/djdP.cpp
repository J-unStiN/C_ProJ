#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *indata, *outdata;

struct data {
	char hakbun[20];
	char name[40];
	int guka;
	int suhak;
	int c;
} jungbo[2000];

int eadate;

void loadfile();
void start();
void julcui();
void add();
void list();
void arrg_main();
void sakjae();
void add_data();
void sujung();
void arr_scr();
void arr_num();


void main()
{
	loadfile();
	start();
}

void loadfile()
{
	int r;
	eadate=0;
	indata=fopen("data.txt","r");
	while(1)
	{
		r=fscanf(indata, "%s %s %d %d %d", &jungbo[eadate].hakbun, &jungbo[eadate].name, &jungbo[eadate].guka, &jungbo[eadate].suhak, &jungbo[eadate].c);
		eadate++;
		if(r<0)
		{
			eadate--;
			break;		
		}
	}
	fclose(indata);
}

void start()
{
	int i;
	system("cls");
	julcui();
	printf("1.추가 2.검색 3.정렬\n4.삭제 5.종료\n");	
	julcui();
	while(1)
	{
		printf("수행할 작업을 입력하세요.:");
		scanf("%d", &i);
		if(i==1)
		{
			add();
			return;
		}
		else if(i==2)
		{
			list();
			return;
		}
		else if(i==3)
		{
			arrg_main();
			return;
		}
		else if(i==4)
		{
			sakjae();
			return;
		}
		else if(i==5)
		{
			exit(1);
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}
}

void julcui()
{
	printf("---------------------------------------------\n");
}

void add()
{
	int i;
	loadfile();
	system("cls");
	while(1)
	{
		printf("작업을 입력하세요.(1.추가, 2.수정, 3.초기화면으로):");
		scanf("%d", &i);
		if(i==1)
		{
			add_data();
			return;
		}
		else if(i==2)
		{
			sujung();
			return;
		}
		else if(i==3)
		{
			main();
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}
}

void add_data()
{
	int i,g;
	int r=1;
	struct data cup;
	system("cls");
	while(1)
	{
		printf("학번을 입력하세요.:");
		scanf("%s", &cup.hakbun);
		for(i=0 ; i<eadate ; i++)
		{
			r=0;	
			if(strcmp(cup.hakbun,jungbo[i].hakbun)!=0)
			{
				r=1;
			}

			if(r==0)
			{
				break;
			}
		}
		if(r==0)
		{
			printf("학번중복!\n");
		}
		else
		{
			break;
		}
	}

	printf("이름을 입력하세요.:");
	scanf("%s", &cup.name);
	printf("국어점수를 입력하세요.:");
	scanf("%d", &cup.guka);
	printf("수학점수를 입력하세요.:");
	scanf("%d", &cup.suhak);
	printf("C언어점수를 입력하세요.:");
	scanf("%d", &cup.c);
	printf("  학번    이름   국어  수학 C언어\n");
	printf("%8s %6s  %3d   %3d   %3d\n", cup.hakbun, cup.name, cup.guka, cup.suhak, cup.c);
	outdata=fopen("data.txt","a");
	fprintf(outdata, "%s %s %d %d %d", cup.hakbun, cup.name, cup.guka, cup.suhak, cup.c);
	fprintf(outdata, "\n");
	fclose(outdata);
	eadate++;
	printf("추가 완료!\n");
	while(1)
	{
		printf("1.추가 항목으로 가기, 2.돌아가기");
		scanf("%d", &g);
		if(g==1)
		{
			add();
			return;
		}
		else if(g==2)
		{
			main();
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}

}

void sujung()
{
	int i,j,g;
	int r=0;
	char cup[20];
	int a;
	int b;
	int c;
	system("cls");
	while(1)
	{
		printf("수정할 학번을 입력하세요.:");
		scanf("%s", &cup);
		for(i=0 ; i<eadate ; i++)
		{
			r=0;
			if(strcmp(cup,jungbo[i].hakbun)==0)		
			{
				r=1;
				break;
			}
		}
		if(r==1)
		{
			break;
		}
		else
		{
			printf("존재하지않는 학번입니다.\n");
		}
	}
	printf("  학번    이름   국어  수학 C언어\n");
	printf("%8s %6s  %3d   %3d   %3d\n", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c);
	printf("수정할 국어점수를 입력하세요.:");
	scanf("%d", &a);
	printf("수정할 수학점수를 입력하세요.:");
	scanf("%d", &b);
	printf("수정할 C언어점수를 입력하세요.:");
	scanf("%d", &c);
	jungbo[i].guka=a;
	jungbo[i].suhak=b;
	jungbo[i].c=c;
	outdata=fopen("data.txt","w");
	for(j=0 ; j<eadate ; j++)
	{
		fprintf(outdata, "%s %s %d %d %d", jungbo[j].hakbun, jungbo[j].name, jungbo[j].guka, jungbo[j].suhak, jungbo[j].c);
		fprintf(outdata, "\n");
	}
	fclose(outdata);
	printf("수정 완료!\n");
	while(1)
	{
		printf("1.추가 항목으로 가기, 2.돌아가기");
		scanf("%d", &g);
		if(g==1)
		{
			add();
			return;
		}
		else if(g==2)
		{
			main();
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}
}


void list()
{
	int i=0;
	int avr,sum;
	int g;
	system("cls");
	printf("<목록>\n");
	printf("  학번    이름   국어  수학 C언어  합계    평균\n");
	for(i=0 ; i<eadate ; i++)
	{
		sum=jungbo[i].guka+jungbo[i].suhak+jungbo[i].c;
		avr=(jungbo[i].guka+jungbo[i].suhak+jungbo[i].c)/3;
		printf("%8s %6s  %3d   %3d   %3d    %3d    %3d\n", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c, sum, avr);
	}

	while(1)
	{
		printf("1.정렬하기 2.돌아가기.:");
		scanf("%d", &g);
		if(g==1)
		{
			arrg_main();
			return;
		}
		else if(g==2)
		{
			main();
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}
}

void arrg_main()
{
	system("cls");

	while(1)
	{
		int h;
		printf("1.성적순, 2.학번순");
		scanf("%d", &h);

		if(h==1)
		{
			arr_scr();
			return;
		}
		else if(h==2)
		{
			arr_num();
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}
}

void arr_scr()
{
	int i,j;
	int avr1,avr2,sum;
	int g;
	struct data cup;
	system("cls");
	for(j=0 ; j<eadate ; j++ )
	{
		for(i=0 ; i<eadate-1 ; i++)
		{
			avr1=(jungbo[i].guka+jungbo[i].suhak+jungbo[i].c)/3;
			avr2=(jungbo[i+1].guka+jungbo[i+1].suhak+jungbo[i+1].c)/3;
			if(avr2>avr1)
			{
				strcpy(cup.hakbun,jungbo[i+1].hakbun);
				strcpy(jungbo[i+1].hakbun,jungbo[i].hakbun);
				strcpy(jungbo[i].hakbun,cup.hakbun);

				strcpy(cup.name,jungbo[i+1].name);
				strcpy(jungbo[i+1].name,jungbo[i].name);
				strcpy(jungbo[i].name,cup.name);

				cup.guka=jungbo[i+1].guka;
				jungbo[i+1].guka=jungbo[i].guka;
				jungbo[i].guka=cup.guka;

				cup.suhak=jungbo[i+1].suhak;
				jungbo[i+1].suhak=jungbo[i].suhak;
				jungbo[i].suhak=cup.suhak;

				cup.c=jungbo[i+1].c;
				jungbo[i+1].c=jungbo[i].c;
				jungbo[i].c=cup.c;
			}

		}

	}
	printf("<성적순 정렬>\n");
	printf("  학번    이름   국어  수학 C언어  합계    평균\n");
	for(i=0 ; i<eadate ; i++)
	{
		sum=jungbo[i].guka+jungbo[i].suhak+jungbo[i].c;
		avr1=(jungbo[i].guka+jungbo[i].suhak+jungbo[i].c)/3;
		printf("%8s %6s  %3d   %3d   %3d    %3d    %3d\n", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c, sum, avr1);
	}

	while(1)
	{
		printf("1.학번순 재정렬, 2.돌아가기");
		scanf("%d", &g);
		if(g==1)
		{
			arr_num();
			return;
		}
		else if(g==2)
		{
			main();
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}

}

void arr_num()
{
	int i,j;
	int avr1,sum;
	int g;
	struct data cup;
	system("cls");
	for(j=0 ; j<eadate ; j++ )
	{
		for(i=0 ; i<eadate-1 ; i++)
		{
			if(strcmp(jungbo[i].hakbun,jungbo[i+1].hakbun)>0)
			{
				strcpy(cup.hakbun,jungbo[i+1].hakbun);
				strcpy(jungbo[i+1].hakbun,jungbo[i].hakbun);
				strcpy(jungbo[i].hakbun,cup.hakbun);

				strcpy(cup.name,jungbo[i+1].name);
				strcpy(jungbo[i+1].name,jungbo[i].name);
				strcpy(jungbo[i].name,cup.name);

				cup.guka=jungbo[i+1].guka;
				jungbo[i+1].guka=jungbo[i].guka;
				jungbo[i].guka=cup.guka;

				cup.suhak=jungbo[i+1].suhak;
				jungbo[i+1].suhak=jungbo[i].suhak;
				jungbo[i].suhak=cup.suhak;

				cup.c=jungbo[i+1].c;
				jungbo[i+1].c=jungbo[i].c;
				jungbo[i].c=cup.c;
			}

		}

	}
	printf("<학번순 정렬>\n");
	printf("  학번    이름   국어  수학 C언어  합계    평균\n");
	for(i=0 ; i<eadate ; i++)
	{
		sum=jungbo[i].guka+jungbo[i].suhak+jungbo[i].c;
		avr1=(jungbo[i].guka+jungbo[i].suhak+jungbo[i].c)/3;
		printf("%8s %6s  %3d   %3d   %3d    %3d    %3d\n", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c, sum, avr1);
	}

	while(1)
	{
		printf("1.성적순 재정렬, 2.돌아가기");
		scanf("%d", &g);
		if(g==1)
		{
			arr_scr();
			return;
		}
		else if(g==2)
		{
			main();
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}
}

void sakjae()
{

	char cup[20];
	int g,i,r,j;
	system("cls");
	while(1)
	{



		printf("삭제할 학번을 입력하세요.(돌아가기:back):");
		scanf("%s", &cup);
		if(strcmp(cup,"back")==0)
		{
			main();
			return;
		}
		for(i=0 ; i<eadate ; i++)
		{
			r=0;
			if(strcmp(cup,jungbo[i].hakbun)==0)		
			{
				r=1;
				break;
			}
		}
		if(r==1)
		{
			break;
		}
		else
		{
			printf("존재하지않는 학번입니다.\n");
		}
	}

	strcpy(jungbo[i].hakbun,jungbo[eadate-1].hakbun);
	strcpy(jungbo[i].name,jungbo[eadate-1].name);
	jungbo[i].guka=jungbo[eadate-1].guka;
	jungbo[i].suhak=jungbo[eadate-1].suhak;
	jungbo[i].c=jungbo[eadate-1].c;
	eadate--;
	outdata=fopen("data.txt","w");
	for(i=0 ; i<eadate ; i++)
	{
		fprintf(outdata, "%s %s %d %d %d", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c);
		fprintf(outdata, "\n");
	}
	fclose(outdata);
	printf("삭제 완료!\n");
	while(1)
	{

		printf("1.돌아가기.:");
		scanf("%d", &g);
		if(g==1)
		{
			main();
			return;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}

}

