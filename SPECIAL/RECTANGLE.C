//program to print a rectangle on screen without using graphics 

#include<stdio.h>
#include<conio.h>
void main()
{
	int a,b,c,d,e,f;
	clrscr();
	printf("Enter The LENGTH & BREADTH Of Rectangle (l*b):-\t");
	scanf("%d%d",&a,&b);
	printf("\n\n");
	printf("%c",218);
	for(c=1;c<=b+2;c++)   /*here c<=b+2 as the ASCII charcter no. 196 is smaller in size
				as compared to the ASCII charcter no.179 for length.
				Actually it Should have been 'b' only*/


	{
	    printf("%c",196);
	}
	printf("%c",191);
	printf("\n");
	for(d=1;d<=a;d++)
	{
		printf("%c",179);
		for(e=1;e<=b+2;e++)
		{
			printf(" ");
		}
		printf("%c\n",179);
	}
	printf("%c",192);
	for(c=1;c<=b+2;c++)
	{
	    printf("%c",196);
	}
	printf("%c",217);

	getch();
}