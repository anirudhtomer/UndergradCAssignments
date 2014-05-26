//TO USE IT AS COMMAND LINE COPY ITS EXE FILE IN A FOLDER....PASS TWO ARGUMENTS (both are files)

//ANIRUDH TOMER...SE COMP-I...SE 42028
//PROGRAM FOR FILE HANDLING

#include<iostream.h>
#include<fstream.h>

const int MAX = 500;

int main(int numarg,char *argv[])
{
	char ch,prvch;
	char paragraph[MAX];

	int numvowel=0,numchar=0,numblank=0,numwords=0,numlines=0;

	ofstream result(argv[1],ios::out); //opening result file in write mode

	if(numarg>2)
	{
		cout<<"WRONG NUMBER OF INPUTS PASSED";
		return 0;
	}

	//OPENING "SOURCE FILE" IN WRITE MODE

	fstream source;

	source.open("source.txt",ios::out);

	cout<<"WRITE ANYTHING (scrap) (press $ to stop):-\n\n";
	cin.getline(paragraph,MAX,'$');

	source<<paragraph;   //write to source file
	source.close();

	//opening souce file in read mode
	source.open("source.txt",ios::in);

	prvch = ' ';

	while(!source.eof())
	{
		source.get(ch);

		numchar++;

		if(ch=='A'||ch=='a'||ch=='E'||ch=='e'||ch=='I'||ch=='i'||ch=='O'||ch=='o'||ch=='U'||ch=='u')
			numvowel++;

		if(ch=='\n')
			numlines++;

		if(ch==' ')
			numblank++;

		if((ch==' ' ||ch=='\n'|| ch=='.' ||ch==EOF) && prvch!=' ' && prvch!='\n' && prvch!='.')
			numwords++;

		prvch = ch;
	}

	cout<<"\t\t";
	cout<<numchar<<"\t"<<numvowel<<"\t"<<numlines<<"\t"<<numblank<<"\t"<<numwords;

	result<<"THE NUMBER OF CHARACTERS ARE:-\t"<<numchar<<"\n\n";
	result<<"THE NUMBER OF VOWELS ARE:-\t"<<numvowel<<"\n\n";
	result<<"THE NUMBER OF LINES ARE:-\t"<<numlines<<"\n\n";
	result<<"THE NUMBER OF SPACES ARE:-\t"<<numblank<<"\n\n";
	result<<"THE NUMBER OF WORDS ARE:-\t"<<numwords<<"\n\n";

	return 0;
}
