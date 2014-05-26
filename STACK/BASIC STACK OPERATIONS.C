//Implementing BASIC operations on stack

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<process.h>
#define SIZE 50

typedef struct operation
{
	int a[SIZE],top;
}stck;

void push(stck *);
void display(stck *);
int pop(stck *);
void clear(stck *);

void main()
{
	   int ch,rp;
	   stck s1;
	   clrscr();
	   s1.top=-1;
	   do
	  {
		printf("\n\nPress Enter to continue");
		getch();
		clrscr();
		printf("***********MENU**********\n\n1.PUSH in stack\n2.POP stack\n3.DISPLAY stack\n4.CLEAR stack\n5.EXIT");
		printf("\nEnter Choice:-\t");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1: push(&s1);
				break;
			case 2: rp=pop(&s1);
				if(rp!=0)
					printf("\n\nThe Popped up value is %d",rp);
				break;
			case 3: display(&s1);
				break;
			case 4: clear(&s1);
				break;
			case 5: exit(0);
		 }

	  }while(1);
}
void clear(stck *ms)
{       int i;
	for(i=ms->top;i>-1;i--)
	{
		ms->a[i]=NULL;
	}
	ms->top=-1;
}
void push(stck *ms)
{
	int i;
	if(ms->top==SIZE-1)
	{
		printf("\n\n\nOVERFLOW OCCURED");
	}

	else
	{
		printf("\n\nEnter element to be pushed:-\t");
		scanf("%d",&ms->a[(ms->top)+1]);
		(ms->top)++;
	}
}

int pop(stck *ms)
{
	int i,x;
	if(ms->top==-1)
	{
		printf("\n\n\nUNDERFLOW OCCURED");
		return 0;
	}

	else
	{
		x=ms->a[(ms->top)];
		ms->a[(ms->top)]=NULL;
		(ms->top)--;
	}
	return x;
}

void display(stck *ms)
{
	int i;
	if(ms->top==-1)
		printf("\n\nEmpty stack");
	else
	{
		printf("\n\nELEMENTS ARE:-\t");
		for(i=0;i<ms->top+1;i++)
		{
			printf("%d   ",ms->a[i]);
		}
	}
}

