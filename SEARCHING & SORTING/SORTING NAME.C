//program to sort names in ascending order

#include<stdio.h>
#include<conio.h>
#include<string.h>
typedef struct student
{
	char name[20];
	int rol;
}st;
void list(st [],st [],int);
void main()
{
	st s1[17],s2[17];
	int i,k,n,j;
	clrscr();
	printf("Enter how many names you want:-\t");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		printf("\n\n");
		printf("Enter your name:-\t");
		flushall();
		scanf("%s",&s1[i].name);
		printf("\nEnter your roll no:-\t");
	       scanf("%d",&s1[i].rol);
	}
	printf("\n\nThe unsorted names are:-\n");

	for(k=0;k<n;k++)
	{
		printf("\n\n%s\t\t",s1[k].name);
		printf("%d",s1[k].rol);
	}
	list(s1,s2,n);
	getch();
}
void list(st s1[17],st s2[17],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j>=0;j--)
		{
			if((strcmp(s1[j].name,s1[j-1].name))<0)
			{
				s2[0]=s1[j];
				s1[j]=s1[j-1];
				s1[j-1]=s2[0];
			}
		}
	}

	printf("\nThe sorted list is:\n");
	for(i=0;i<n;i++)
	{
		puts(s1[i].name);
		printf("\n");
	}
}