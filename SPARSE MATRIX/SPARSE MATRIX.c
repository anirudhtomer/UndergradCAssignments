//ANIRUDH TOMER....SE COMP-I....ROLL NO:42028
//program for operations on SPARSE MATRIX
//at:- registered trademark


/*the method of addition that has been used here is
unique in the world (according to me).you won't find it any of the books
it has a fantastic logic (completely mine) but it's time & space complexities are high...ANIRUDH TOMER(at)*/

/*the other method is yet to be debugged. it is much more lengthy & has more complex logic
hope i will debug it soon.	SO RELY ON  "void atadd"    at:-trademark */



#include<stdio.h>
#include<conio.h>
#include<process.h>
#define MAX 30
#define sm_bg() for(m=k3;m>(index[l]+cnit);m--)\
		{\
			res[m][0]=res[m-1][0];\
			res[m][1]=res[m-1][1];\
			res[m][2]=res[m-1][2];\
		}\
		res[j][0]=sp2[i][0];\
		res[j][1]=sp2[i][1];\
		res[j][2]=sp2[i][2];\
		k3++;\
		total[l]++;\
		for(m=l+1;m<res[0][0];m++)\
			index[m]++;



void enter(int[MAX][MAX],int,int);
void display(int [MAX][3],int);

int spr(int [MAX][MAX],int ,int,int [MAX][3]);
void sim_tra(int [MAX][MAX],int,int);
void fast_tra(int [MAX][MAX],int,int);
//void add(int [20][20],int[20][20],int,int);    yet to be debugged
void atadd(int [MAX][MAX],int[MAX][MAX],int,int);

void main()
{
	int a[MAX][MAX],b[MAX][MAX],r,c,ch,sp[MAX][3];
	clrscr();

	printf("Enter the size of matrix/matrices:-\t");
	scanf("%d%d",&r,&c);
	enter(a,r,c);
	do
	{
		getch();
		clrscr();
		printf("\n\n********************MENU*******************\n\n");
		printf("1.convert to COMPACT FROM\n2.SIMPLE TRANSPOSE\n3.FAST TRANSPOSE\n4.ADDITION of sparse matrix\n5.Enter NEW MATRIX\n6.EXIT");

		printf("\n\nEnter your choice:-\t");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:	spr(a,r,c,sp);
				break;

			case 2:	sim_tra(a,r,c);
				break;

			case 3: fast_tra(a,r,c);
				break;

			case 4: enter(b,r,c);
				atadd(a,b,r,c);
				break;

			case 5: clrscr();
				printf("Enter the size of matrix/matrices:-\t");
				scanf("%d%d",&r,&c);
				enter(a,r,c);
				break;

			case 6: exit(0);
		}
	}while(1);
}
void enter(int mat[MAX][MAX],int row,int col)
{
	int i,j;
	printf("\n*********ENTER MATRIX********\n\n");
	for(i=0;i<row;i++)
	{
		printf("\nEnter The Elements of row %d:\n",i+1);
		for(j=0;j<col;j++)
		{
			scanf("%d",&mat[i][j]);
		}
	}
}
void display(int spr[MAX][3],int k)
{
	int i,j;

	for(i=0;i<k;i++)
	{
		printf("\n");
		for(j=0;j<3;j++)
		{
			printf("%d\t",spr[i][j]);
		}
		if(i<1)
			printf("\n");

	}
}

int spr(int a[MAX][MAX],int r,int c,int com[MAX][3])
{
	clrscr();
	int i,j,k=1;
	com[0][0]=r;
	com[0][1]=c;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(a[i][j]!=0)
			{
				com[k][0]=i;
				com[k][1]=j;
				com[k][2]=a[i][j];
				k++;
			}
		}
	}
	com[0][2]=k-1;

	printf("\n\nThe sparse matrix is:\n");
	display(com,k);

	return k;
}

void sim_tra(int a[MAX][MAX],int r,int c)
{
	int k,i,j,sp[MAX][3],res[20][3],k1=1;

	k=spr(a,r,c,sp);

	res[0][0]=c,res[0][1]=r,res[0][2]=k-1;

	for(i=0;i<c;i++)
	{
		for(j=1;j<k;j++)
		{
			if(sp[j][1]==i)
			{
				res[k1][0]=sp[j][1];
				res[k1][1]=sp[j][0];
				res[k1][2]=sp[j][2];
				k1++;
			}
		}
	}

	printf("\n\nTHE SIMPLE TRANSPOSE OF THE SPARSE MATRIX IS :-\n");
	display(res,k1);
}
void fast_tra(int a[MAX][MAX],int r,int c)
{
	int k,i,j,sp[MAX][3],res[MAX][3],total[10],cnt,index[15];

	k=spr(a,r,c,sp);

	for(i=0;i<c;i++)
	{
		total[i]=0;
	}
/* total[cnt]++ increases the number of similar types
of elements present in the sparse form.
"cnt" is equal to value of the element in "column 1" of
sparse matrix.
cnt has a maximum value of c-1,
whereas c is number of columns present in actual matrix.*/

	for(i=1;i<k;i++)
	{
		cnt=sp[i][1];
		total[cnt]++;

	}

/*in the following for loop what happens is:-
  variable "i" varies from 1 to "total number of columns - 1"
  for column "0" element index starts from "1" always
  for "i th" element the index is the:-
  index of previous element+ total number of previous elements
  (i.e "element 0 for 1" or "element 1 for 2" as previous elements)
*/
	index[0]=1;

	for(i=1;i<c;i++)
	{
		index[i]=index[i-1]+total[i-1];
	}

	res[0][0]=c,res[0][1]=r,res[0][2]=k-1;

/* index[sp[i][0]]++ increases the index postion for same element present
more than once.
e.g element "0 (column 0)" entry may be present more than once for two
different rows. we have already assigned index postions only to the different
types of columns (i.e 0,1,2,3 for x*4 matrix) but what we can say about their
index postions if present more than once is that :-
"if it's present again increase the index for that type of column by 1
or "index[sp[i][0]]++".*/

	for(i=1;i<k;i++)
	{
		j=index[sp[i][1]];
		index[sp[i][1]]++;

		res[j][0]=sp[i][1];
		res[j][1]=sp[i][0];
		res[j][2]=sp[i][2];

	}
	printf("\n\nTHE FAST TRANSPOSE OF THE SPARSE MATRIX IS :-\n");
	display(res,k);
}
void atadd(int a[MAX][MAX],int b[MAX][MAX],int r,int c)
{
	int i,j,k1,k2,k3,l,index[10],sp1[MAX][3],sp2[MAX][3],res[MAX][3],total[10];
	int cnot=0,cnit=0,m;

	k1=spr(a,r,c,sp1);
	k2=spr(b,r,c,sp2);
	clrscr();

	getch();
	printf("The FIRST sparse matrix is:-\n");
	display(sp1,k1);

	getch();
	printf("\n\nThe SECOND sparse matrix is:-\n");
	display(sp2,k2);

	res[0][0]=sp1[0][0],res[0][1]=sp1[0][1];

	for(i=0;i<res[0][0];i++)
		total[i]=0;

	for(i=1,k3=1;i<k1;i++,k3++)
	{
		res[k3][0]=sp1[i][0];
		res[k3][1]=sp1[i][1];
		res[k3][2]=sp1[i][2];
		total[sp1[i][0]]++;
	}

	index[0]=1;

	for(i=1;i<res[0][0];i++)
	{
		index[i]=index[i-1]+total[i-1];
	}

	for(i=1;i<k2;i++)
	{
		l=sp2[i][0];
		for(j=index[l],cnit=0;j<(index[l]+total[l]);j++)
		{
			if(sp2[i][1]<res[j][1])
			{
				sm_bg();
				goto back;
			}

			if(sp2[i][1]==res[j][1])
			{
				if((res[j][2]+sp2[i][2])!=0)
					res[j][2]=sp2[i][2]+res[j][2];

				else
				{
					for(m=j;m<k3;m++)
					{
						res[m][0]=res[m+1][0];
						res[m][1]=res[m+1][1];
						res[m][2]=res[m+1][2];
					}
					k3--;
					total[l]--;
					for(m=l+1;m<res[0][0];m++)
						index[m]--;
				}
				goto back;
			}
			cnit++;
		}
		if(cnit==total[l])
		{
		       sm_bg();
		}
		back:
	}
	res[0][2]=k3-1;
	getch();
	printf("\n\nThe addition of sparse matrices is :-\n");
	display(res,k3);

}











/*void add(int a[20][20],int b[20][20],int r,int c)
{
	int i,j,k1,k2,k3=1,l,sp1[20][3],sp2[20][3],res[15][3],cnt,cnt2,flag=0;

	k1=spr(a,r,c,sp1);
	k2=spr(b,r,c,sp2);

	clrscr();

	printf("The FIRST sparse matrix is:-\n");
	display(sp1,k1);

	printf("\n\nThe SECOND sparse matrix is:-\n");
	display(sp2,k2);

	if(k1==1||k2==1)
	{
		printf("\n\nTHE ADDITION OF THE MATRIX IS:\n");

		if(k1==1)
			display(sp2,k2);
		else
			display(sp1,k1);

		goto back;
	}


	res[0][0]=r,res[0][1]=c;

	for(i=1;i<k1;i++)
	{
		for(j=1,cnt=0;j<k2;j++,flag=0)
		{
			for(l=1,cnt2=0;l<k3;l++)
			{
				if((sp2[j][0]==res[l][0] && sp2[j][1]==res[l][1])||(sp1[i][0]==res[l][0] && sp1[i][1]==res[l][1]))
					cnt2++;
			}

			if(sp1[i][0]==sp2[j][0])
			{
				if(!cnt2)
				{
					if(sp1[i][1]==sp2[j][1])
					{
						if( (sp1[i][2]+sp2[j][2])!=0)
						{
							res[k3][0]=sp1[i][0];
							res[k3][1]=sp1[i][1];
							res[k3][2]=sp1[i][2]+sp2[j][2];
							k3++;

						}
						flag=1;

					}

					if(sp1[i][1]<sp2[j][1])
					{
						res[k3][0]=sp1[i][0];
						res[k3][1]=sp1[i][1];
						res[k3][2]=sp1[i][2];
						k3++;
						flag=1;
					}

					if(sp1[i][1]>sp2[j][1])
					{
						res[k3][0]=sp2[j][0];
						res[k3][1]=sp2[j][1];
						res[k3][2]=sp2[j][2];
						k3++;
						flag=1;
					}

				 }
			}
			if(sp1[i][0]!=sp2[j][0] || flag!=1)
				cnt++;
			if(cnt==k2-1)
			{
				res[k3][0]=sp1[i][0];
				res[k3][1]=sp1[i][1];
				res[k3][2]=sp1[i][2];
				k3++;
			}
		}
	}
	res[0][2]=k3-1;
	printf("\n\nTHE ADDITION OF THE MATRIX IS:\n");
	display(res,k3);
	back:
} */