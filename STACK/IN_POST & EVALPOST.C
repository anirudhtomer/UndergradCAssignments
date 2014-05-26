#include<sc.h>
#include<math.h>
#define MAX 30

typedef struct expressions
{
	int top;
	char data[MAX];
}stack;

void push(stack *pst,char ele)
{
	pst->top++;
	pst->data[pst->top]=ele;
}
char pop(stack *pst)
{
	char ret;
	ret=pst->data[pst->top];
	pst->top--;
	return ret;
}


int evaluate(int,int,char);
int prior(char ,char);
void in_post();
void evalpost();

void main()
{
	int chmnu;
	char expr[MAX];

	while(1)
	{
		clrscr();
		printf("\t\t\tP O S T FI X\t E X P R E S S I O N S\n\n");
		printf("\n\t1.INFIX TO POSTFIX\n\t2.EVALUATION OF POSTFIX\n\t3.E X I T");
		printf("\n\nENTER YOUR CHOICE:-\t");
		scanf("%d",&chmnu);
		switch(chmnu)
		{
			case 1: in_post();
				break;

			case 2: evalpost();
				break;

			case 3: goto endmnu;

			default: printf("\n\nEnter proper choice");
		}
		getch();
	}
	endmnu:
}

void evalpost()
{
	char pstfx[MAX],*ptr,v1,v2;
	int val,res;
	clrscr();

	printf("ENTER THE POSTFIX EXPRESSION:-\t");
	flushall();
	gets(pstfx);
	ptr=pstfx;

	stack evpost;
	evpost.top=-1;
	printf("\n");
	while(*ptr!='\0')
	{
		if(*ptr>='a'&& *ptr<='z')
		{
			printf("\nEnter value of    %c:-\t",*ptr);
			scanf("%d",&val);
			*ptr=val+48;

		}
		ptr++;
	}

	ptr=pstfx;

	while(*ptr!='\0')
	{
		if(*ptr>=48 && *ptr<=57)
			push(&evpost,*ptr);
		else
		{
			v2=pop(&evpost);
			v1=pop(&evpost);
			res=evaluate((v1-48),(v2-48),*ptr);
			push(&evpost,(res+48));

		}

		ptr++;
	}
	printf("\n\nTHE EVALUATED ANSWER IS     %d",res);
}

int evaluate(int x1,int x2,char op)
{
	int x3;

	switch(op)
	{
		case '-': x3=x1-x2;
			  break;
		case '+': x3=x1+x2;
			  break;
		case '*': x3=x1*x2;
			  break;
		case '/': x3=x1/x2;
			  break;
		case '^': x3=pow(x1,x2);
			  break;

		default : printf("\n\nWrong operator sent");
	}
	return x3;
}






void in_post()
{
	char infx[MAX],pstfx[MAX],*ptr,*str,flag;
	stack coinpst;
	int ret;
	coinpst.top=-1;

	clrscr();

	printf("ENTER THE INFIX EXPRESSION:-\t");
	flushall();
	gets(infx);

	ptr=infx,str=pstfx;


	while(*ptr!='\0')
	{
		flag=0;
		if(*ptr>='a'&&*ptr<='z')
		{
			*str=*ptr;
			str++;
			goto incre;
		}
		else
		{
			if(*ptr=='(')
			{
				push(&coinpst,*ptr);
				flag=1;
				goto incre;
			}

			if(*ptr==')')
			{
				while(coinpst.data[coinpst.top]!='(')
				{
					*str=pop(&coinpst);
					str++;
				}
				pop(&coinpst);
				flag=1;
				goto incre;

			}

			if(!flag)
			{
				ret=prior(coinpst.data[coinpst.top],*ptr);

				switch(ret)
				{
					case 0: push(&coinpst,*ptr);
						goto incre;
					case 1: *str=pop(&coinpst);
						push(&coinpst,*ptr);
						str++;
						goto incre;
				}
			}

		}


		incre:
		ptr++;
	}
	while(coinpst.top!=-1)
	{
		*str=pop(&coinpst);
		if(*str!='(')
			str++;
	}
	*str='\0';
	printf("\n\nTHE POSTFIX EQUIVALENT IS    %s",pstfx);


}


int prior(char prev,char pres)
{
	char set[7]={'-','+',2,'*','/',2,'^'};
	int i,x,y,fl;

	for(i=0,x=0,y=0;i<7;i++)
	{
		if(prev==set[i])
			x=i;
		if(pres==set[i])
			y=i;
	}

	if( y-x>1   ||  x==0)
		return 0;



	return 1;


}


