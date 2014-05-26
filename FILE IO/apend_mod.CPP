//PROGRAM TO OPEN A FILE IN APPEND MODE  (add at end)

#include<iostream.h>
#include<fstream.h>
#include<conio.h>

int main()
{
	char ch[30];

	ofstream fout("file.txt",ios::app);

	clrscr();

	cout<<"ENTER ANYTHING:-\t";
	cin.getline(ch,30,'$');

	fout<<ch;

	return 0;

}
