/*program to print two words.....one of which travels from
  left to right..&...another from right to left...consecutively*/

#include<stdio.h>
#include<conio.h>
#include<dos.h>

int i,j,k,m,n;
float dl,dl2;
char f[15],s[15],l[15];

void game(char *,char *,char *,float );

void main()
{

	clrscr();
	printf("\nEnter The First Word:-\t");
	flushall();
	gets(f);

	printf("\nEnter The Second Word:-\t");
	flushall();
	gets(s);

	printf("\nEnter The Last Word:-\t");
	flushall();
	gets(l);
	printf("\n\nEnter How Much Seconds Delay You Want(greater than 0.009 sec):-\t");
	scanf("%f",&dl);
	dl2=dl*1000.0;

	clrscr();
	game(f,s,l,dl2);

	getch();

}

void game(char *f,char *s,char *l,float dl2)
{
	for(i=0;i<13;i++)
	{
	     j=i*3;
	     for(k=0;k<j;k++)
	     {
		printf(" ");
	     }
	     printf("%s",f);

	     m=71-i*6;
	     for(n=m;n>=0;n--)
	     {
		printf(" ");
	     }
	     printf("%s",s);

	     delay(dl2);
	     clrscr();
	}
	printf("\n\n\n\n\n\n\n\n\n\t\t\t***********%s*************",l);
}