#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class MACRO
{
	FILE *fin,*fout;

	char source[30][10][10];
	int totallines;
	int sourcestart;

	int mdtptr,mntptr,alaptr;

	char mdt[30][6][20];

	struct MNT
	{
		int mdtindex;
		int alaindex;
		char macroname[10];
	}mnt[5];

	struct ALA
	{
		char alaindex[3];
		char actarg[10];
		char dummyarg[10];
	}ala[10];

	public:

	MACRO()
	{
		mntptr = 0;
		mdtptr = 0;
		alaptr = 0;
	}

	void readSource();
	void pass1();
	void displayPass1();
	void pass2();

};

int main()
{
	MACRO m1;

	clrscr();
	m1.readSource();
	m1.pass1();
	m1.displayPass1();
	m1.pass2();

	getch();
	return 0;
}

//pass2
void MACRO::pass2()
{
	int i,j,k,l;
	int pass;
	int mntp;

	fout = fopen("expand.txt","w");

	for(i=sourcestart;i<totallines;i++)
	{
		pass = 0;
		for(j=0;j<mntptr;j++)
		{
			if(!strcmpi(source[i][0],mnt[j].macroname))
			{
				pass = 1;
				mntp = j;
				break;
			}
		}

		if(pass == 1) //macro detected
		{
			//copy actual to ALA
			for(j=1;strcmpi(source[i][j],"NULL");j++)
				strcpy(ala[mnt[mntp].alaindex + j -1].actarg,source[i][j]);

			//read mdt & reaplace #kinda with actarg
			for(j=mnt[mntp].mdtindex+1;strcmpi(mdt[j][0],"MEND");j++)
			{
				for(k=0;strcmpi(mdt[j][k],"NULL");k++)
				{
					for(l=mnt[mntp].alaindex;l<alaptr;l++)
					{
						if(!strcmpi(mdt[j][k],ala[l].alaindex))
						{
							fputs("\t",fout);
							fputs(ala[l].actarg,fout);
							fputs("\t",fout);
							break;
						}

					}
					if(l==alaptr)
					{
						fputs("\t",fout);
						fputs(mdt[j][k],fout);
					}

				}
				fputs("\n",fout);
			}

		}

		else
		{
			for(j=0;strcmpi(source[i][j],"NULL");j++)
			{
				fputs(source[i][j],fout);
				fputs("\t",fout);
			}
			fputs("\n",fout);
		}

	}
}

//displayPass1
void MACRO::displayPass1()
{
	int i,j;

	getch();
	cout<<"\n\nMDT\n\n";

	for(i=0;i<mdtptr;i++)
	{
		cout<<i<<"\t";
		for(j=0;strcmp(mdt[i][j],"NULL");j++)
			cout<<mdt[i][j]<<"\t";
		cout<<"\n";
	}

	getch();
	cout<<"\n\nMNT\n\n";

	for(i=0;i<mntptr;i++)
		cout<<i<<"\t"<<mnt[i].macroname<<"\t"<<mnt[i].mdtindex<<"\t"<<mnt[i].alaindex<<"\n";

	cout<<"\n\nALA\n\n";

	for(i=0;i<alaptr;i++)
		cout<<i<<"\t"<<ala[i].alaindex<<"\t"<<ala[i].dummyarg<<"\t"<<ala[i].actarg<<"\n";

}

//pass1
void MACRO::pass1()
{
	int i,j,k;
	int flag;
	char tempstr[10];

	/*
	 *	flag = 0;  //macro search
	 *	flag = 1 //macro found...add to ala mnt & mdt
	 *	flag = 2 //add to mdt the data
	*/

	flag=0;
	mntptr = 0;
	alaptr = 0;
	mdtptr = 0;
	for(i=0;i<totallines;i++)
	{
		j=0;

		if(flag==0)
		{
			if(!strcmpi(source[i][j],"MACRO"))
				flag = 1;
			else if(!strcmpi(source[i][j],"START"))
				break;
		}

		else if(flag==1)
		{
			//add entry to the mnt
			strcpy(mnt[mntptr].macroname,source[i][0]);
			mnt[mntptr].mdtindex = mdtptr;
			mnt[mntptr].alaindex = alaptr;
			mntptr++;

			strcpy(mdt[mdtptr][0],source[i][0]);

			//add entry to the ala
			for(k=1;strcmpi(source[i][k],"NULL");k++)
			{
				strcpy(ala[alaptr].alaindex,"#");
				strcat(ala[alaptr].alaindex,itoa(alaptr,tempstr,10));
				strcat(ala[alaptr].alaindex,"\0");

				strcpy(ala[alaptr].dummyarg,source[i][k]);
				strcpy(ala[alaptr].actarg,"");
				alaptr++;

				strcpy(mdt[mdtptr][k],source[i][k]);
			}

			mdtptr++;
			flag = 2;

		}

		else if(flag==2)
		{
			if(!strcmpi(source[i][0],"MEND"))
			{
				strcpy(mdt[mdtptr][0],"MEND");
				mdtptr++;
				flag = 0;
			}

			else
			{
				for(k=0;strcmpi(source[i][k],"NULL");k++)
				{
					for(j=mnt[mntptr-1].alaindex;j<alaptr;j++)
					{
						if(!strcmpi(ala[j].dummyarg,source[i][k]))
						{
							strcpy(mdt[mdtptr][k],ala[j].alaindex);
							break;
						}
					}

					if(j==alaptr)
						strcpy(mdt[mdtptr][k],source[i][k]);

				}
				mdtptr++;
			}
		}
	}
	sourcestart = i;
}

//readSource()
void MACRO::readSource()
{
	char ch;
	int i,j,k;
	char tempstr[10];

	fin = fopen("source.txt","r");

	i=0;
	j=0;
	k=0;
	totallines = 0;
	strcpy(tempstr,"");
	while(1)
	{
		ch = fgetc(fin);

		if(ch==' ' || ch=='\t' || ch==',' ||ch=='\n' || ch==EOF)
		{
			tempstr[k] = '\0';

			if(strlen(tempstr)>0)
				strcpy(source[i][j++],tempstr);

			if(ch=='\n')
			{
				if(j>0)
				{
					strcpy(source[i][j],"NULL");
					i++;
					totallines++;
				}

				j=0;

			}

			if(ch==EOF)
			{

				if(j>0)
				{
					strcpy(source[i][j],"NULL");
					i++;
					totallines++;
				}

				break;
			}

			k=0;
			strcpy(tempstr,"");
		}
		else
			tempstr[k++] = ch;
	}

	//source
	cout<<"\n\nTHE SOURCE CODE IS::\n\n";

	for(i=0;i<totallines;i++)
	{
		for(j=0;strcmp(source[i][j],"NULL")!=0;j++)
		{
			cout<<source[i][j]<<"\t";
		}
		cout<<"\n";
	}

	for(i=0;i<30;i++)
		for(j=0;j<6;j++)
			strcpy(mdt[i][j],"NULL");
}


