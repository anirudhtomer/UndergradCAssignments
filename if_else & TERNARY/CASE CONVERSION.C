//program to convert smallcase character into uppercase charcter

#include<stdio.h>
#include<conio.h>
void main()
{
	int as1,as2;
	char ch1,ch2;
	clrscr();
	printf("enter any alphabet either & in upper or lower case & SEE THE MAGIC:-\t");
	scanf("%c",&ch1);
	
	if(ch1>='a'&&ch1<='z')
	{
		ch2=ch1-32;
		printf("\nIt's in lowercase & It's upper case equivalent is:-\t%c \n\nwith the ASCII VALUE=%d",ch2,ch2);

	}
	else
	{
			if(ch1>='A'&&ch1<='Z')
				{
					ch2=ch1+32;
					printf("\nIt's in uppercase & It's lower case equivalent is:-\t%c \n\nwith the ASCII VALUE=%d",ch2,ch2);
				}
			else
					printf("\nyou haven't entered an alphabet");
	}



	getch();
	}