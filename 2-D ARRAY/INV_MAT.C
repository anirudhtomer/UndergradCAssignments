//Program to find the inverse of  Matrix

#include<stdio.h>
#include<conio.h>
#include<math.h>

void cofac(int [3][3]);
void display(int [3][3]);
void inver(int [3][3],int);

void main()
{
	int a[3][3],i,j;
	clrscr();
	printf("\n\nEnter the MATRIX:\n");
	for(i=0;i<3;i++)
	{
		printf("\nEnter elements of row %d",i+1);
		for(j=0;j<3;j++)
		{
			printf("\nEnter element %d:-\t",j+1);
			scanf("%d",&a[i][j]);
		}
	}
	display(a);
	getch();
	cofac(a);
	getch();
}
void cofac(int a[3][3])
{
	int i,j,k,l,co[3][3],m[4],cnt=0,det,sum=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0,cnt=0;k<3;k++)
			{
				for(l=0;l<3;l++)
				{
					if(k!=i&&l!=j)
					{
						m[cnt]=a[k][l];
						cnt++;
					}
				}
			}
			co[i][j]=pow(-1,i+j)*(m[0]*m[3]-m[1]*m[2]);
			if(i>0)
				continue;
			sum=sum+a[i][j]*co[i][j];
		}
	}
	det=sum;
	clrscr();
	printf("The ORIGINAL matrix is:-\n");
	display(a);
	printf("\n\nThe COFACTOR of the given matrix is:-\n\n");
	display(co);
	printf("\n\nThe DETERMINANT of the matrix is %d",det);
	getch();
	inver(co,det);

}
void display(int x[3][3])
{
	int i,j;
	for(i=0;i<3;i++)
	{
		printf("\n");
		for(j=0;j<3;j++)
		{
			printf("%d\t",x[i][j]);
		}
	}
}

void inver(int co[3][3],int det)
{
	int i,j;
	float adj[3][3];
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			adj[j][i]=co[i][j];
		}
	}
	clrscr();
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			adj[i][j]=(float)adj[i][j]/det;
		}
	}

	printf("\n\nThe inverse of the matrix is:-\n");
	for(i=0;i<3;i++)
	{
		printf("\n");
		for(j=0;j<3;j++)
		{
			printf("%f\t",adj[i][j]);
		}
	}
}