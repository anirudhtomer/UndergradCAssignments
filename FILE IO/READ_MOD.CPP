//PROGRAM TO READ CHARACTERS FROM A FILE USING CONSTRUCTOR SYNTAX

#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>

int main()
{
	char ch[30];

	ifstream ipfile;

	ipfile.open("file.txt",ios::in);

	clrscr();

	if(ipfile==NULL)
	{
		cout<<"NO FILE PRESENT";
		exit(1);
	}

	while(!ipfile.eof())
	{
		ipfile.getline(ch,30,EOF);
		cout<<ch;
	}
	getch();

	return 0;
}