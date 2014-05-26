//ANIRUDH TOMER....SE COMP-I....ROLL NO:42028
//program to solution of simultaneous equations using CRAMMERS RULE

#include<stdio.h>
#include<conio.h>

int det(int [3][4]);
void crammer(int [3][4]);

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
	crammer(equ);
	getch();
}

void crammer(int eq[3][4])
{
	int i,j,e,solu[4],sndt[3][4],flag=0;
	float ans[3];

	solu[0]=det(eq);

	for(e=0;e<3;e++)
	{
		for(i=0;i<3;i++)
		{
			for(j=0,flag=0;j<4;j++)
			{
				if((e==j) && (flag!=1))
				{
					sndt[i][j]=eq[i][3];
					flag=1;
				}
				else
					sndt[i][j]=eq[i][j];
			}
		}
		solu[e+1]=det(sndt);
		ans[e]=(float)(solu[e+1]*1.0/solu[0]);
		printf("\nThe variable %d has value=%.3f",e+1,ans[e]);

	}
}
int det(int a[3][4])
{
	int e1,e2,e3;

	e1=a[0][0]*(a[1][1]*a[2][2]-a[1][2]*a[2][1]);
	e2=-a[0][1]*(a[1][0]*a[2][2]-a[1][2]*a[2][0]);
	e3=a[0][2]*(a[1][0]*a[2][1]-a[1][1]*a[2][0]);

	return(e1+e2+e3);
}