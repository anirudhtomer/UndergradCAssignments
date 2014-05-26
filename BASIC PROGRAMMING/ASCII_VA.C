/*ASCII VALUE OF ANY CHRACTER*/

#include<stdio.h>
#include<conio.h>
void main()
{
	char ch,ans='y';
	do
	{
		clrscr();
		printf("enter any character:-\t");
		flushall();
		scanf("%c",&ch);
		printf("\nThe ASCII value of the charater '%c' is %d",ch,ch);
		printf("\n\nPress Enter to continue");
		flushall();
		scanf("%c",&ans);

	}while(ans==10);
	getch();
}