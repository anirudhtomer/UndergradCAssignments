//PROGRAM TO SHOW THE USE OF..... data type:-"enumerator"

#include<stdio.h>
#include<conio.h>

enum colour{red,blue,green,yellow,black,orange};

void main()
{
	int i=4;
	clrscr();

	printf("red=%d",red);
	printf("\tblue=%d",blue);
	printf("\tgreen=%d",green);
	printf("black=%d",black);

	if(i==black)
	{
		printf("\tThe value of black is equal to i");
	}
	else
		printf("black is not my favourite colour");

	getch();
}