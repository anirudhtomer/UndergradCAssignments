//KAUN BANEGA SOFTWARE-PATI

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>

int main()
{
	int sum=2000,m,o;
	char ch1[20],ch='y',ch2='y';

	clrscr();
	printf("\nHello Iam ANIRUDH TOMER & Today we will Play **KBS**\n\nWHAT'S YOUR NAME :-\t");
	scanf("%s",ch1);
	printf("\n\nHello %s You Are\n\n*************  WELCOME TO  :-\tKAUN BANEGA SOFTWARE-PATI  *************\n",ch1);
	printf("\n\n####RULES:-####\n\n\n1. FIVE QUESTIONS will be asked in this QUIZ\n\n2. You May CHOOSE ANY ONE OF 4 CHOICES \n\n3. You will get $5000 for the RIGHT ANSWER &\n\n4. $2500 will be deducted for the WRONG ANSWER\n\n5. You Will Be Given initial Amount Of $2000\n\n6. You can QUIT At Any Time you want\n\n7. If Your Money Goes Below Zero You Have To QUIT");


	for(;ch=='y';)
	{
	printf("\n\nSHOULD WE START:-\t");
	flushall();
	scanf("%c",&ch2);

	if(ch2=='y')
	      {
		clrscr();
		printf("\n\n\n\n*******************HERE WE START************************* ");
		printf("\n\n\nQUESTION I. When was MAHATMA GANDHI born?");
		printf("\n1: 2 October 1869\t2: 15 August 1947\n3: 26 January 1895\t4: 31 January 1948");
		printf("\n\nEnter Your Choice:-\t");
		scanf("%d",&m);
		switch(m)
		{
			case 1:	printf("\nCONGRATS YOU GOT IT RIGHT");
				sum=sum+5000;
				printf("\n\nYour Net MONEY= $%d",sum);
				break;
			case 2:
			case 3:
			case 4:	printf("\nSORRY YOU ANSWERED WRONG");
				sum=sum-2500;
				printf("\n\nYour Net Money= $%d",sum);
				break;
			default : printf("\n\nENTER PROPER CHOICE ONLY");
				  break;
		}


	if(sum>0)
	{
	printf("\n\n\nQUESTION II. Which is Longest River?");
	printf("\n1: River Missisippi & Missouri\t2: River Amazon \n3: River Nile\t4: River ganga");
	printf("\n\nEnter Your Choice:-\t");
	scanf("%d",&m);
	switch(m)
	{
		case 3:		printf("\nCONGRATS YOU GOT IT RIGHT");
				sum=sum+5000;
				printf("\n\nYour Net MONEY= $%d",sum);
				break;
		case 2:
		case 1:
		case 4:		printf("\nSORRY YOU ANSWERED WRONG");
				sum=sum-2500;
				printf("\n\nYour Net Money= $%d",sum);
				break;
		default:        printf("\n\nENTER PROPER CHOICE ONLY");
	}
	if(sum>0)
	{
	printf("\n\n\nQUESTION III. Where is IBIZA ISLAND Located?");
	printf("\n1: Caspian Sea\t2: Meditarrian Sea\n3: Black Sea\t4: Red Sea");
	printf("\n\nEnter Your Choice:-\t");
	scanf("%d",&m);
	switch(m)
	{
		case 2:	printf("\nCONGRATS YOU GOT IT RIGHT");
				sum=sum+5000;
				printf("\n\nYour Net MONEY= $%d",sum);
				break;
		case 1:
		case 3:
		case 4:		printf("\nSORRY YOU ANSWERED WRONG");
				sum=sum-2500;
				printf("\n\nYour Net Money= $%d",sum);
				break;
		default :	printf("\n\nENTER PROPER CHOICE ONLY");
	}

	printf("\n\n\nQUESTION IV. Whom did India Managed To Beat In 20-20 World-Cup Semis?");
	printf("\n1: Pakistan\t2: Sri Lanka\n3: New Zealand\t4: Australia");
	printf("\n\nEnter Your Choice:-\t");
	scanf("%d",&m);
	switch(m)
	{
		case 4:	printf("\nCONGRATS YOU GOT IT RIGHT");
				sum=sum+5000;
				printf("\n\nYour Net MONEY= $%d",sum);
				break;
		case 1:
		case 2:
		case 3:		printf("\nSORRY YOU ANSWERED WRONG");
				sum=sum-2500;
				printf("\n\nYour Net Money= $%d",sum);
				break;
		default :	printf("\n\nENTER PROPER CHOICE ONLY");
	}
	if(sum>0)

	{
	printf("\n\n\nQUESTION V. Who Won EURO-CUP 2008?");
	printf("\n1: Italy\t2: Spain\n3: France\t4: Germany");
	printf("\n\nEnter Your Choice:-\t");
	scanf("%d",&m);
	switch(m)
	{
		case 2:	printf("\nCONGRATS YOU GOT IT RIGHT");
				sum=sum+5000;
				printf("\n\nYour Net MONEY= $%d",sum);
				break;
		case 1:
		case 3:
		case 4:		printf("\nSORRY YOU ANSWERED WRONG");
				sum=sum-2500;
				printf("\n\nYour Net Money= $%d",sum);
				break;
		default :	printf("\n\nENTER PROPER CHOICE ONLY");
	}
	}
	else
	 printf("\n\nYour Balance Is Less than Zero\n\n@@@@@Ok Good Bye Sir @@@@@");
	}
	else
	 printf("\n\nYour Balance Is Less Than Zero\n\n@@@@@Ok Good Bye Sir @@@@@");
       }
	else
	 printf("\n\nYour Balance Is Less than Zero\n\n@@@@@Ok Good Bye Sir @@@@@");
       }
       else
	 printf("\n\n\n\n@@@@@ Good Bye Sir @@@@@");
	 printf("\n\ndo you wish to play again:-\t");
	 flushall();
	 scanf("%c",&ch);
       }
	getch();
	return 0;
}