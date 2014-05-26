//ANIRUDH TOMER....SE COMP-I....ROLL NO:42028

//program for OPERATIONS on POLYNOMIALS

#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<math.h>

typedef struct polynomial
{
	int coef,exp;
}poly1;

int enter(poly1 [15]);
void display(poly1 [15],int);
void add();
void mul();
void check(poly1 [],int);
void eval();

void main()
{
	int k,ch;
	poly1 p1[15];

	do
	{
		clrscr();
		printf("\n\n***********MENU**************\n\n");
		printf("1.ADDITON of polynomials\n2.MULTIPLICATION of polynomials\n3.EVALUATION of polynomial\n4.EXIT");
		printf("\nEnter your choice:-\t");
		scanf("%d",&ch);
		switch(ch)
		{

			case 1:	add();
				break;
			case 2: mul();
				break;
			case 3: eval();
				break;
			case 4: exit(0);

		}
		getch();
	}while(1);

}

int enter(poly1 p[15])
{
	int i,j;
	int tco,tex;
	char ch='+';

	for(i=0;ch=='+';i++)
	{
		flushall();
		printf("\nEnter term %d:-\t",i+1);
		scanf("%d,%d%c",&tco,&tex,&ch);
		p[i].coef=tco;
		p[i].exp=tex;

	}
	j=i;
	return j;
}

void display(poly1 p[15],int s)
{
	int i;
	for(i=s-1;i>=0;i--)
	{
		if(!p[i].exp)
			printf(" %d +",p[i].coef);

		else
		{
			if(p[i].coef==1)
				printf(" X^%d +",p[i].exp);

			else
				printf(" %d X^%d +",p[i].coef,p[i].exp);
		}
	}
	printf("\b%c",NULL);
}

void add()
{

	poly1 p1[15],p2[15],res[15];
	int i,l,k1,k2,sp,cnt,flag=0;

	printf("\nEnter the 1st polynomial( coeff1,exp1 + coeff2,exp2.... ):\n");
	k1=enter(p1);
	printf("\n\nEnter the 2nd polynomial( coeff1,exp1 + coeff2,exp2.... ):\n");
	k2=enter(p2);

	for(i=0;i<k1;i++)
	{
		res[i]=p1[i];
	}
	sp=k1;
	for(i=0;i<k2;i++,flag=0)
	{
		for(l=0,cnt=0;l<sp;l++)
		{
			if(p2[i].exp==res[l].exp)
			{
				flag=1;
				break;
			}
			else
				cnt++;
		}
		if(flag)
		{
			res[l].coef=res[l].coef+p2[i].coef;
		}
		if(flag!=1 && cnt==l)
		{
			res[l]=p2[i];
			sp++;
		}
	}
	clrscr();
	printf("THE FIRST POLYNOMIAL IS:\n");
	check(p1,k1);

	printf("\n\nTHE SECOND POLYNOMIAL IS:\n");
	check(p2,k2);

	printf("\n\nTHE SUM OF THE POLYNOMIALS IS:\n");
	check(res,sp);
}

void mul()
{

	poly1 p1[15],p2[15],res[30];
	int i,j,k1,k2,sp=0;

	printf("\nEnter the 1st polynomial( coeff1,exp1 + coeff2,exp2.... ):\n");
	k1=enter(p1);
	printf("\n\nEnter the 2nd polynomial( coeff1,exp1 + coeff2,exp2.... ):\n");
	k2=enter(p2);

	for(i=0;i<k1;i++)
	{
		for(j=0;j<k2;j++)
		{
			res[sp].coef=p1[i].coef*p2[j].coef;
			res[sp].exp=p1[i].exp+p2[j].exp;
			sp++;
		}
	}

	clrscr();
	printf("THE FIRST POLYNOMIAL IS:\n");
	check(p1,k1);

	printf("\n\nTHE SECOND POLYNOMIAL IS:\n");
	check(p2,k2);

	printf("\n\nTHE PRODUCT OF THE POLYNOMIALS IS:\n");
	check(res,sp);
}

void check(poly1 x[30],int s)
{
	int i,j,k,siz;
	poly1 ret[15],temp[15];
	for(i=0;i<s;i++)
	{
		if(x[i].coef!=0)
		{
			for(j=i+1;j<s;j++)
			{
				if(x[i].exp==x[j].exp)
				{
					x[i].coef=x[i].coef+x[j].coef;
					x[j].coef=0;
				}
			}
		}
	}

	for(i=0,siz=0;i<s;i++)
	{
		if(x[i].coef!=0)
		{
			ret[siz]=x[i];
			siz++;
		}
	}

	for(i=0;i<siz-1;i++)
	{
		for(j=i;j>=0;j--)
		{
			if(ret[j+1].exp<ret[j].exp)
			{
				temp[0]=ret[j+1];
				ret[j+1]=ret[j];
				ret[j]=temp[0];
			}
		}
	}

	display(ret,siz);
}
void eval()
{
	poly1 p1[15];
	int subs,sum;
	int i,k1;

	printf("\nEnter the polynomial( coeff1,exp1 + coeff2,exp2.... ):\n");
	k1=enter(p1);
	printf("\nEnter the value to be substituted:-\t");
	scanf("%d",&subs);

	for(i=0,sum=0;i<k1;i++)
	{
		sum=sum+p1[i].coef*pow(subs,p1[i].exp);
	}
	clrscr();
	printf("The Polynomial entered is :-\t");
	check(p1,k1);
	printf("\n\nThe value substituted is %d",subs);
	printf("\n\nAns is %d",sum);
}























