//PROGRAM TO SHOW HOW TO PRINT RANDOM NUMBERS

#include <stdlib.h> //for the function randomize
#include <stdio.h>
#include <time.h> /it isn't necessary, but may be of use at some point of time,about which I might not be knowing
#include<conio.h>

int main(void)
{
   int i;
   clrscr();
   randomize();

   /*if you do not use the "randomize function then
   on the first run some random numbers will be printed
   but they won't change on the next run time.
   SO IT MAKE SURE THAT SAME NUMBERS ARE NOT
   REPEATED (same as the last run time)
   ON EVERY RUN OF THE PROGRAM & USER MAY NOT GET confused */
   //anirudh tomer

   printf("Ten random numbers from 0 to 99\n\n");

   for(i=0; i<10; i++)
       printf("%d\n", rand() % 100);


   printf("\n\nSix random numbers from 0 to 999\n\n");

   for(i=0; i<6; i++)
       printf("%d\n", rand() % 1000);

   getch();
   return 0;

}

