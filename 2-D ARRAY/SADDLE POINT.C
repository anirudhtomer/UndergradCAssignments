//TO FIND SIDDLE POINTS IN A GIVEN MATRIX
/*siddle points are those elements ' a[i][j]' which have smallest value in their
 row 'i' and biggest value in column 'j ' */

#include<sc.h>

void siddle_pt(int [MAX][MAX],int,int);

void main()
{
	int i,j,arr[MAX][MAX],row,col;

	clrscr();
	printf("Enter the size of the array:-\t");
	scanf("%d%d",&row,&col);

	printf("\n");
	for(i=0;i<row;i++)
	{
		printf("\nENTER THE ELEMENTS OF ROW %d:-\t",i+1);
		for(j=0;j<col;j++)
		{
			scanf("%d",&arr[i][j]);
		}
	}

	siddle_pt(arr,row,col);

	getch();
}

void siddle_pt(int a[MAX][MAX],int r,int c)
{
	int big[MAX],small[MAX],i,j,min,max,cnt;


	clrscr();
	printf("\n\nTHE SMALLEST VALUES OF EACH ROW ARE PRESENT IN THE COLUMNS\n\n ");

	for(i=0;i<r;i++)
	{
		small[i]=0;
		min=a[i][0];
		for(j=1;j<c;j++)  //TO FIND THE SMALLEST ELEMENT IN A ROW
		{
			if(min>a[i][j])
			{
				min=a[i][j];
				small[i]=j;
			}
		}
		printf("%d\t",small[i]+1);

	}


	printf("\n\nTHE BIGGEST VALUES OF EACH COLUMN ARE PRESENT IN THE ROWS\n\n ");
	for(j=0;j<c;j++)
	{
		big[j]=0;
		max=a[0][j];

		for(i=1;i<r;i++) // TO FIND THE BIGGEST ELEMENT IN A COLUMN
		{
			if(max<a[i][j])
			{
				max=a[i][j];
				big[j]=i;
			}
		}
		printf("%d\t",big[j]+1);
	}

	printf("\n\n\n\nTHE MATRIX YOU HAVE ENTERED IS :-\n\n");
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%d\t\t",a[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	int flag=0;
	for(i=0,cnt=0;i<r;i++)
	{
		if(big[small[i]]==i)
		{
			printf("\nTHE SIDDLE POINT %d IS      %d  ",++cnt,a[i][small[i]]);
			flag=1;
		}
	}
	if(!flag)
		printf("\n\nTHERE IS NO SIDDLE POINT PRESENT");


}