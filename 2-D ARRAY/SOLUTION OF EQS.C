/*	ANIRUDH TOMER....SE COMP-I....ROLL NO:42028

	program to solve simultaneous equations using :
1.CRAMMERS RULE....2.GAUSS SIEDAL RULE....3.GAUSS ELIMINATION METHOD

test	x+2y-z=2              solution : 22,-8,4
	3x+8y+2z=10
	4x+9y-z=12    */


#include <stdio.h>
#include<conio.h>
#include<math.h>
#include<process.h>

void crammer(float [3][3],float [3]);
void gs_sdl(float[3][3],float [3]);
void gs_ele();

void copy(float [3][3],float [3][3]);
float det(float [3][3]);
void reduce(float [3][4],int ,int);

void main()
{
	float a[3][3],con[3];
	int i,j,chmnu;
	clrscr();

	printf("\nEnter the Coefficient Matrix(3 X 3) :\n ");
	for(i=0;i<3;i++)
	{
		printf("\nEnter for EQUATION %d:-\t",i+1);
		for(j=0;j<3;j++)
		{
		    scanf("%f",&a[i][j]);
		}
	}

	printf("\nEnter Right Side constants of three equations:-\t");
	for(i=0;i<3;i++)
	{
	  scanf("%f",&con[i]);
	}

	while(1)
	{
		clrscr();
		printf("***************MENU************\n\n");
		printf("1.CRAMMERS RULE\n2.GAUSS SIEDAL RULE\n3.GAUSS ELIMINATON METHOD\n4.EXIT");
		printf("\n\nEnter your choice:-\t");
		scanf("%d",&chmnu);
		switch(chmnu)
		{
			case 1: crammer(a,con);
				break;
			case 2: gs_sdl(a,con);
				break;
			case 3: gs_ele();
				break;
			case 4: exit(0);
		}
		getch();
	}
}
void crammer(float a[3][3],float con[3])
{
	float b[3][3],x[3];
	int i,j;

	for(i=0;i<3;i++)
	{
		copy(a,b);
		for(j=0;j<3;j++)
		{
			b[j][i]=con[j];
		}
		x[i]=det(b)/det(a);
	}


	printf("\nSolution: ");
	for(i=0;i<3;i++)
	printf("\t%0.2f",x[i]);
}

void gs_sdl(float a[3][3],float con[3])
{
	float x[3]={0.00,0.00,0.00},epsilon,old[3];
	int i,j;

	for(i=0;i<30 ;i++)
	{
		old[0]=x[0];
		old[1]=x[1];
		old[2]=x[2];
		x[0]=1/a[0][0]*(con[0]-a[0][1]*x[1]-a[0][2]*x[2]);
		x[1]=1/a[1][1]*(con[1]-a[1][0]*x[0]-a[1][2]*x[2]);
		x[2]=1/a[2][2]*(con[2]-a[2][0]*x[0]-a[2][1]*x[1]);

		epsilon=fabs(old[0]-x[0]);  //'fabs' is version of 'abs' for float values

		if(fabs(old[1]-x[1])>epsilon)
		{
			epsilon=fabs(old[1]-x[1]);
		}

		if(fabs(old[2]-x[2])>epsilon)
		{
			epsilon=fabs(old[2]-x[2]);
		}

		if(epsilon<.0001)
			break;
	}

	printf("\nSolution: ");
	for(i=0;i<3;i++)
	   printf("\t%7.2f",x[i]);
}

float det(float a[3][3])
{
	float val=0.00;
	val=val+a[0][0]*(a[1][1]*a[2][2]-a[2][1]*a[1][2]);
	val=val-a[0][1]*(a[1][0]*a[2][2]-a[2][0]*a[1][2]);
	val=val+a[0][2]*(a[1][0]*a[2][1]-a[2][0]*a[1][1]);
	return(val);
}

void copy(float a[3][3],float b[3][3])
{
	int i,j;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			b[i][j]=a[i][j];
		}
	}
}

void gs_ele()
{
	float a[3][4],x[3];
	int i,j;

	clrscr();

	printf("\n Enter a 3 X 3 Coefficient Matrix:\n");

	for(i=0;i<3;i++)
	{
		printf("\nEnter the equation %d:-\t",i+1);
		for(j=0;j<3;j++)
		{
			scanf("%f",&a[i][j]);
		}
	}

	printf("\nEnter the three right side constants:-\t");
	for(i=0;i<3;i++)
	{
		scanf("%f",&a[i][3]);
	}

	for(i=0;i<2;i++)
	{
		reduce(a,i,i);
	}

	x[2]=a[2][3]/a[2][2];
	x[1]=1/a[1][1]*(a[1][3]-x[2]*a[1][2]);
	x[0]=1/a[0][0]*(a[0][3]-x[1]*a[0][1]-x[2]*a[0][2]);

	printf("\n\nSolution=");
	for(i=0;i<3;i++)
	{
		printf("\t%0.2f",x[i]);
	}

}

void reduce(float a[3][4],int pivot ,int col)
{
    int i,j;
    float factor;

    factor=a[pivot][col];

    for(i=0;i<4;i++)
    {
	  a[pivot][i]/=factor;
    }

    for(i=pivot+1;i<3;i++)
    {
	factor=a[i][col];
	for(j=0;j<4;j++)
	{
	     a[i][j]=a[i][j]-a[pivot][j]*factor;
	}
    }
}

