//program for user defined string functions

#include<stdio.h>
#include<conio.h>
#include<process.h>

int i,j,k,ln;
char name[30],same[30];

void swch();
void menu();

void n_str();
int  lenstr(char *);
void revstr(char *);
void copstr(char *);
void catstr(char *);
void uprstr(char *);
void lwrstr(char *);
void cmpstr(char *);
void palstr(char *);
void ch_char(char *);
void blank(char *);
void words(char *);
void substr(char *);

void main()
{
	clrscr();
	n_str();
	getch();

}

void menu()
{
	printf("\n\n\t\t\t**************MENU**************\n");
	printf("\n\n1.string LENGTH\n2.string REVERSE\n3.string COPY\n");
	printf("4.string CONCATINATION\n5.string UPPERCASE\n");
	printf("6.string LOWERCSE\n7.string COMPARE\n8.string PALINDROME\n");
	printf("9.SUBSTRING\n10.Presence of CHARACTER\n11.BLANK Spaces\n12.Number of WORDS");
	printf("\n13.Enter New String\n14.Exit\n\n");
}

void swch()
{
       do
       {
		getch();
		clrscr();
		printf("STRING ENTERED:\t%s\n\nPRESS \"ENTER\" TO CONTINUE",name);
		menu();
		printf("\n\nEnter Your Choice:-\t");
		scanf("%d",&i);

		switch(i)
		{
			case 1: j=lenstr(name);
				printf("\n\nThe LENGTH of the string = %d",j);
				break;

			case 2:	revstr(name);
				break;

			case 3: copstr(name);
				break;

			case 4:	catstr(name);
				break;

			case 5:	uprstr(name);
				break;

			case 6: lwrstr(name);
				break;

			case 7:	cmpstr(name);
				break;

			case 8: palstr(name);
				break;

			case 9:	substr(name);
				break;

			case 10:ch_char(name);
				break;

			case 11:blank(name);
				break;

			case 12:words(name);
				break;

			case 13:n_str();
				break;

			case 14:exit(0);

			default: printf("\n\nPlease Enter a Proper Choice");

		}
       }while(1);
}


int lenstr(char *n)
{
	for(i=0;n[i]!='\0';i++)
		ln=i+1;

	return ln;
}

void revstr(char *n)
{
	ln=lenstr(n);

	printf("\n\nThe REVERSE of the string is...");

	for(i=ln;i>=0;i--)
		printf("%c",n[i]);
}

void copstr(char *n)
{
	printf("\nEnter a 2nd string:-\t");
	flushall();
	gets(same);

	for(i=0;n[i]!='\0';i++)
	{
		same[i]=n[i];
	}
	same[i]='\0';
	printf("\n\nstring COPYED from ..name[20].to.same[20] is:-\t%s",same);
}

void catstr(char *n)
{
	printf("\nEnter a 2nd string:-\t");
	flushall();
	gets(same);

	ln=lenstr(n);

	for(i=ln,j=0;same[j]!='\0';j++,i++)
	{
		n[i]=same[j];
	}
	n[i]='\0';
	printf("\n\nCONCATINATED string is %s",n);
}

void uprstr(char *n)
{
	for(i=0,j=0;n[i]!='\0';i++)
	{
		same[i]=n[i]-32;

		if(same[i]<65)
			j++;

	}
	same[i]='\0';
	if(j==i)
		printf("\n\nThe String is already in UPPERCASE");
	else
		printf("\n\nThe string in UPPERCASE is %s",same);
}

void lwrstr(char *n)
{
	for(i=0,j=0;n[i]!='\0';i++)
	{
		same[i]=n[i]+32;

		if(same[i]>123)
			j++;
	}
	same[i]='\0';
	if(j!=i)
		printf("\n\nThe string in LOWERCASE is %s",same);

	else
		printf("\n\nThe String is already in LOWERCASE");
}

void cmpstr(char *n)
{
	int cnt;
	printf("\nEnter a 2nd string:-\t");
	flushall();
	gets(same);

	ln=lenstr(n);
	j=lenstr(same);

	if(ln!=j)
		printf("\n\nString are not equal in length");

	else
	{
		for(i=0,j=0,cnt=0;n[i]!='\0';i++)
		{
			k=same[i]-n[i];
			if(!k)
			{
				cnt++;
				continue;
			}
			printf("\nThe ASCII value difference at position");
			printf("%d =   %d",i+1,k);
		}
		if(cnt==i)
			printf("\nTHE STRINGS ARE EQUAL");
	}
}

void palstr(char *n)
{
	ln=lenstr(n);

	for(i=0,j=ln-1,k=0;n[i]!='\0';j--,i++)
	{
		if(n[i]==n[j])
			k++;
	}
	if(k==i)
		printf("\n\nstring is a PALINDROME");
	else
		printf("\n\nstring is not a PALINDROME");
}

void substr(char *n)
{
	char same[10];

	printf("\nEnter a 2nd string:-\t");
	flushall();
	gets(same);

	for(i=0,ln=0;n[i]!='\0';i++)
	{
		k=i;
		for(j=0;same[j]!='\0';j++)
		{
			if(n[i]==same[j])
			{
				i++;
			}
			else
				break;
		}
		if(same[j]=='\0')
		{
			printf("\n\nSubstring Present");
			break;
		}
		else
			ln++;
		i=k;
	}
	if(ln==i)
		printf("\n\nNo such Substring Present");
}


void ch_char(char *n)
{
	char ch;
	printf("\n\nEnter The charcter you want to check:-\t");
	flushall();
	scanf("%c",&ch);
	k=0;
	for(i=0;name[i]!='\0';i++)
	{
	    if(ch==name[i])
	    {
		k++;
	    }
	}
	n[i]='\0';
	printf("\n\nCHARCTER \"%c\" HAS OCCURED :- %d TIMES",ch,k);

}

void blank(char *n)
{
	flushall();
	k=0;
	for(i=0;n[i]!='\0';i++)
	{
		if(n[i]==32)
			k++;
	}
	printf("\n\nNumber of BLANK SPACES are %d",k);
}

void words(char *n)
{       k=0;
	for(i=0;n[i]!='\0';i++)
	{
		if(  ((n[i]>='a'&&n[i]<='z') || (n[i]>='A'&&n[i]<='Z')) && ((n[i+1]==32) || (n[i+1]=='\0')) )
			k++;
	}
	printf("\n\nNumber of words present are:- %d",k);
}

void n_str()
{
	clrscr();

	printf("\Enter The String Name:-\t");
	flushall();
	gets(name);

	swch();
}

