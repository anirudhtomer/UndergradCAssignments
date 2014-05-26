//PROGRAM FOR SINGLE INHERITENCE

#include<iostream.h>
#include<conio.h>

class alpha
{
	int x;

	public:

	int y;

	void enterx()
	{
		cout<<"\nENTER THE VALUE OF \"x\":-\t";
		cin>>x;
	}

	void entery()
	{
		cout<<"\nENTER THE VALUE OF \"y\":-\t";
		cin>>y;
	}

	void dispx()
	{
		cout<<"\n\nTHE VALUE OF x is:-\t";
		cout<<x;
		cout<<"\n\nTHE VALUE OF y IN BASE is:-\t";
		cout<<y;

	}

};

class beta : public alpha
{
	int y;

	public:
	beta():y(2){};

	void enterx()
	{
		cout<<"\t\t\""<<y<<"\""<<endl;

		alpha::enterx();

		cout<<"ENTER THE VALUE OF THE BASE CLASS \"y\" :-\t";
		cin>>y;

		cout<<"\t\t\""<<beta::y<<"\""<<endl;
	}

};

int main()
{
	beta derived;
	alpha basist;

	clrscr();

	basist.enterx();
	basist.dispx();

	derived.enterx();
	derived.dispx();

	basist.dispx();

	getch();
	return 0;
}

