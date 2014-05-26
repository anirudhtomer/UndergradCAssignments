#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

struct elements
{
	int data;
	elements *down;
};

struct stackk
{
	 elements *top;
};

void pushit(stackk **s,elements *el)
{
	el->down = (*s)->top;

	(*s)->top = el;

}

void display(stackk **s)
{

	printf("\n\nTHE ELEMENTS IN STACK ARE:-\n\n");

	printf("%d\n%d\n%d",(*s)->top->data,(*s)->top->down->data,(*s)->top->down->down->data);


}

int main()
{
	elements a,b,c;

	stackk *s1;

	s1 = (stackk*) malloc(sizeof(stackk));

	s1->top = NULL;

	a.data = 1;
	b.data = 2;
	c.data = 3;

	clrscr();


	pushit(&s1,&a);
	pushit(&s1,&b);
	pushit(&s1,&c);

	display(&s1);

	getch();

	return 0;

}