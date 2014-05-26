//program to interchange elements at even & odd positions

#include<stdio.h>
#include<conio.h>

void main()
{
	int i,n,j;
	float arr[20],temp;
	clrscr();

	printf("\nenter the size of the array:-\t");
	scanf("%d",&n);

	printf("\n");

	for(i=0;i<n;i++)
	{
		printf("Enter the Element %d:-\t",i+1);
		scanf("%f",&arr[i]);
	}
	printf("\n\nUNMODIFIED ARRAY\n");
	for(i=0;i<n;i++)
	{
		printf("\n%f",arr[i]);

	}

	for(i=0,j=0;i<n;i+=1)
	{
		if(i%2!=0)
	      {
			j=i;
			temp=arr[j];
			arr[j]=arr[j-1];
			arr[j-1]=temp;
	      }

	}

	printf("\n\nMODIFIED ARRAY\n");
	for(i=0;i<n;i++)
	{
		printf("\n%f",arr[i]);

	}

	getch();
}