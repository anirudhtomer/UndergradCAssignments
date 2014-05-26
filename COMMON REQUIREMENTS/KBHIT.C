#include <conio.h>

int main(void)
{
   clrscr();

   if(kbhit()!=0)
	cprintf("\r\nA key was pressed...\r\n");

   return 0;
}

