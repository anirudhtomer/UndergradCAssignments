//ANIRUDH TOMER.....SE COMP -I.....ROLL NO:42028

//program for user defined string functions

#include<stdio.h>
#include<conio.h>
#include<process.h>

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
	int i,j;
	char name[30];

	clrscr();
	back:printf("\Enter The String Name:-\t");
	flushall();
	gets(name);

       do
       {
		getch();
		clrscr();

		printf("STRING ENTERED:\t%s\n\nPRESS \"ENTER\" TO CONTINUE",name);
		printf("\n\n\t\t\t**************MENU**************\n");
		printf("\n\n1.string LENGTH\n2.string REVERSE\n3.string COPY\n");
		printf("4.string CONCATINATION\n5.string UPPERCASE\n");
		printf("6.string LOWERCSE\n7.string COMPARE\n8.string PALINDROME\n");
		printf("9.SUBSTRING\n10.Presence of CHARACTER\n11.BLANK Spaces\n12.Number of WORDS");
		printf("\n13.Enter New String\n14.Exit\n\n");

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

			case 13:goto back;

			case 14:exit(0);

			default: printf("\n\nPlease Enter a Proper Choice");

		}
       }while(1);
}


int lenstr(char *n)
{
	int ln=0;
	char *ptr;
	ptr=n;
	while(*ptr!='\0')
	{
		ln=ln+1;
		ptr++;
	}
	return ln;
}

void revstr(char *n)
{
	int ln;
	char *ptr;
	ln=lenstr(n);
	ptr=(n+(ln-1));
	printf("\n\nThe REVERSE of the string is...");

	while(ptr>=n)
	{
		printf("%c",*(ptr));
		ptr--;
	}
}

void copstr(char *n)
{
	char same[30],*ptr,*str;

	printf("\nEnter a 2nd string:-\t");
	flushall();
	gets(same);
	ptr=n;
	str=same;
	while(*ptr!='\0')
	{
		*str=*ptr;
		ptr++,str++;
	}
	*str='\0';
	printf("\n\nstring COPYED from ..name[20].to.same[20] is:-\t%s",same);
}

void catstr(char *n)
{
	int ln;
	char same[30],*ptr,*str;
	printf("\nEnter a 2nd string:-\t");
	flushall();
	gets(same);

	ln=lenstr(n);
	ptr=(n+ln);
	str=same;
	while(*str!='\0')
	{
		*ptr=*str;
		ptr++;
		str++;
	}
	*ptr='\0';
	printf("\n\nCONCATINATED string is %s",n);
}

void uprstr(char *n)
{
	int j,ln;
	char same[30],*ptr,*str;

	ptr=n,str=same;
	ln=lenstr(n);

	for(j=0;*ptr!='\0';ptr++,str++)
	{
		if(*ptr>=97)
			*str=*ptr-32;
		else
		{
			*str=*ptr;
			j++;
		}

	}
	*str='\0';
	if(j==ln)
		printf("\n\nThe String is already in UPPERCASE");
	else
		printf("\n\nThe string in UPPERCASE is %s",same);
}

void lwrstr(char *n)
{
       int j,ln;
	char same[30],*ptr,*str;

	ptr=n,str=same;
	ln=lenstr(n);

	for(j=0;*ptr!='\0';ptr++,str++)
	{
		if(*ptr>=97)
		{
			*str=*ptr;
			j++;
		}
		else
		{
			*str=*ptr+32;
		}


	}
	*str='\0';
	if(j==ln)
		printf("\n\nThe String is already in LOWERCASE");
	else
		printf("\n\nThe string in LOWERCASE is %s",same);

}

void cmpstr(char *n)
{
	int i,j,k,ln,cnt;
	char same[30],*ptr,*str;

	printf("\nEnter a 2nd string:-\t");
	flushall();
	gets(same);

	ln=lenstr(n);
	j=lenstr(same);
	ptr=n,str=same;
	if(ln!=j)
		printf("\n\nString are not equal in length");

	else
	{
		for(i=0,cnt=0;*ptr!='\0';ptr++,str++,i++)
		{
			k=(*str)-(*ptr);
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
	int k=0,ln;
	char *ptr,*str;
	ln=lenstr(n);
	ptr=n;
	str=(n+(ln-1));
	while(*ptr!='\0')
	{
		if(*ptr==*str)
			k++;
		ptr++,str--;
	}
	if(k==ln)
		printf("\n\nstring is a PALINDROME");
	else
		printf("\n\nstring is not a PALINDROME");
}

void substr(char *n)
{
	int cnt;
	char same[30],*ptr,*str,*k;

	printf("\nEnter a 2nd string:-\t");
	flushall();
	gets(same);
	str=same;

	for(ptr=n,cnt=0;*ptr!='\0';ptr++)
	{
		k=ptr;
		for(str=same;*str!='\0';)
		{
			if(*ptr==*str)
			{
				ptr++,str++;
			}
			else
				break;
		}
		if(*str=='\0')
		{
			cnt++;
			ptr=k;
		}


	}
	if(!cnt)
		printf("\n\nNo such Substring Present");
	else
		printf("\n\nThe string %s is present %d times",same,cnt);
}


void ch_char(char *n)
{
	int i,k;
	char ch,*ptr;

	printf("\n\nEnter The charcter you want to check:-\t");
	flushall();
	scanf("%c",&ch);
	k=0;
	ptr=n;

	while(*ptr!='\0')
	{
	    if(ch==*ptr)
	    {
		k++;
	    }
	    ptr++;
	}
	*ptr='\0';
	printf("\n\nCHARCTER \"%c\" HAS OCCURED :- %d TIMES",ch,k);

}

void blank(char *n)
{
	int i,k;

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
{
	int i,k;

	k=0;
	for(i=0;n[i]!='\0';i++)
	{
		if(  ((n[i]>='a'&&n[i]<='z') || (n[i]>='A'&&n[i]<='Z')) && ((n[i+1]==32) || (n[i+1]=='\0')) )
			k++;
	}
	printf("\n\nNumber of words present are:- %d",k);
}


