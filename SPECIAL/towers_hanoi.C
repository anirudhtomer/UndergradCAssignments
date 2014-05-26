#include<sc.h>

void towers(int,char ,char ,char);

void main()
{
	int n;

	clrscr();

	printf("Enter the total number of Pegs:-\t");
	scanf("%d",&n);

	printf("\n\n");
	towers(n,'A','C','B');
	getch();
}

void towers(int n,char fpg,char tpg,char apg)
{
	if(n==1)
	{
		printf("\n1 - %c - %c",fpg,tpg);
		return;
	}

	towers(n-1,fpg,apg,tpg);
	printf("\n%d - %c - %c",n,fpg,tpg);

	towers(n-1,apg,tpg,fpg);
}











