#include<iostream.h>
#include<conio.h>

class A
{
	int i;

	public:
	int j;

	A(int o,int p ,int r)
	{
		i = o;
		j = p;
		k = r;
	}

	void enterA()
	{
		cout<<"\n\n(BASE)ENTER i,j,k:-\t";
		cin>>i>>j>>k;
	}

	void displayA()
	{
		cout<<"\n\n(BASE)i,j,k ARE:-\t";
		cout<<i<<"  "<<j<<"  "<<k;
	}

	protected:
	int k;

};

class B :public A
{
	int l;

	public:
	int m;

	B(int a,int b,int c,int d,int e,int f):A(d,e,f)
	{
		l = a;
		m = b;
		n = c;
	}

	void enterB()
	{
		cout<<"\n\n(DERIV)ENTER j,k,l,m,n:-\t";
		cin>>j>>k>>l>>m>>n;
	}

	void displayB()
	{
		B::displayA();
		cout<<"\n\n(DERIV)j,k,l,m,n ARE:-\t";
		cout<<j<<"  "<<k<<"  "<<l<<"  "<<m<<"  "<<n;
	}

	protected:
	int n;
};

int main()
{
	A a1(1,2,3);
	B b1(-1,-2,-3,-4,-5,-6);

	clrscr();

	a1.enterA();
	a1.displayA();

	b1.enterB();
	b1.displayB();
	b1.enterA();
	a1.displayA();

	b1.displayA();
	b1.displayB();

	getch();

	return 0;
}