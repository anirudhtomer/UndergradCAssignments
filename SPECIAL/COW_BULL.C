//GAME:- COWS & BULLS

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<process.h>

typedef struct game
{
	int bull,cow,num,cnt;
}bulley;

int getkey();
int chset();
void sep(int *,int);
void win(int);

void main()
{

	int i,j,k=0,a[4],b[4],num2,x,ret;

	bulley b1[15];
	b1[k].cnt=0;
	num2=chset();
	sep(b,num2);

	do
	{

		ret=getkey();
		clrscr();

		switch(ret)
		{
			case 66:clrscr();
				exit(0);
			case 28:
				printf("\n\nPRESS \"F8\" TO EXIT or \"Enter\" to continue\n\n");

				printf("NUMBER\t  COWS\t  BULLS\t  CHANCE");
				if(k)
				printf("\n");

				for(i=0;i<k;i++)
				{
					printf("\n%d\t     %d\t       %d\t%d",b1[i].num,b1[i].cow,b1[i].bull,b1[i].cnt);
				}
				printf("\n\n\nEnter \"4 DIGIT\" Number....");
				scanf("%4d",&b1[k].num);
				sep(a,b1[k].num);
				b1[k].cnt=k+1;

				for(i=0,b1[k].cow=0,b1[k].bull=0;i<4;i++)
				{
					for(j=0;j<4;j++)
					{
						if(a[i]==b[j])
						{
							if(i==j)
								b1[k].bull++;
							else
								b1[k].cow++;
							break;
						}
					}
				}
				printf("  :-  %d COW  & %d BULL",b1[k].cow,b1[k].bull);
				k++;
		}

	}while( b1[k-1].bull!=4 && k<15 );

	if(k<15)
	{
		delay(1000);
		win(k);
	}
	else
	{
		printf("\n\n\nSORRY, YOU WERE NOT ABLE TO COMPLETE GAME IN 15 CHANCES\n\nSO YOU LOSE IT");
		delay(1000);
		exit(0);
	}
	getch();
}

int getkey()
{
	union REGS i,o;
	while(!kbhit())

	i.h.ah=0;
	int86 (22,&i,&o);
	return(o.h.ah);
}

void win(int cnt)
{
	clrscr();
	printf("**************CONGRATS**************\n\nYOU TOOK %d CHANCES WIN THE GAME",cnt);
}
void sep(int *a,int n)
{
	int i,quo;
	for(quo=n,i=3;i>=0;i--)
	{
		a[i]=quo%10;
		quo=quo/10;
	}
}

int chset()
{
	int set,alp;
	clrscr();
	printf("CHOOSE QUESTION SET (between 1 & 10):-\t");
	scanf("%d",&set);
	switch(set)
	{
		case 1: alp=4536;
			break;
		case 2: alp=9785;
			break;
		case 3: alp=7012;
			break;
		case 4: alp=1524;
			break;
		case 5: alp=9031;
			break;
		case 6: alp=8210;

			break;
		case 7: alp=6095;
			break;
		case 8: alp=7932;
			break;
		case 9: alp=4956;
			break;
		case 10: alp=2134;
			 break;
		default: chset();
	}
	return alp;
}
