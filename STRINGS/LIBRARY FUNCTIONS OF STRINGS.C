//program to perform operations on strings using library functions

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
void main()
{
	int ch,ln;
	char name[20],same[20];
	clrscr();
	printf("enter the string name[20] :-\t");
	gets(name);

	printf("\n\n**************MENU**************\n");
	printf("\n1.string LENGTH\n2.string COPY\n3.string REVERSE\n");
	printf("4.string CONCATINATION\n5.string UPPERCASE\n");
	printf("6.string LOWERCSE\n7.string COMPARE\n8.string PALINDROME\n");
	printf("9.SUBSTRING\n10.Exit");

	printf("\n\nEnter Your choice:-\t");
	scanf("%d",&ch);

	switch(ch)
	{
		case 1:	ln=strlen(name);
			printf("\nThe string length is... %d",ln);
			break;

		case 2: printf("\nenter the string same[20]:-\t");
			fflush(stdin);
			gets(same);
			strcpy(same,name);
			printf("The string in same[20] is... %s",same);
			break;

		case 3:	strrev(name);
			printf("\nThe reversed string is... %s",name);
			break;

		case 4: printf("\nenter the string same[20]:-\t");
			fflush(stdin);
			gets(same);

			strcat(name,same);
			printf("\n The concatinated string is %s",name);
			break;

		case 5: strupr(name);
			printf("The string in uppercase is... %s",name);
			break;

		case 6: strlwr(name);
			printf("The string in lowercase is... %s",name);
			break;

		case 7:	printf("\nenter the string same[20]:-\t");
			fflush(stdin);
			gets(same);

			ln=strcmp(name,same);
			printf("\n The ASCII difference is %d",ln);
			break;

		case 8: strcpy(same,name);
			strrev(name);
			if(!strcmp(name,same))
				printf("\nString is a PALINDROME");
			else
				printf("\nString Not a Palindrome");
			break;

		case 9:	printf("\nenter the string same[20]:-\t");
			fflush(stdin);
			gets(same);
			char *sub;
			sub=strstr(name,same);
			printf("\nThe Substring in name[20] is %d",sub);
			break;

		case 10: exit(0);

	}

	getch();
}

