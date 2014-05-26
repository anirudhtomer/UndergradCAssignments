//program for matchstick game

#include<stdio.h>
#include<conio.h>
#include<string.h>

void main()

{
	int a=0,b,c=0,d;
	char name[20],e;
	clrscr();
	printf("\n\n\t\t\t**********MATHSTICKS GAME**********\n\n");
	printf("\n\n\nPLEASE ENTER YOUR NAME:-\t");
	flushall();
	scanf("%s",&name);
	printf("\n\n\nHI \"%s\" TODAY WE WILL PLAY THE GAME OF MATCHSTICKS \n\nI PROMISE YOU THAT YOU WILL SURELY LOSE THIS GAME\n",name);
	printf("\n\n\nTHE RULES:-\n\n1.THERE ARE 43 MATCHSTICKS\n\n2. YOU WILL BE THE FIRST ONE TO PICK UP STICKS\n\n3. YOU CAN PICK 1,2,3..6 NUMBER OF STICKS & SAME APPLIES TO COMPUTER ALSO\n\n4. THE ONE WHO PICKS UP LAST STICK LOSES THE GAME\n\n5. YOU HAVE TO PROMISE ME THAT IF YOU LOSE YOU HAVE TO GIVE ME 100 Rs.");
	printf("\n\n\nARE YOU READY TO PLAY & WILL YOU KEEP YOUR PROMISE REGARDING MONEY  :- \t");
	fflush(stdin);
	scanf("%c",&e);
	if(e=='y'||e=='Y')
	{
	 clrscr();
	 printf("REMEMBER NOT TO PICK UP MORE THAN 6 MATCHSTICKS \n\nOK HERE WE START\n\n\n\n");
	for(b=1,d=43;b<=6;b++)
	{
		printf("\n\n\nPICK UP STICKS:-\t");
		scanf("%d",&a);
		c=7-a;
		printf("\n\nanalyzing..... I WILL PICK UP %d STICKS",c);
		d=d-7;
		printf("\n\nNUMBER OF STICKS LEFT ARE =  %d",d);
		printf("\n");
	}
	}
	printf("\n\nTHERE IS ONLY \"ONE STICK\" LEFT AND THAT YOU HAVE TO PICK UP\n\nI KEPT MY PROMISE & NOW AS PER RULES YOU KEEP YOURS.\n");

	getch();
}