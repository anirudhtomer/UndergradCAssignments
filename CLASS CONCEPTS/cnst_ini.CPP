//HOW TO INITIALIZE CONSTANT MEMBER & STATIC MEMBERS OF A CLASS

#include<iostream.h>

class A
{
	const int cnst;
	static int statc;
	int xtra;

	public:

	A(int m):cnst(m)
	{

	};

	static void its_static() //can access static member functions only
	{
		statc = 9;
	}
};

int A::statc = 4;


int main()
{
	A a1(2);

	A::its_static();

	return 0;
}

//DEFINITION OF STATIC FUNCTION

