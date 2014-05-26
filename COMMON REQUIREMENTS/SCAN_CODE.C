//program to get the scan code of a key

#include<stdio.h>
#include<conio.h>
#include<dos.h>
int getkey();
void main()
{
	int ret;
	clrscr();
	printf("Press any key:-\t");
	ret=getkey();
	printf("\n\nThe scan code of the key is:-\t%d",ret);
	getch();
}

int getkey()
{
	union REGS i,o;
	while(!kbhit())
		i.h.ah=0;

	int86 (22,&i,&o);
	return(o.h.ah);
}
