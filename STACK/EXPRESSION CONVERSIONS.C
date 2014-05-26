//ANIRUDH TOMER....SE COMP-I....ROLL NO: 42028
//program for EXPRESSION CONVERSION USING "STACK"


/*testing expression:---  INFIX: ((A+B)*C-(D-E))^(F+G)
			 PREFIX: ^-*+ABC-DE+FG
			POSTFIX: AB+C*DE--FG+^     */


/*I TOOK 37 HOURS FOR ME TO COMPLETE THIS PROGRAM.
HOPE THE READER MAY COMPLETE IT IN LESSER TIME.*/


#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<math.h>
#include<string.h>

typedef struct stackop
{
	int top;
	char stk[20];
}stack1;

typedef struct stackopstr
{
	int top2;
	char stk2[20][30];
}stack2;

void pushstr(char [30],stack2*);
char* popstr(stack2*);

void push(char ,stack1 *);
char pop(stack1 *);

int calculate(int ,int ,char );
int prior(char ,char );
int check_pst_in(char ,char );
int check_pre_in(char *);

void evalpost(char *);
void evalpre(char *);

void in_post(char *);
void in_pre(char *);

void post_in(char *);
void pre_in(char *);

void post_pre(char *);
void pre_post(char *);

void main()
{
	int chmnu;
	char expr[20];

	while(1)
	{
		clrscr();
		printf("***********MENU*************\n\n");
		printf("1.INFIX TO POSTFIX\n2.EVALUATION OF POSTFIX\n");
		printf("\n3.INFIX TO PREFIX\n4.EVALUATION OF PREFIX\n");
		printf("\n5.POSTFIX TO INFIX\n6.PREFIX TO INFIX\n");
		printf("\n7.POSTFIX TO PREFIX\n8.PREFIX TO POSTFIX\n\n9.EXIT");

		printf("\n\nENTER YOUR CHOICE:-\t");
		scanf("%d",&chmnu);

		switch(chmnu)
		{
			case 2: printf("\nEnter the POSTFIX expresssion:-\n");
				flushall();
				gets(expr);
				evalpost(expr);
				break;

			case 4: printf("\nEnter the PREFIX expresssion:-\n");
				flushall();
				gets(expr);
				evalpre(expr);
				break;

			case 1: printf("\nEnter the INFIX expresssion:-\n");
				flushall();
				gets(expr);
				in_post(expr);
				break;

			case 3: printf("\nEnter the INFIX expresssion:-\n");
				flushall();
				gets(expr);
				in_pre(expr);
				break;

			case 5: printf("\nEnter the POSTFIX expresssion:-\n");
				flushall();
				gets(expr);
				post_in(expr);
				break;

			case 7: printf("\nEnter the POSTFIX expresssion:-\n");
				flushall();
				gets(expr);
				post_in(expr);
				break;

			case 8: printf("\nEnter the PREFIX expresssion:-\n");
				flushall();
				gets(expr);
				pre_post(expr);
				break;

			case 6: printf("\nEnter the PREFIX expresssion:-\n");
				flushall();
				gets(expr);
				pre_in(expr);
				break;

			case 9: exit(0);
		}
		getch();
	}
}
void push(char num,stack1 *psh)
{
	psh->top++;
	psh->stk[psh->top]=num;
}

char pop(stack1 *spop)
{
	char ret;
	ret=spop->stk[spop->top--];
	return ret;
}

void in_post(char *infx)
{
	int i,j,flag,ret;
	char oper[7]={'(',')','-','+','*','/','^'},pstfx[20],*base,*xp;
	base=pstfx;
	xp=infx;
	stack1 coinpst;

	coinpst.top=-1;

	while(*xp!='\0')
	{
		for(i=0,flag=0;i<7;i++)
		{

			if(*xp==oper[i])
			{
				if(*xp=='(')
				{
					push('(',&coinpst);
					flag=1;
					break;
				}
				if(*xp==')')
				{
					while(coinpst.stk[coinpst.top]!='(')
					{
						*base=pop(&coinpst);
						base++;
					}
					pop(&coinpst);//just to remove the '('
				}
				else
				{
					ret=prior(*xp,coinpst.stk[coinpst.top]);
					switch(ret)
					{
						case 0: push(*xp,&coinpst);
							break;
						case 1: *base=pop(&coinpst);
							base++;
							push(*xp,&coinpst);
							break;
					}
				}

				flag=1;
				break;
			}
		}
		if(!flag)
		{
			*base=*xp;
			base++;
		}
		xp++;
	}
	while(coinpst.top!=-1 )
	{
		*base=pop(&coinpst);
		if(*base!='(')
			base++;
	}
	*base='\0';
	printf("\n\nTHE POSTFIX STRING IS:-   %s",pstfx);

}
int prior(char second,char first)
{
	int i,x,y,fl;
	char arr[7]={'+','-',2,'*','/',2,'^'};
	//0-just push
	//1-pop & push


	for(i=0,fl=0;i<7;i++)
	{
		if(second==arr[i])
			x=i;

		if(first==arr[i])
		{
			y=i;
			fl=1;
		}
	}

	if(fl!=1 || (x-y)>1)
		return 0;

	return 1;
}
void evalpost(char *pstfx)
{
	int i,j,res,flag,val;
	char opnd1,opnd2,str[20],*vistr;
	char opnd[10]={48,49,50,51,52,53,54,55,56,57};

	vistr=str;

	printf("\n");

	while(*pstfx!='\0')
	{
		if( (*pstfx>='A' && *pstfx<'Z') ||(*pstfx>='a'&& *pstfx<='z') )
		{
			printf("\nENTER VALUE OF VARIABLE \"%c\":-\t",*pstfx);
			scanf("%d",&val);
			*vistr=val+48;
		}
		else
			*vistr=*pstfx;

		vistr++,pstfx++;
	}
	*vistr='\0';

	stack1 evpost;
	evpost.top=-1;

	vistr=str;
	while(*vistr!='\0')
	{
		for(j=0,flag=0;j<10;j++)
		{
			if(*vistr==opnd[j])
			{
				push(*vistr,&evpost);
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			opnd1=pop(&evpost);
			opnd2=pop(&evpost);
			res=calculate(opnd2-48,opnd1-48,*vistr);
			push((res+48),&evpost);
		}
		vistr++;

	}
	printf("\n\nTHE EVALUATED ANSWER OF POSTFIX STRING IS %d",res);
}
int check_pst_in(char pre,char next)
{
	char opt[5]={'+','-','*','/','^',};
	int i,f1=0,f2=0;

	for(i=0;i<5;i++)
	{
		if(pre==opt[i])
			f1=1;

		if(next==opt[i])
			f2=1;

	}
	//1-put braces
	//0-continue

	if( (f1==1&&(f2==0||f2==1||next=='\0')))
		return 1;

	return 0;
}
int check_pre_in(char *pre)
{
	int i;
	char opt[5][2]={"+\0","-\0","*\0","/\0","^\0"};

	for(i=0;i<5;i++)
	{
		if(!(strcmp(pre,opt[i])))
			return 0;
	}
	return 1;
	//0-do push
	//1-pop and add together & push
}
void post_pre(char *pstfx)
{
	int i,ret;
	char str1[30],str2[30],temp[30],ch3[2];
	ch3[1]='\0';

	stack2 copstpre2;
	copstpre2.top2=-1;

	for(i=0;pstfx[i]!='\0';i++)
	{
		ch3[0]=pstfx[i];
		strcpy(str1,NULL);
		strcpy(str2,NULL);
		strcpy(temp,NULL);

		if(pstfx[i]>='a'&&pstfx[i]<='z')
			pushstr(ch3,&copstpre2);

		else
		{
			strcpy(str1,popstr(&copstpre2));
			strcpy(str2,popstr(&copstpre2));
			strcpy(temp,ch3);
			strcat(temp,str2);
			strcat(temp,str1);
			strcat(temp,NULL);
			pushstr(temp,&copstpre2);
		}
	}
	printf("\n\nTHE PREFIX EXPRESSION IS \n%s",temp);
}
void pre_post(char *prefx)
{
	int i,ret;
	char str1[30],str2[30],temp[30],ch3[2];
	ch3[1]='\0';

	stack2 coprepst2;
	coprepst2.top2=-1;

	strrev(prefx);

	for(i=0;prefx[i]!='\0';i++)
	{
		ch3[0]=prefx[i];
		strcpy(str1,NULL);
		strcpy(str2,NULL);
		strcpy(temp,NULL);

		if(prefx[i]>='a'&&prefx[i]<='z')
			pushstr(ch3,&coprepst2);

		else
		{
			strcpy(str1,popstr(&coprepst2));
			strcpy(str2,popstr(&coprepst2));
			strcpy(temp,ch3);
			strcat(temp,str2);
			strcat(temp,str1);
			strcat(temp,NULL);
			pushstr(temp,&coprepst2);
		}
	}
	strrev(temp);
	printf("\n\nTHE POSTFIX EXPRESSION IS \n%s",temp);
}

void pre_in(char *prefx)
{
	int i,ret;
	char str1[30],str2[30],temp[30],ch3[2];
	ch3[1]='\0';

	stack2 coprein2;
	coprein2.top2=-1;

	for(i=0;prefx[i]!='\0';i++)
	{
		ch3[0]=prefx[i];
		strcpy(str1,NULL);
		strcpy(str2,NULL);
		strcpy(temp,NULL);

		if(prefx[i]>='a'&&prefx[i]<='z')
		{
			pushstr(ch3,&coprein2);
			while(check_pre_in(coprein2.stk2[coprein2.top2 -1])==1 && coprein2.top2!=0)
			{

				strcpy(str1,popstr(&coprein2));
				strcpy(str2,popstr(&coprein2));
				strcpy(ch3,popstr(&coprein2));

				strcpy(temp,str2);
				strcat(temp,ch3);
				strcat(temp,str1);

				pushstr(temp,&coprein2);
				strcpy(temp,NULL);
				if(prefx[i+1]=='\0')
				{
					strcpy(temp,"(");
					strcat(temp,NULL);
					strcat(temp,popstr(&coprein2));
					strcat(temp,NULL);
					strcat(temp,")\0");
					pushstr(temp,&coprein2);
				}
			}
		}
		else
		{
			if(check_pre_in(coprein2.stk2[coprein2.top2])==1 && coprein2.top2!=-1)
			{
				strcpy(str1,popstr(&coprein2));
				strcpy(temp,"(");
				strcat(temp,str1);
				strcat(temp,")");
				strcat(temp,NULL);
				pushstr(temp,&coprein2);
			}
			pushstr(ch3,&coprein2);
		}

	}
	strcpy(temp,popstr(&coprein2));
	printf("\n\nTHE INFIX EXPRESSION IS \n%s",temp);

}
void post_in(char *pstfx)
{
	int i,ret;
	char str1[20],str2[20],temp[30],ch3[2];

	stack2 copstin2;
	copstin2.top2=-1;

	for(i=0;pstfx[i]!='\0';i++)
	{
		ret=check_pst_in(pstfx[i-1],pstfx[i+1]);
		if(pstfx[i]>='a' && pstfx[i]<='z')
		{
			switch(ret)
			{
				case 0: ch3[0]=pstfx[i],ch3[1]='\0';
					pushstr(ch3,&copstin2);
					break;

				case 1: ch3[0]=pstfx[i],ch3[1]='\0';
					strcpy(temp,"(");
					strcat(temp,popstr(&copstin2));
					strcat(temp,")\0");
					pushstr(temp,&copstin2);
					pushstr(ch3,&copstin2);
					break;
			}
		}
		else
		{

			ch3[0]=pstfx[i],ch3[1]='\0';

			strcpy(temp,NULL);
			strcpy(str1,NULL);
			strcpy(str2,NULL);
			if(ret==1)
				strcpy(temp,"(");

			strcat(str1,temp);
			strcat(str1,popstr(&copstin2));

			if(ret==1)
				strcat(str1,")");

			strcpy(str2,popstr(&copstin2));

			strcpy(temp,str2);
			strcat(temp,ch3);
			strcat(temp,str1);
			strcat(temp,NULL);
			pushstr(temp,&copstin2);
		}

	}

	printf("\n\nTHE INFIX EXPRESSION IS \n%s",temp);


}
void pushstr(char str[30],stack2 *psh2)
{
	psh2->top2++;
	strcpy(psh2->stk2[psh2->top2],NULL);
	strcat(psh2->stk2[psh2->top2],str);
	strcat(psh2->stk2[psh2->top2],NULL);
}

char* popstr(stack2 *spop2)
{
	char ret[40];
	strcpy(ret,NULL);
	strcat(ret,spop2->stk2[spop2->top2--]);
	strcat(ret,NULL);
	return ret;
}

void in_pre(char *infx)
{
	int i,j,flag,ret,len;
	char oper[7]={'(',')','-','+','*','/','^'},prefx[30],*xp;
	char chr3[2],str1[20],str2[20],temp[20];

	xp=infx;

	stack1 coinpre;
	stack2 coinpre2;

	coinpre2.top2=-1;
	coinpre.top=-1;

	while(*xp!='\0')
	{
		for(i=0,flag=0;i<7;i++)
		{

			if(*xp==oper[i])
			{
				if(*xp=='(')
				{
					push('(',&coinpre);
					flag=1;
					break;
				}
				if(*xp==')')
				{
					while(coinpre.stk[coinpre.top]!='(')
					{
						strcpy(str1,popstr(&coinpre2));
						strcpy(str2,popstr(&coinpre2));
						chr3[0]=pop(&coinpre);

						strcpy(temp,chr3);
						strcat(temp,str2);
						strcat(temp,str1);

						pushstr(temp,&coinpre2);
					}
					pop(&coinpre);//just to remove the '('
				}
				else
				{
					ret=prior(*xp,coinpre.stk[coinpre.top]);
					switch(ret)
					{
						case 0: push(*xp,&coinpre);
							break;
						case 1: strcpy(str1,popstr(&coinpre2));
							strcpy(str2,popstr(&coinpre2));
							chr3[0]=pop(&coinpre);

							strcpy(temp,chr3);
							strcat(temp,str2);
							strcat(temp,str1);

							pushstr(temp,&coinpre2);
							push(*xp,&coinpre);
							break;
					}
				}

				flag=1;
				break;
			}
		}
		if(!flag)
		{
			chr3[0]=*xp;
			chr3[1]='\0';
			pushstr(chr3,&coinpre2);
		}
		xp++;
	}
	while(coinpre.top!=-1 )
	{
		strcpy(str1,popstr(&coinpre2));
		strcpy(str2,popstr(&coinpre2));
		chr3[0]=pop(&coinpre);

		strcpy(temp,chr3);
		strcat(temp,str2);
		strcat(temp,str1);

		pushstr(temp,&coinpre2);
	}
	strcat(coinpre2.stk2[coinpre2.top2],'\0');
	strcpy(prefx,popstr(&coinpre2));
	printf("\n\nTHE PREFIX STRING IS:-   %s",prefx);


}

void evalpre(char *prefx)
{
	int i,j,res,flag,val;
	char opnd1,opnd2,str[20],*vistr;
	char opnd[10]={48,49,50,51,52,53,54,55,56,57};

	vistr=str;
	printf("\n");
	while(*prefx!='\0')
	{
		if( (*prefx>='A' && *prefx<'Z') ||(*prefx>='a'&& *prefx<='z') )
		{
			printf("\nENTER VALUE OF VARIABLE \"%c\":-\t",*prefx);
			scanf("%d",&val);
			*vistr=val+48;
		}
		else
			*vistr=*prefx;
		vistr++;
		prefx++;
	}
	*vistr='\0';

	stack1 evpre;
	evpre.top=-1;

	strrev(str);
	vistr=str;

	while(*vistr!='\0')
	{
		for(j=0,flag=0;j<10;j++)
		{
			if(*vistr==opnd[j])
			{
				push(*vistr,&evpre);
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			opnd1=pop(&evpre);
			opnd2=pop(&evpre);
			res=calculate(opnd1-48,opnd2-48,*vistr);
			push((res+48),&evpre);
		}
		vistr++;

	}
	printf("\n\nTHE EVALUATED ANSWER OF PREFIX STRING IS %d",res);
}

int calculate(int a,int b,char optr)
{
	int res;
	switch(optr)
	{
		case '+':  res=a+b;
			   break;
		case '-':  res=a-b;
			   break;
		case '*':  res=a*b;
			   break;
		case '/':  res=a/b;
			   break;
		case '^':  res=pow(a,b);
			   break;
		default: printf("\n\nWrong operator was sent");
	 }
	 return res;
}


