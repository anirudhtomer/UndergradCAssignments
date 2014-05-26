//PROGRAM TO PUT CHARACTERS IN A FILE USING CONSTRUCTOR SYNTAX & IN WRITE MODE

#include<iostream.h>
#include<fstream.h>

int main()
{
	ofstream outfile("file.txt",ios::out | ios::binary);

	//	outfile.put('8').put('A').put('o');

	outfile<<8<<'A'<<'o'<<"\nstr";

	//  "outfile" can be changed to any other name

	/*need not to close the file as it is created using constructor
	  & the destructor is called implicitly to close the file*/
	

	return 0;
}