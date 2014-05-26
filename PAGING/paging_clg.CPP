#include<iostream.h>
#include<conio.h>

class PAGING
{
	int framesize,n;

	int page[20],frame[10];

	public:

	void initialize();

	void FIFO();
	void LRU();

};

int main()
{
	PAGING paging;

	clrscr();

	paging.initialize();
//	paging.FIFO();
	paging.LRU();

	getch();
	return 0;
}

//initialize
void PAGING::initialize()
{
	int i;

	cout<<"\nEnter the number of the pages:\t";
	cin>>n;

	cout<<"\nEnter the number of the pages from frame:\t";
	cin>>framesize;

	for(i=0;i<framesize;i++)
		frame[i]=-1;

	cout<<"Enter the pages :\n";
	for(i=0;i<n;i++)
		cin>>page[i];
}

//FIFO
void PAGING::FIFO()
{
	int i,j;
	int curpos = 0;

	cout<<"\n\n";

	for(i=0;i<n;i++)
	{
		for(j=0;j<framesize;j++)
		{
			if(frame[j]==page[i])
				break;
		}

		if(j==framesize)  //page is to be replaced...page fault
		{
			cout<<"(PAGE FAULT) ";

			frame[curpos] = page[i];

			if(++curpos==framesize)
				curpos = 0;
		}
		else
				cout<<"             ";


		cout<<"FRAME CONTENTS:\t";
		for(j=0;j<framesize;j++)
			cout<<frame[j]<<"\t";

		cout<<"\n";
	}
}

//LRU
void PAGING::LRU()
{
	int i,j,minval;
	int curpos = 0;
	int *lru = new int[framesize];
	int timestamp = 0;

	for(i=0;i<framesize;i++)
		lru[i] = -1;

	cout<<"\n\n";

	for(i=0;i<n;i++)
	{
		for(j=0;j<framesize;j++)
		{
			if(frame[j]==page[i])
			{
				lru[j] = timestamp++;
				break;
			}
		}

		if(j==framesize)  //page is to be replaced...page fault
		{
			cout<<"(PAGE FAULT) ";

			minval = 1000;
			curpos = -1;
			for(j=0;j<framesize;j++)
			{
				if(lru[j] < minval)
				{
					curpos = j;
					minval = lru[j];
				}
			}

			frame[curpos] = page[i];
			lru[curpos] = timestamp++;
		}
		else
				cout<<"             ";


		cout<<"FRAME CONTENTS:\t";
		for(j=0;j<framesize;j++)
			cout<<frame[j]<<"\t";

		cout<<"\n";
	}

}
