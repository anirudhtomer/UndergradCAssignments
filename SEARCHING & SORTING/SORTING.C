//program to do different types of sorting

#include<stdio.h>
#include<conio.h>
#include<process.h>

int i,j,k,*p,n,temp,arr[20];

void enter();
void display(int *,int);

void menu();
void swch(int *,int);

void bub_sort(int *,int);
void sel_sort(int *,int);
void ins_sort(int *,int);
void shl_sort(int *,int);
void rad_sort(int *,int);

void main()
{
	clrscr();
	enter();
	getch();
}

void menu()
{
	printf("\n\n**********SORT MENU*********");
	printf("\n\n1.BUBBLE sort\n2.SELECTION SORT\n3.INSERTION SORT\n4.SHELL SORT\n5.RADIX SORT");

}

void swch(int *arr,int n)
{
	int ch;

	printf("\n\nEnter Your Choice:-\t");
	scanf("%d",&ch);

	switch(ch)
	{
		case 1: bub_sort(arr,n);
			break;

		case 2:	sel_sort(arr,n);
			break;

		case 3:	ins_sort(arr,n);
			break;

		case 4: shl_sort(arr,n);
			break;

		case 5:	rad_sort(arr,n);
			break;

		default: exit(0);
	}
}

void enter()
{

	printf("Enter number of elements in the array:-\t");
	scanf("%d",&n);
	p=arr;
	for(i=0;i<n;i++)
	{
		printf("\nEnter Element %d:-\t",i+1);
		scanf("%d",p);
		p++;
	}
	menu();
	swch(arr,n);
}

void display(int *arr,int n)
{
	printf("\n\nTHE SORTED ELEMENTS OF ARRAY ARE IN ORDER:-\n\n");

	for(i=0;i<n;i++)
	{
		printf("%d\t",*(arr+i));
	}
}

void bub_sort(int *arr,int n)
{

	for(i=0;i<=n-1;i++)    // i  represnts number of passes
	{
		for(j=0;j<n-i-1;j++) // j stands for array element
		{
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	display(arr,n);
}

void sel_sort(int *arr,int n)
{
	int min;

	for(i=0;i<n-1;i++)   // i is for number of passes
	{
		min=arr[i];
		for(j=i+1;j<n;j++)
		{
			if(min>arr[j])
			{
				temp=min;
				min=arr[j];
				arr[j]=temp;
			}
		}
		arr[i]=min;
	}
	display(arr,n);
}

void ins_sort(int *a,int n)
{
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j>0;j--)
		{
			if(a[j]<a[j-1])
			{
				temp=a[j];
				a[j]=a[j-1];
				a[j-1]=temp;
			}
			else
			{
				break;
			}
		}
	}
	display(a,n);
}

void rad_sort(int *a,int n)
{
	int large=a[0],m,p,div=0,cnt1=0,cnt2,rad[10][20],a1[10],total[10],ori[20];

	for(i=1,ori[0]=a[0];i<n;i++)
	{
		if(large<a[i])
			large=a[i];
		ori[i]=a[i];
	}

	for(j=0,p=large;p!=0;j++)
	{
		p=p/10;
		cnt1++;
	}

	for(i=0,div=10;i<cnt1;i++,div*=10)
	{

		for(j=0;j<10;j++)
			total[j]=-1;

		for(j=0;j<n;j++)
		{
			a1[j]=a[j]%10;
			total[a1[j]]=-1;
			for(k=0;k<=j;k++)
			{
				if(a1[k]==a1[j])
					total[a1[j]]++;

			}

			rad[a1[j]][total[a1[j]]]=ori[j];
		}
		for(m=0,j=0;m<10;m++)
		{
			for(p=0;p<=total[m];p++,j++)
			{
				a[j]=rad[m][p]/div;
				ori[j]=rad[m][p];
			}
		}

	}
	printf("\n\nTHE SORTED ARRAY IS:-\n\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<=total[i];j++)
		{
			printf("%d\t",rad[i][j]);
		}
	}
}

void shl_sort(int *a,int n)
{
	int d,i,j;
	for(d=n/2;d!=0;d=d/2)  //value of "d" changes
	{
		for(i=0;i<n;i++)     //insertion sort starts
		{
			for(j=i;j-d+1>0;j-=d)  //only elements of list (depending on value of n) are compared
			{
				if(a[j]<a[j-d])   //comparison
				{
					temp=a[j];
					a[j]=a[j-d];
					a[j-d]=temp;
				}
				else
					break;
			}
			
		}
		
	}
	display(a,n);
}

