//ANIRUDH TOMER....SE COMP-I....ROLL NO:42028
//program to solution of simultaneous equations using GAUSS SIEDAL RULE

#include<stdio.h>
#include<conio.h>

void gauss(int [3][4]);
void main()
{
	int i,j,equ[3][4];
	clrscr();

	printf("Enter the equations:-\t");
	for(i=0;i<3;i++)
	{
		printf("\n\nEnter the equation %d:-\t",i+1);
		for(j=0;j<4;j++)
		{
			scanf("%d",&equ[i][j]);
		}
	}
	gauss(equ);
	getch();
}
void gauss(int eq[3][4])
{
	int i,j,e,solu[4],sndt[3][4],flag=0;
	float ans[3];
	while(1)
	{
	}
}
