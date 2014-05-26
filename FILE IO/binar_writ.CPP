//PROGRAM TO OPEN A FILE IN BINARY MODE

#include<iostream.h>
#include<fstream.h>
#include<conio.h>

int main()
{
	char ch[30];

	ofstream fout("file.txt",ios::binary);

	clrscr();

	cout<<"ENTER ANYTHING:-\t";
	cin.getline(ch,30,'$');

	fout<<ch;

	return 0;

}
