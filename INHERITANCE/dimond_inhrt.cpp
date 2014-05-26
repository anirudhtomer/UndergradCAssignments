//PROGRAM FOR DIAMOND INHERITANCE

#include<iostream.h>
#include<conio.h>

class grandpa
{
	char name[20];

	public:

	grandpa()
	{
		name[0] = 'a';
		name[1] = '\0';
	}

	void enter()
	{
		cout<<"\n\nENTER NAME OF GRANDPA:-\t";
		cin.getline(name,20,'$');
	}


	void display()
	{
		cout<<"\n\nTHE NAME OF THE GRANDPA IS :-\t"<<name;
	}

};

class papa : virtual public grandpa
{
	char name[20];

	public:

	void enter()
	{
		cout<<"\n\nENTER NAME OF PAPA:-\t";
		cin.getline(name,20,'$');
	}

	void hell(){};

};

class mom : virtual public grandpa
{
	char name[20];

	public:
	void enter()
	{
		cout<<"\n\nENTER NAME OF MOM:-\t";
		cin.getline(name,20,'$');
	}
	void hell(){};

};

class son : public papa,mom
{
	char name[20];

	public:

	void enter()
	{
		cout<<"\n\nENTER NAME OF SON:-\t";
		cin.getline(name,20,'$');
	}


   /*	IF THE FOLLOWING DISPLAY FUNCTION  IS USED INSTEAD OF DERIVING VIRTUALLY THEN AMBIGUITY FOR DISPLAY
	ISN'T PRODUCED.

	void display()
	{
		cout<<"\n\nTHE NAME OF THE SON IS :-\t"<<name;
	}    */


};

int main()
{
	son s1;

	clrscr();

	s1.enter();
	s1.display();

	//s1.hell();   //produces ambiguity

	getch();
	return 0;
}

