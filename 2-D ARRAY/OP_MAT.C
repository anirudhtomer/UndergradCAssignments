//ANIRUDH TOMER....SE COMP-I....ROLL NO:42028
//program for operations on matrices

#include<stdio.h>
#include<conio.h>
#include<process.h>

int i,j,k;

void swch();
void menu();

void sum_mat();
void sub_mat();
void mul_mat();
int tra_mat(int [10][10]);
void sym_mat();
void skw_mat();

void enter(int [10][10],int,int);
void display(int [10][10],int,int);

void main()
{
	clrscr();
	swch();
	getch();
}

void enter(int a1[10][10],int r1,int c1)
{
	clrscr();


	printf("Enter the matrix:-\n\n");
	for(i=0;i<r1;i++)
	{
		printf("ENTER THE ELEMENTS OF ROW %d\n",i+1);

		for(j=0;j<c1;j++)
		{
			printf("\nEnter element %d:-\t",j+1);
			scanf("%d",(*(a1+i)+j));
		}
		printf("\n");
	}

}
void menu()
{

	printf("\n\n*********MENU*********\n\n\n");
	printf("\n1.ADDITION of matrices\n\n2.DIFFRENCE of matrices\n\n3.MULTIPLICATION of matrices");
	printf("\n\n4.TRANSPOSE of matrix\n\n5.SYMMETRICITY of a matrix\n\n6.SKEW SYMMETRICITY of a matrix\n\n7.EXIT\n");
}

void swch()
{
	int ch,res[10][10];

	while(1)
	{
	clrscr();
	menu();
	printf("\nEnter choice:-\t");
	scanf("%d",&ch);

	switch(ch)
	{
		case 1: sum_mat();
			break;

		case 2: sub_mat();
			break;

		case 3: mul_mat();
			break;

		case 4:	tra_mat(res);
			break;

		case 5: sym_mat();
			break;

		case 6: skw_mat();
			break;

		case 7: exit(0);

		default: printf("\nEnter proper choice");
	}
	getch();
	}
}

void sum_mat()
{
	int a[10][10],b[10][10],r1,c1,r2,c2,res[10][10];

	printf("\n\nEnter the sizes of two matrices (r1*c1 & r2*c2):-\t");
	scanf("%d*%d & %d*%d",&r1,&c1,&r2,&c2);

	if(r1!=r2 && c1!=c2)
	{
		printf("\nPlease Enter size such that r1=r2 & c1=c2");
		printf("\n\nEnter the sizes of two matrices (r1*c1 & r2*c2):-\t");
		scanf("%d*%d & %d*%d",&r1,&c1,&r2,&c2);
	}

	enter(a,r1,c1);
	enter(b,r2,c2);


	for(i=0;i<r1;i++)
	{

		for(j=0;j<c1;j++)
		{
			res[i][j]=a[i][j]+b[i][j];
		}
	}
	display(res,r1,c1);

}

void sub_mat()
{
	int a[10][10],b[10][10],r1,c1,r2,c2,res[10][10];

	printf("\nEnter the sizes of two matrices (r1*c1 & r2*c2):-\t");
	scanf("%d*%d & %d*%d",&r1,&c1,&r2,&c2);

	if(r1!=r2 && c1!=c2)
	{
		printf("\nPlease Enter size such that r1=r2 & c1=c2");
		printf("\n\nEnter the sizes of two matrices (r1*c1 & r2*c2):-\t");
		scanf("%d*%d & %d*%d",&r1,&c1,&r2,&c2);
	}

	enter(a,r1,c1);
	enter(b,r2,c2);

	for(i=0;i<r1;i++)
	{

		for(j=0;j<c1;j++)
		{
			res[i][j]=a[i][j]-b[i][j];
		}
	}

	display(res,r1,c1);

}

void display(int res[10][10],int rs,int cs)
{
	clrscr();
	printf("\nTHE RESULT IS :-\n\n");

	for(i=0;i<rs;i++)
	{
		for(j=0;j<cs;j++)
		{
			printf("%d\t",*(*(res+i)+j));
		}
		printf("\n\n");
	}

}

void mul_mat()
{
	int a[10][10],b[10][10],r1,c1,r2,c2,res[10][10];

	printf("\nEnter the sizes of two matrices (r1*c1 & r2*c2):-\t");
	scanf("%d*%d & %d*%d",&r1,&c1,&r2,&c2);
	if(c1!=r2)
	{
		printf("\nPlease Enter size such that c1=r2");
		printf("\n\nEnter the sizes of two matrices (r1*c1 & r2*c2):-\t");
		scanf("%d*%d & %d*%d",&r1,&c1,&r2,&c2);
	}

	int sum;

	enter(a,r1,c1);
	enter(b,r2,c2);

	for(i=0;i<r1;i++)
	{
		for(j=0;j<c2;j++)
		{
			sum=0;
			for(k=0;k<c1;k++)
			{
				sum+=a[i][k]*b[k][j];
			}
			res[i][j]=sum;
		}
	}

	display(res,r1,c2);
}

int tra_mat(int res[10][10])
{

	int a[10][10],s;
	printf("\nEnter the size of matrix (rows=columns):-\t");
	scanf("%d",&s);

	enter(a,s,s);

	for(i=0;i<s;i++)
	{
		for(j=0;j<s;j++)
		{
			res[j][i]=a[i][j];
		}
	}
	display(res,s,s);
	return s;
}

void sym_mat()
{
	int r,t_res[10][10],cnt=0;

	r=tra_mat(t_res);

	for(i=0;i<r;i++)
	{
		for(j=0;j<r;j++)
		{
			if(t_res[i][j]==t_res[j][i])
			{
				cnt++;
			}
		}
	}

	if(cnt==r*r)
	{
		printf("\n\n\nIT IS A SYMMETRIC MATRIX");
	}
	else
		printf("\n\n\nIT IS NOT A SYMMETRIC MATRIX");
}

void skw_mat()
{
	int r,t_res[10][10],cnt=0;

	r=tra_mat(t_res);

	for(i=0;i<r;i++)
	{
		for(j=0;j<r;j++)
		{
			if((t_res[i][j]==-t_res[j][i]) && (!t_res[i][i]))
			{
				cnt++;
			}
		}
	}

	if(cnt==r*r)
	{
		printf("\n\n\nIT IS A SKEW SYMMETRIC MATRIX");
	}
	else
		printf("\n\n\nIT IS NOT A SKEW SYMMETRIC MATRIX");
}