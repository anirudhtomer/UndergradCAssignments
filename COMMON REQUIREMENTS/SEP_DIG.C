/*progarm to seperate digits of a user defined number and storing them
	in an array for further use*/

#include<stdio.h>
#include<conio.h>
int sum(long [],long);
void main()

{

	long a,b,c,num,d,n,dig[20],cnt=0,s;
	clrscr();

	printf("Enter Any Number:-\t");
	scanf("%ld",&num);

	printf("\n\n\nSEPARATED DIGITS ARE:-\n\n");

	for(b=1,n=0,c=num;b>0;b++)
	{

	    a=c%10;
	    c=c/10;

	    printf("  %d",a);
	    cnt++;

	    dig[n]=a;
	    n++;

	    if(c==0)
	    break;

	}

	printf("\n\nThe total number of digits are %d",cnt);
	printf("\n\nTHESE ARE THE ELEMENTS STORED AT DIFFERNT LOCATIONS IN ARRAY\n\n");

	for(int i=n-1;i>=0;i--)
	{
		printf("%d ",dig[i]);
	}
	s=sum(dig,n);
	printf("\n\n\nThe sum of the digits is :-%d",s);
	getch();

}
int sum(long dig[20],long n)
{
	long s;
	if(!n)
		return 0;
	else
		s=s+sum(dig,n-1);

	return (s);
}