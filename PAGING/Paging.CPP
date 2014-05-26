#include<iostream.h>
#include<conio.h>
#include<string.h>

class PAGING
{
	int curtimestamp;
	int FMT[8];

	struct PAGE
	{
		int virtualnumber;
		char page[8];
		int timestamp;

	}mmpage[32],hdpage[8];

	struct PAGETABLE
	{
		int valid; //0-invalid //1-valid
		int mmaddress;
	}pagetable[40];//PAGE TABLE for	40 pages...8 in hard disk

	public:
	PAGING()
	{
		curtimestamp = 0;
	}

	void initialize();
	void display();

	void LRU_FIFO(int);

};

int main()
{
	PAGING *paging = new PAGING();
	int chmnu;

	while(1)
	{
		clrscr();

		cout<<"********** PAGING *********\n\n";
		cout<<"\n1.LRU\n2.FIFO\n3.Exit\n\nEnter choice:-\t";
		cin>>chmnu;

		paging->initialize();
		cout<<"System Initialized";

		switch(chmnu)
		{
			case 1: paging->LRU_FIFO(0);
					break;

			case 2: paging->LRU_FIFO(1);
					break;

			case 3: return 0;

		}
		getch();
	}

}

//LRU_FIFO  //0 LRU //1 FIFO
void PAGING::LRU_FIFO(int type)
{
	int num,i,min,mmindex,tableindex;
	char ch;

	PAGE *temppage = NULL;

	while(1)
	{
		cout<<"\nEnter the virtual address of the page to watch contents:-\t";
		cin>>num;

		//check for validity in page table
		if(pagetable[num].valid)
		{
			cout<<"\n\n"<<mmpage[pagetable[num].mmaddress].page<<"\n";

			if(type==0)
				mmpage[pagetable[num].mmaddress].timestamp = curtimestamp++;

			display();
		}
		else
		{
			//page fault
			cout<<"PAGE FAULT FOR virtual address "<<num<<"\tPress anything";

			temppage = new PAGE();
			//search in hard disk virtual memory & save in temp space
			temppage->virtualnumber = hdpage[FMT[pagetable[num].mmaddress]].virtualnumber;
			strcpy(temppage->page,hdpage[FMT[pagetable[num].mmaddress]].page);
			temppage->timestamp = curtimestamp++;

			//search the LRU PAGE in main memory
			min = 1000;
			mmindex = 0;
			tableindex = 0;
			for(i=0;i<40;i++)
			{
				if(pagetable[i].valid)
				{
					if(min > mmpage[pagetable[i].mmaddress].timestamp)
					{
						min = mmpage[pagetable[i].mmaddress].timestamp;
						mmindex = pagetable[i].mmaddress;
						tableindex = i;
					}
				}
			}

			//index is the mm index where swapped page is to stored
			//now update the FMT and put the LRU page in hard disk & update its pagetable entry
			pagetable[tableindex].valid = 0;

			hdpage[FMT[pagetable[num].mmaddress]].virtualnumber = mmpage[pagetable[tableindex].mmaddress].virtualnumber;
			strcpy(hdpage[FMT[pagetable[num].mmaddress]].page,mmpage[pagetable[tableindex].mmaddress].page);

			pagetable[tableindex].mmaddress = pagetable[num].mmaddress;
			//copy the older page to mm & update its page table entry
			pagetable[num].valid = 1;
			pagetable[num].mmaddress = mmindex;

			mmpage[mmindex].virtualnumber = temppage->virtualnumber;
			mmpage[mmindex].timestamp = temppage->timestamp;
			strcpy(mmpage[mmindex].page,temppage->page);

			getch();
			display();

		}

		cout<<"DO u want to continue(y/n):-\t";
		cin>>ch;

		if(ch!='y' && ch!='Y')
			break;
	}

}

//display
///DISPLAY PAGES IN MAIN MEMORY and HARD DISK
void PAGING::display()
{
	int i;

	clrscr();
	cout<<"\n\nMAIN MEMORY PAGES ARE\n\n";
	for(i=0;i<32;i++)
	{
		cout<<i<<"\t"<<mmpage[i].virtualnumber<<"\t"<<mmpage[i].timestamp<<"\t"<<mmpage[i].page<<"\n";
	}

	cout<<"\n\nHARD DISK PAGES ARE\n\n";
	for(i=0;i<8;i++)
		cout<<i<<"\t"<<hdpage[i].virtualnumber<<"\t"<<hdpage[i].page<<"\n";


}
//initialization
void PAGING::initialize()
{
	int i;
	char temp[3] = {'\0','\0','\0'};

	curtimestamp = 0;
	for(i=0;i<32;i++)
	{
		mmpage[i].virtualnumber = i;
		mmpage[i].timestamp = curtimestamp++;
		strcpy(mmpage[i].page,"PG ");

		temp[0] = i/10 + 48;
		temp[1] = i%10 + 48;
		strcat(mmpage[i].page,temp);

		pagetable[i].valid = 1;
		pagetable[i].mmaddress = i;
	}

	for(i=0;i<8;i++)
	{
		hdpage[i].virtualnumber = i + 32;
		hdpage[i].timestamp = curtimestamp++;

		strcpy(hdpage[i].page,"PG ");

		temp[0] = ((i+32)/10) + 48;
		temp[1] = ((i+32)%10) + 48;
		strcat(hdpage[i].page,temp);

		pagetable[i+32].valid = 0;
		pagetable[i+32].mmaddress = i;//contains the FMT address now

		FMT[i] = i;
	}

}
