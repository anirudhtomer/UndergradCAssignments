//PROGRAM TO TEST SPACE COMPLEXITY OF TEXT & BINARY FILE

/*in text mode if u press "ENTER" the "carriage return & line feed"
characters are entered.....IN binary mode only "line feed"
character is entered     */


#include<iostream.h>
#include<fstream.h>
#include<conio.h>

int main()
{
	int pointer;
	char ch[30];

	ofstream fout;

	clrscr();

	//OPENING IN TEXT MODE


	fout.open("filetext.txt",ios::out);

	cout<<"\nENTER ANYTHING:-\t";
	cin.getline(ch,30,'$');

	fout<<ch;

	pointer = fout.tellp();

	cout<<"\n\nTHE OFFSET IN CASE OF TEXT MODE IS:-\t"<<pointer<<" bytes";
	fout.close();


	//OPENING IN BINARY FILE

	cout<<"\n\nENTER ANYTHING:-\t";
	cin.getline(ch,30,'$');

	fout.open("filebin.txt",ios::binary);

	fout<<ch;

	pointer = fout.tellp();

	cout<<"\n\nTHE OFFSET IN CASE OF BINARY MODE IS:-\t"<<pointer<<" bytes";
	fout.close();

	getch();

	return 0;

}
