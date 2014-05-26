//program for fibonacci series upto--n
#include<stdio.h>
#include<conio.h>

#define NUM 100

int main()
{
	int i,j,k;

	clrscr();

	for(i=1,j=1;i<NUM;)
	{
		printf("%d , ",i);
		k = j;
		j = i;
		i = i+k;
	}

	getch();
	return 0;
}
