//program to perform differnt operations on sets

#include<stdio.h>
#include<conio.h>
#include<process.h>

int i,j,k;

int uni_set(int [],int,int[],int,int[]);
int dif_set(int[],int,int[],int,int[]);
void int_set(int[],int,int[],int,int[]);
void sym_dif(int[],int,int[],int);

void main()
{
	int a1[10],a2[10],n1,n2,res[10],ch;
	clrscr();
	printf("Enter the size of the sets:-\t");
	scanf("%d%d",&n1,&n2);

	printf("\n\nEnter the elements of the 1st set:-\n");
	for(i=0;i<n1;i++)
	{
		printf("\nEnter Element %d:-\t",i+1);
		scanf("%d",&a1[i]);
	}

	printf("\n\nEnter the elements of the 2nd set:-\n");
	for(i=0;i<n2;i++)
	{
		printf("\nEnter Element %d:-\t",i+1);
		scanf("%d",&a2[i]);
	}

	while(1)
	{
	clrscr();
	printf("\n\n*********MENU**********");
	printf("\n\n1.UNION of sets\n2.INTERSECTION of sets\n3.DIFFERENCE of sets");
	printf("\n4.SYMMETRIC difference of sets\n5.EXIT");

	printf("\n\nEnter Choice:-\t");
	scanf("%d",&ch);

	switch(ch)
	{
		case 1:	uni_set(a1,n1,a2,n2,res);
			break;

		case 2:	int_set(a1,n1,a2,n2,res);
			break;

		case 3:	dif_set(a1,n1,a2,n2,res);
			break;

		case 4: sym_dif(a1,n1,a2,n2);
			break;

		case 5: exit(0);

		default:printf("\n\nPlease enter a proper choice");


	}
	getch();
	}
}

int uni_set(int a1[10],int n1,int a2[10],int n2,int uni[10])
{
	int cnt,m=0;

	for(i=0,k=0;i<n1;i++)
	{
		uni[i]=a1[i];
	}
	k=i;

	for(j=0;j<n2;j++)
	{
		for(i=0,m=0;i<k;i++)
		{
			if(uni[i]!=a2[j])
			{
			   m++;
			}
		}
		if(m==k)
		{
			uni[k]=a2[j];
			k++;
		}


	}

	clrscr();
	printf("\n\nTHE UNION OF THE SETS IS:-\n");
	for(i=0;i<k;i++)
	{
		printf("%d   ",uni[i]);
	}
	return k;
}

int dif_set(int a1[10],int n1,int a2[10],int n2,int res[10])
{
	int n;
	for(i=0,k=0;i<n1;i++)
	{
		n=0;
		for(j=0;j<n2;j++)
		{
			if(a1[i]!=a2[j])
			{
				n++;
			}
		}
		if(n==n2)
		{
			res[k]=a1[i];
			k++;
		}
	}
	clrscr();
	printf("\n\nTHE DIFFERNCE OF THE SETS IS:-\n");
	for(i=0;i<k;i++)
	{
		printf("%d   ",res[i]);
	}
	return k;
}

void int_set(int a1[10],int n1,int a2[10],int n2,int res[10])
{
	int n;
	for(i=0,k=0;i<n1;i++)
	{
		for(j=0;j<n2;j++)
		{
			if(a1[i]==a2[j])
			{
				res[k]=a1[i];
				k++;
			}
		}

	}
	clrscr();
	printf("\n\nTHE INTERSECTION OF THE SETS IS:-\n");
	for(i=0;i<k;i++)
	{
		printf("%d   ",res[i]);
	}
}

void sym_dif(int a1[10],int n1,int a2[10],int n2)
{
	int dif1[10],dif2[10],unidif[10],s1,s2,sf,lp;

	s1=dif_set(a1,n1,a2,n2,dif1);
	s2=dif_set(a2,n2,a1,n1,dif2);
	sf=uni_set(dif1,s1,dif2,s2,unidif);

	clrscr();
	printf("\n\nTHE SYMMETRIC DIFFERNCE OF THE SETS IS:-\n");
	for(i=0;i<sf;i++)
	{
		printf("%d   ",unidif[i]);
	}
}