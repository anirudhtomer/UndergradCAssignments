#include <time.h>
#include <stdio.h>
#include<conio.h>

int main(void)
{
   clrscr();
   clock_t start, end;
   start = clock();


   end = clock();
   printf("The time was: %f\n", (end - start) / CLK_TCK);

   return 0;
}
