//ASCII CHARACTERS

#include<stdio.h>
#include<conio.h>

void main()
{
	int a,more=1;
	char cont='y';
	clrscr();
	for(;cont=='y'||cont=='Y';)
	{
		for(a=1;a<=255&& more==1;a++)
		{
			printf("\n\n\nASCII VALUE:- %d    ----   CHARACTER:- %c",a,a);
			if(a%10==0)
			 {
				printf("\n\nMORE(1):-\t");
				scanf("%d",&more);

				getch();
				clrscr();
			 }
		}
		if(more!=1)
		   break;

		printf("\n\nDO YOU WISH TO SEE AGAIN:-\t");
		flushall();
		scanf("%c",&cont);

	}
}