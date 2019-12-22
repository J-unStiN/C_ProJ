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
	printf("1.�߰� 2.�˻� 3.����\n4.���� 5.����\n");	
	julcui();
	while(1)
	{
		printf("������ �۾��� �Է��ϼ���.:");
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
			printf("�߸��� �Է��Դϴ�.\n");
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
		printf("�۾��� �Է��ϼ���.(1.�߰�, 2.����, 3.�ʱ�ȭ������):");
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
			printf("�߸��� �Է��Դϴ�.\n");
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
		printf("�й��� �Է��ϼ���.:");
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
			printf("�й��ߺ�!\n");
		}
		else
		{
			break;
		}
	}

	printf("�̸��� �Է��ϼ���.:");
	scanf("%s", &cup.name);
	printf("���������� �Է��ϼ���.:");
	scanf("%d", &cup.guka);
	printf("���������� �Է��ϼ���.:");
	scanf("%d", &cup.suhak);
	printf("C��������� �Է��ϼ���.:");
	scanf("%d", &cup.c);
	printf("  �й�    �̸�   ����  ���� C���\n");
	printf("%8s %6s  %3d   %3d   %3d\n", cup.hakbun, cup.name, cup.guka, cup.suhak, cup.c);
	outdata=fopen("data.txt","a");
	fprintf(outdata, "%s %s %d %d %d", cup.hakbun, cup.name, cup.guka, cup.suhak, cup.c);
	fprintf(outdata, "\n");
	fclose(outdata);
	eadate++;
	printf("�߰� �Ϸ�!\n");
	while(1)
	{
		printf("1.�߰� �׸����� ����, 2.���ư���");
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
			printf("�߸��� �Է��Դϴ�.\n");
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
		printf("������ �й��� �Է��ϼ���.:");
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
			printf("���������ʴ� �й��Դϴ�.\n");
		}
	}
	printf("  �й�    �̸�   ����  ���� C���\n");
	printf("%8s %6s  %3d   %3d   %3d\n", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c);
	printf("������ ���������� �Է��ϼ���.:");
	scanf("%d", &a);
	printf("������ ���������� �Է��ϼ���.:");
	scanf("%d", &b);
	printf("������ C��������� �Է��ϼ���.:");
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
	printf("���� �Ϸ�!\n");
	while(1)
	{
		printf("1.�߰� �׸����� ����, 2.���ư���");
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
			printf("�߸��� �Է��Դϴ�.\n");
		}
	}
}


void list()
{
	int i=0;
	int avr,sum;
	int g;
	system("cls");
	printf("<���>\n");
	printf("  �й�    �̸�   ����  ���� C���  �հ�    ���\n");
	for(i=0 ; i<eadate ; i++)
	{
		sum=jungbo[i].guka+jungbo[i].suhak+jungbo[i].c;
		avr=(jungbo[i].guka+jungbo[i].suhak+jungbo[i].c)/3;
		printf("%8s %6s  %3d   %3d   %3d    %3d    %3d\n", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c, sum, avr);
	}

	while(1)
	{
		printf("1.�����ϱ� 2.���ư���.:");
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
			printf("�߸��� �Է��Դϴ�.\n");
		}
	}
}

void arrg_main()
{
	system("cls");

	while(1)
	{
		int h;
		printf("1.������, 2.�й���");
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
			printf("�߸��� �Է��Դϴ�.\n");
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
	printf("<������ ����>\n");
	printf("  �й�    �̸�   ����  ���� C���  �հ�    ���\n");
	for(i=0 ; i<eadate ; i++)
	{
		sum=jungbo[i].guka+jungbo[i].suhak+jungbo[i].c;
		avr1=(jungbo[i].guka+jungbo[i].suhak+jungbo[i].c)/3;
		printf("%8s %6s  %3d   %3d   %3d    %3d    %3d\n", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c, sum, avr1);
	}

	while(1)
	{
		printf("1.�й��� ������, 2.���ư���");
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
			printf("�߸��� �Է��Դϴ�.\n");
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
	printf("<�й��� ����>\n");
	printf("  �й�    �̸�   ����  ���� C���  �հ�    ���\n");
	for(i=0 ; i<eadate ; i++)
	{
		sum=jungbo[i].guka+jungbo[i].suhak+jungbo[i].c;
		avr1=(jungbo[i].guka+jungbo[i].suhak+jungbo[i].c)/3;
		printf("%8s %6s  %3d   %3d   %3d    %3d    %3d\n", jungbo[i].hakbun, jungbo[i].name, jungbo[i].guka, jungbo[i].suhak, jungbo[i].c, sum, avr1);
	}

	while(1)
	{
		printf("1.������ ������, 2.���ư���");
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
			printf("�߸��� �Է��Դϴ�.\n");
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



		printf("������ �й��� �Է��ϼ���.(���ư���:back):");
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
			printf("���������ʴ� �й��Դϴ�.\n");
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
	printf("���� �Ϸ�!\n");
	while(1)
	{

		printf("1.���ư���.:");
		scanf("%d", &g);
		if(g==1)
		{
			main();
			return;
		}
		else
		{
			printf("�߸��� �Է��Դϴ�.\n");
		}
	}

}

