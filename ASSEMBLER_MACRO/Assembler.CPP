//ASSEMBLER
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#define IS 0
#define AD 1

#define C 0
#define L 1
#define S 2

class ASSEMBLER
{
	FILE *fin,*fout;
	int totallines;
	int motlen,potlen,reglen;

	char source[30][10][10];

	struct MOT
	{
		char str[10];
	}mot[6];

	struct POT
	{
		char str[10];
	}pot[7];

	struct REG
	{
		char str[5];
	}reg[4];

	struct SYMBOLTAB
	{
		char str[10];
		int address;
		int len;
	}symboltab[10];

	struct LITERALTAB
	{
		int address;
		char str[10];

	}literaltab[10];

	struct INTERMEDIATECODE
	{
		int lc;
		int isad;
		int opcode;
		int opr1;
		int cls;
		int opr2;

	}ic[30];

	struct MACHINECODE
	{
		int lc;
		int opcode;
		int opr1;
		int opr2address;

	}mc[30];

	int pooltab[10];
	int pooltabptr,lc,symboltabptr,literaltabptr,icptr,mcptr;

	public:

	ASSEMBLER()
	{
		motlen = 6;
		potlen = 7;
		reglen = 4;
		pooltabptr = 0;
		symboltabptr = 0;
		literaltabptr = 0;
		icptr = 0;
		mcptr = 0;
		lc = 0;

		pooltab[pooltabptr] = 0;

	}

	void setPOT();
	void setMOT();
	void setREG();

	void readSource();
	void pass1();
	void pass2();
	int checkMOT(char *);
	int checkPOT(char *);
	int checkREG(char *);

	void generror(int i,int j)
	{
		cout<<"error in line "<<i<<" at column "<<j<<"\n";
	}

	void processMOTSYMBOL(int,int,int);
	void processPOTSYMBOL(int,int,int);
	void processSYMBOL(int);
	int addLITERAL(char *);
	int addSYMBOL(char *);

	void displayPass1();

};

int main()
{
	ASSEMBLER assembler;

	clrscr();
	assembler.setMOT();
	assembler.setPOT();
	assembler.setREG();

	assembler.readSource();
	assembler.pass1();
	assembler.displayPass1();
	assembler.pass2();

	getch();
	return 0;
}

//display Pass1
void ASSEMBLER::displayPass1()
{
	int i;

	cout<<"\nLITERAL TABLE:-\n\n";
	for(i=0;i<literaltabptr;i++)
		cout<<i<<"\t"<<literaltab[i].str<<"\t"<<literaltab[i].address<<"\n";

	getch();

	cout<<"\n\nSYMBOL TABLE:-\n\n";
	for(i=0;i<symboltabptr;i++)
		cout<<i<<"\t"<<symboltab[i].str<<"\t"<<symboltab[i].address<<"\t"<<symboltab[i].len<<"\n";

	getch();

	cout<<"\n\nPOOL TABLE:-\n\n";
	for(i=0;i<pooltabptr;i++)
		cout<<i<<"\t"<<pooltab[i]<<"\n";

	getch();

	cout<<"\n\nINTERMEDIATE CODE:-\n\n";
	for(i=0;i<icptr;i++)
	{
		cout<<ic[i].lc<<"\t"<<ic[i].isad<<"\t"<<ic[i].opcode<<"\t"<<ic[i].opr1<<"\t";
		cout<<ic[i].cls<<"\t"<<ic[i].opr2<<"\n";
	}
}

//check REG
int ASSEMBLER::checkREG(char *strsrc)
{
	int i;

	for(i=0;i<reglen;i++)
	{
		if(!strcmpi(strsrc,reg[i].str))
			return i;
	}

	return -1;

}

//check MOT
int ASSEMBLER::checkMOT(char *strsrc)
{
	int i;

	for(i=0;i<motlen;i++)
	{
		if(!strcmpi(strsrc,mot[i].str))
			return i;
	}

	return -1;

}

//check POT
int ASSEMBLER::checkPOT(char *strsrc)
{
	int i;

	for(i=0;i<potlen;i++)
	{
		if(!strcmpi(strsrc,pot[i].str))
			return i;
	}

	return -1;

}

//pass2
void ASSEMBLER::pass2()
{
	int i;
	char *ptr = new char[20];
	fout = fopen("expand.txt","w");

	cout<<"\n\nEXPANDED CODE:\n\n";

	for(i=0;i<icptr;i++)
	{
		if(ic[i].isad==AD)
			continue;

		mc[mcptr].lc = ic[i].lc;
		mc[mcptr].opcode = ic[i].opcode;
		mc[mcptr].opr1 = ic[i].opr1;

		fputs(itoa(mc[mcptr].lc,ptr,10),fout);
		fputs("\t",fout);
		fputs(itoa(mc[mcptr].opcode,ptr,10),fout);
		fputs("\t",fout);
		fputs(itoa(mc[mcptr].opr1,ptr,10),fout);
		fputs("\t",fout);

		switch(ic[i].cls)
		{
			case C: mc[mcptr].opr2address = ic[i].opr2;
					break;
			case L: mc[mcptr].opr2address = literaltab[ic[i].opr2].address;
					break;
			case S: mc[mcptr].opr2address = symboltab[ic[i].opr2].address;
					break;
		}

		fputs(itoa(mc[mcptr].opr2address,ptr,10),fout);
		fputs("\n",fout);

		cout<<mc[mcptr].lc<<"\t"<<mc[mcptr].opcode<<"\t"<<mc[mcptr].opr1<<"\t"<<mc[mcptr].opr2address<<"\n";

		mcptr++;

	}

	fclose(fout);
}

//pass1
void ASSEMBLER::pass1()
{
	int i,index;

	for(i=0;i<totallines;i++)
	{
		if((index = checkMOT(source[i][0]))!=-1)
			processMOTSYMBOL(index,i,1);

		else if((index = checkPOT(source[i][0]))!=-1)
			processPOTSYMBOL(index,i,1);

		else //it is a symbol
			processSYMBOL(i);

	}
}

//process SYMBOL
void ASSEMBLER::processSYMBOL(int instptr)
{
	int temp;

	temp = checkREG(source[instptr][0]);
	if(temp > -1)
		generror(instptr,0);

	//if its a literal
	if(source[instptr][0][0]=='=')
		generror(instptr,0);

	else
	{
		temp = addSYMBOL(source[instptr][0]);
		symboltab[temp].address = lc;

		if((temp = checkMOT(source[instptr][1]))!=-1)
			processMOTSYMBOL(temp,instptr,2);

		else if((temp = checkPOT(source[instptr][1]))!=-1)
			processPOTSYMBOL(temp,instptr,2);
		else
			generror(instptr,1);
	}
}

//processMOTSYMBOL
void ASSEMBLER::processMOTSYMBOL(int opcode,int instptr,int index)
{
	int temp;

	switch(opcode)
	{
		case 1: //movem operand can be only a symbol
				if(!strcmpi(source[instptr][index],"NULL"))
					generror(instptr,index);

				temp = checkREG(source[instptr][index]);
				if(temp > -1)
					generror(instptr,index);

				temp = checkMOT(source[instptr][index]);
				if(temp > -1)
					generror(instptr,index);

				temp = checkPOT(source[instptr][index]);
				if(temp > -1)
					generror(instptr,index);

				//if its a literal
				if(source[instptr][index][0]=='=')
					generror(instptr,1);
				else
				{
					ic[icptr].lc = lc++;
					ic[icptr].isad = IS;
					ic[icptr].opcode = opcode;
					ic[icptr].opr1 = addSYMBOL(source[instptr][index]);
				}


				break;
		default: //mover,add,mul,sub,div
				//read the 1st operand
				if(!strcmpi(source[instptr][index],"NULL"))
					generror(instptr,index);

				temp = checkREG(source[instptr][index]);
				if(temp==-1)
					generror(instptr,index);
				ic[icptr].lc = lc++;
				ic[icptr].isad = IS;
				ic[icptr].opcode = opcode;
				ic[icptr].opr1 = temp;
	}

	//next operand can be only a symbol or a literal
	if(!strcmpi(source[instptr][index+1],"NULL"))
		generror(instptr,index+1);

	temp = checkREG(source[instptr][index+1]);
	if(temp > -1)
		generror(instptr,index+1);
	temp = checkMOT(source[instptr][index+1]);
	if(temp > -1)
		generror(instptr,index+1);

	temp = checkPOT(source[instptr][index+1]);
	if(temp > -1)
		generror(instptr,index+1);

	//if its a literal
	if(source[instptr][index+1][0]=='=')
	{
		ic[icptr].cls = L;
		ic[icptr].opr2 = addLITERAL(source[instptr][index+1]);
	}
	else
	{
		ic[icptr].cls = S;
		ic[icptr].opr2 = addSYMBOL(source[instptr][index+1]);
	}

	icptr++;

}

//processPOTSYMBOL
void ASSEMBLER::processPOTSYMBOL(int opcode,int instptr,int index)
{
	int temp,i;

	switch(opcode)
	{
		case 0: //start
				if(!strcmpi(source[instptr][index],"NULL"))
					ic[icptr].lc = 0;
				else
					ic[icptr].lc = atoi(source[instptr][index]);

				ic[icptr].isad = AD;
				ic[icptr].opcode = opcode;
				ic[icptr].opr1 = -1;
				ic[icptr].cls = C;
				ic[icptr].opr2 = -1;

				lc = ic[icptr].lc;
				icptr++;
				break;

		case 1: //end
				for(i=pooltab[pooltabptr];i<literaltabptr;i++)

				{
					literaltab[i].address = lc;

					ic[icptr].lc = lc++;
					ic[icptr].isad = AD;
					ic[icptr].opcode = opcode;
					ic[icptr].opr1 = -1;
					ic[icptr].cls = L;
					ic[icptr].opr2 = i;

					icptr++;
				}

				pooltabptr++;
				pooltab[pooltabptr] = literaltabptr;

				break;

		case 2: //origin

				break;

		case 3: //ltorg
				for(i=pooltab[pooltabptr];i<literaltabptr;i++)
				{
					literaltab[i].address = lc;

					ic[icptr].lc = lc++;
					ic[icptr].isad = AD;
					ic[icptr].opcode = opcode;
					ic[icptr].opr1 = -1;
					ic[icptr].cls = L;
					ic[icptr].opr2 = i;

					icptr++;
				}

				pooltabptr++;
				pooltab[pooltabptr] = literaltabptr;

				break;

		case 4: //dc
				temp = addSYMBOL(source[instptr][0]);
				symboltab[temp].address = lc;
				symboltab[temp].len = 1;

				ic[icptr].lc = lc++;
				ic[icptr].isad = AD;
				ic[icptr].opcode = opcode;
				ic[icptr].opr1 = -1;
				ic[icptr].cls = C;
				ic[icptr].opr2 = temp;
				icptr++;

				break;

		case 5: //ds
				temp = addSYMBOL(source[instptr][0]);
				symboltab[temp].address = lc;
				symboltab[temp].len = atoi(source[instptr][index]);

				ic[icptr].lc = lc++;
				ic[icptr].isad = AD;
				ic[icptr].opcode = opcode;
				ic[icptr].opr1 = -1;
				ic[icptr].cls = C;
				ic[icptr].opr2 = -1;
				icptr++;

				break;

		case 6: //equ
				temp = addSYMBOL(source[instptr][0]);
				symboltab[temp].address = symboltab[addSYMBOL(source[instptr][index])].address;
				symboltab[temp].len = 1;

				temp = addSYMBOL(source[instptr][index]);

				ic[icptr].lc = lc++;
				ic[icptr].isad = AD;
				ic[icptr].opcode = opcode;
				ic[icptr].opr1 = -1;
				ic[icptr].cls = S;
				ic[icptr].opr2 = temp;
				icptr++;

				break;


	}
}

//add symbol
int ASSEMBLER::addSYMBOL(char *strsrc)
{
	int i,flag=0;

	for(i=0;i<symboltabptr;i++)
	{
		if(!strcmpi(symboltab[i].str,strsrc))
		{
			flag = 1;
			break;
		}
	}

	if(flag==0)
	{
		symboltab[symboltabptr].address = -1;
		symboltab[symboltabptr].len = 1;
		strcpy(symboltab[symboltabptr].str,strsrc);

		symboltabptr++;
	}

	return i;

}
//add LITERAL
int ASSEMBLER::addLITERAL(char *strsrc)
{
	int i;
	int flag = 0;

	for(i=pooltab[pooltabptr];i<literaltabptr;i++)
	{
		if(!strcmpi(literaltab[i].str,strsrc))
		{
			flag = 1;
			break;
		}
	}

	if(flag==0)//not present in literal tab
	{
		literaltab[literaltabptr].address = -1;
		strcpy(literaltab[literaltabptr].str,strsrc);
		literaltabptr++;
	}

	return i;
}

//read source
void ASSEMBLER::readSource()
{
	char *string = new char[40];
	char ch;
	int offset;
	int i,j,k;

	fin = fopen("C:\\tc\\bin\\source.txt","r");

	offset = 0;
	i=0;
	j=0;
	totallines = 0;

	while(1)
	{
		ch = fgetc(fin);

		if(ch==' ' || ch==',' || ch=='\n' || ch=='\t' || ch==EOF)
		{
			string[offset] = '\0';


			if(strlen(string)>0)
				strcpy(source[i][j++],string);

			if(ch==EOF)
			{
				strcpy(source[i][j],"NULL");

				if(j>0)
				{
					i++;
					totallines++;
				}
				j=0;
				break;
			}

			if(ch=='\n')
			{
				strcpy(source[i][j],"NULL");

				if(j>0)
				{
					i++;
					totallines++;
				}
				j=0;
			}

			offset = 0;
		}

		else
			string[offset++] = ch;

	}


	for(i=0;i<totallines;i++)
	{
		for(j=0;strcmpi(source[i][j],"NULL");j++)
		{
			cout<<source[i][j]<<" ";
		}
		cout<<"\n";
	}

}

//set reg
void ASSEMBLER::setREG()
{
	strcpy(reg[0].str,"AREG");
	strcpy(reg[1].str,"BREG");
	strcpy(reg[2].str,"CREG");
	strcpy(reg[3].str,"DREG");
}

//set POT
void ASSEMBLER::setPOT()
{
	strcpy(pot[0].str,"START");
	strcpy(pot[1].str,"END");
	strcpy(pot[2].str,"ORIGIN");
	strcpy(pot[3].str,"LTORG");
	strcpy(pot[4].str,"DC");
	strcpy(pot[5].str,"DS");
	strcpy(pot[6].str,"EQU");
}

//set MOT
void ASSEMBLER::setMOT()
{
	strcpy(mot[0].str,"MOVER");
	strcpy(mot[1].str,"MOVEM");
	strcpy(mot[2].str,"ADD");
	strcpy(mot[3].str,"MUL");
	strcpy(mot[4].str,"SUB");
	strcpy(mot[5].str,"DIV");
}

