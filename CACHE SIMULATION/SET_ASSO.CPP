//ANIRUDH TOMER.....TE COMP-I.....42037
//PROGRAM TO IMPLEMENT SET ASSOCIATIVE MEMORY ACCESS IN CACHE

#include<iostream.h>
#include<conio.h>
#define SIZE 0x3fff

class dacs
{
	char mem[SIZE];
	int adr;
	int tagno,setno,byteno;
	char data;

	struct cache
	{
		int tag1,tag2; //though it should be char but i use int for simplicity
		int flag;  // 0 -tag1.......1-tag2
		char byte[2][8];
	}set[32];

	public:

	void initmem();
	void getadr();
	void getfields();
	void getdata();
	void putdata();
};

int main()
{
	char chmnu;

	dacs d1;

	d1.initmem();

	while(1)
	{
		clrscr();
		cout<<"\n\n********** DIRECT ACCESS CACHE ***********";
		cout<<"\n\n1. READ FROM MEMORY\n\n2. WRITE TO MEMORY\n\n3. EXIT";
		cout<<"\n\nENTER CHOICE:-\t";
		cin>>chmnu;

		if(chmnu!='3')
			d1.getadr();

		clrscr();

		switch(chmnu)
		{
			case '1': d1.getdata();
					break;

			case '2': d1.putdata();
					break;

			case '3': return 0;

			default: cout<<"\n\nENTER PROPER CHOICE";
		}
		cin>>chmnu;  //i don't know why but getch() isn't working this time
	}
}

//INITIALIZE MEMORY
void dacs::initmem()
{
	int i;
	unsigned char ch;

	for(i=0,ch=0;i<SIZE;i++)
	{
		mem[i] = ch;
		ch++;

		if(ch>254)
			ch = 0;
	}

	//initialize cache memory
	for(i=0;i<32;i++)
	{
		set[i].tag1 = 0xffff;
		set[i].tag2 = 0xffff;
		set[i].flag = -1;
	}
}

//GET THE ADDRESS FROM THE USER
void dacs::getadr()
{
	clrscr();
	do
	{
		cout<<"\nENTER ANY ADDRESS (in hex):-\t";
		cscanf("%x",&adr);
	}while(adr<0 || adr>SIZE);

	getfields();
}

//GET THE SET,TAG & BYTE FIELDS
void dacs::getfields()
{
	byteno = adr & 0x0007;
	setno = adr & 0x00f8;
	tagno = adr & 0xff00;

	setno = setno>>3;
	tagno = tagno>>8;
}

//READ OPERATION ON CACHE
void dacs::getdata()
{
	int i;

	cprintf("\n\nTHE ADDRESS TO BE ACCESSED (in hex):-\t%x",adr);
	cout<<"\n\nCACHE hit/miss:-\t";

	if(set[setno].tag1 == tagno || set[setno].tag2 == tagno)  //cache hit
	{
		if(set[setno].tag1 == tagno)
			set[setno].flag = 0;
		else
			set[setno].flag = 1;

		cout<<"HIT";
	}

	else  //cache miss
	{
		cout<<"MISS";

		if(set[setno].flag==-1 || set[setno].flag == 1)  //lru is way1 or nothing is lru
		{
			set[setno].tag1 = tagno;
			set[setno].flag = 0;
		}
		else
		{
			set[setno].tag2 = tagno;
			set[setno].flag = 1;
		}

		for(i=0;i<8;i++)
			set[setno].byte[set[setno].flag][i] = mem[(tagno<<8)|(setno<<3)|i];
	}

	data = set[setno].byte[set[setno].flag][byteno];

	cout<<"\n\nWAY NO:-\t"<<set[setno].flag;
	cout<<"\n\nTAG NO:-\t"<<tagno;
	cout<<"\n\nSET NO:-\t"<<setno;
	cout<<"\n\nBYTE NO:-\t"<<byteno;

	cout<<"\n\nDATA OBTAINED:-\t"<<data;
}

//WRITE OPERATION ON CACHE
void dacs::putdata()
{
	int i;

	cout<<"\n\nENTER THE DATA TO BE WRITTEN:-\t";
	cin>>data;

	clrscr();

	cprintf("\n\nTHE ADDRESS TO BE ACCESSED (in hex):-\t%x",adr);
	cout<<"\n\nCACHE hit/miss:-\t";

	mem[adr] = data;

	if(set[setno].tag1 == tagno || set[setno].tag2 == tagno)  //cache hit
	{
		cout<<"HIT";

		if(set[setno].tag1 == tagno)
			set[setno].flag = 0;
		else
			set[setno].flag = 1;

		for(i=0;i<8;i++)
			set[setno].byte[set[setno].flag][i] = mem[(tagno<<8)|(setno<<3)|i];

	}

	else  //cache miss
		cout<<"MISS";

	cout<<"\n\nWAY NO:-\t"<<set[setno].flag<<"\t\t-ve way no shows cache miss";
	cout<<"\n\nTAG NO:-\t"<<tagno;
	cout<<"\n\nSET NO:-\t"<<setno;
	cout<<"\n\nBYTE NO:-\t"<<byteno;

	cout<<"\n\nDATA WRITTEN:-\t"<<data;
}
