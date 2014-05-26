//PROGRAM TO PUT CHARACTERS IN A FILE WITHOUT CONSTRUCTOR SYNTAX & IN WRITE MODE

#include<iostream.h>
#include<fstream.h>
//commented parts also work similarly in respective areas

int main()
{
	int i = 456;

	ofstream otfile;

	otfile.open("file.txt",ios::out);


   //	otfile.put('8').put('A').put('o');

	otfile<<i;

	/*we need to close the file as it is created without constructor*/

	otfile.close();

	return 0;
}