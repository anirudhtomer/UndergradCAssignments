//HOW TO DECLARE A 2D ARRAY AT RUN TIME && USE OF (calloc)

#include<iostream.h>
#include<alloc.h>
#include<conio.h>

int main()
{
	int *ptr,i,j,r,c;

	clrscr();

	cout<<"ENTER THE NUMBER OF ROWS AND COLUMNS:-\t";
	cin>>r>>c;

	ptr = (int*) calloc(r*c,2);

	cout<<"ENTER ARRAY:\n\n";
	for(i=0;i<r;i++)
	{
		cout<<"ENTER ROW "<<i+1<<" :-\n\n";
		for(j=0;j<c;j++)
		{
			cout<<"\t"<<ptr+i*c+j<<"\t::";
			cin>>*(ptr+i*c+j);
		}
	}

	cout<<"\n\nTHE ARRAY IS:-\n\n";
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			cout<<*(ptr+i*c+j)<<"\t";
		}
		cout<<"\n";
	}

	getch();
	return 0;
}
