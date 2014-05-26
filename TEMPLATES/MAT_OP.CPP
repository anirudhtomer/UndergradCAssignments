//ANIRUDH TOMER....SE 42028....SE COMP-I
//PROGRAM TO PERFORM MATRIX OPERATIONS USING TEMPLATES

#include<iostream.h>
#include<conio.h>

template<class T>

class matop
{
	int r1,c1,r2,c2;
	T *arr1,*arr2;

	public:

	matop()
	{
		arr1=NULL;
		arr2=NULL;
	}

	~matop()
	{
		if(arr1)
			delete [] arr1;

		if(arr2)
			delete [] arr2;
	}

	void enter_mat();

	void add_mat();
	void sub_mat();
	void mult_mat();
	void trans_mat();
};

int main()
{
	int chtype = 3,chop;

	matop <int> int_mat;
	matop <float> float_mat;

	while(chtype !=1 && chtype!=2)
	{
		clrscr();

		cout<<"\n\n\t*********** MATRIX OPERATIONS USING TEMPLATES***********";
		cout<<"\n\n\n1.INTEGER MATRIX\n\n2.FLOATING PT .MATRIX\n\n3.EXIT";

		cout<<"\n\nENTER CHOICE:-\t";
		cin>>chtype;

		clrscr();

		switch(chtype)
		{
			case 1: int_mat.enter_mat();
					break;

			case 2: float_mat.enter_mat();
					break;

			case 3: return 0;

			default: cout<<"\n\n\nENTER EITHER \"1\" or \"2\"";
		}
		getch();

	}


	while(1)
	{
		clrscr();
		cout<<"\n\n\t\t******* OPERATIONS ON MATRIX ************";
		cout<<"\n\n1. ADDITON OF MATRICES\n\n2. SUBTRACTION OF MATRICES";
		cout<<"\n\n3. MULTIPLICATION OF MATRICES\n\n";
		cout<<"4. TRANSPOSE OF FIRST MATRIX\n\n5. EXIT";

		cout<<"\n\nENTER YOUR CHOICE:-\t";
		cin>>chop;

		clrscr();

		switch(chop)
		{
			case 1: if(chtype==1)
						int_mat.add_mat();
					else
						float_mat.add_mat();

					break;

			case 2: if(chtype==1)
						int_mat.sub_mat();
					else
						float_mat.sub_mat();

					break;

			case 3: if(chtype==1)
						int_mat.mult_mat();
					else
						float_mat.mult_mat();

					break;

			case 4: if(chtype==1)
						int_mat.trans_mat();
					else
						float_mat.trans_mat();

					break;

			case 5: return 0;

			default: cout<<"\n\n\nENTER PROPER CHOICE";
		}

		getch();
	}

}


/***********FUNCTION TO ENTER MATRIX*************/
template <class T>
void matop<T>::enter_mat()
{
	int i,j;

	cout<<"ENTER THE SIZE OF 1st MATRIX (r*c):-\t";
	cin>>r1>>c1;

	arr1 = new T[r1*c1];

	cout<<"\n\n\nENTER THE 1st MATRIX :-\n";

	for(i=0;i<r1;i++)
	{
		cout<<"\nENTER "<<c1<<" ROW "<<i+1<<" ELEMENTS:-\t";
		for(j=0;j<c1;j++)
		{
			cin>>*(arr1+i*c1+j);
		}
	}


	cout<<"\n\n\n\nENTER THE SIZE OF 2nd MATRIX (r*c):-\t";
	cin>>r2>>c2;

	arr2 = new T[r2*c2];

	cout<<"\n\nENTER THE 2nd MATRIX :-\n";

	for(i=0;i<r2;i++)
	{
		cout<<"\nENTER "<<c2<<" ROW "<<i+1<<" ELEMENTS:-\t";
		for(j=0;j<c2;j++)
		{
			cin>>*(arr2+i*c2+j);
		}
	}

}

/************** MATRIX ADDITION *******************/
template <class T>
void matop<T>::add_mat()
{
	int i,j;

	T *res;

	if(r1!=r2 || c1!=c2)
	{
		cout<<"\n\nMATRICES CAN'T BE ADDED AS either r1!=r2 or c1!=c2 ";
		return;
	}


	res = new T[r1*c1];

	cout<<"\nTHE RESULT OF MATRIX ADDITION IS:-\n\n";

	for(i=0;i<r1;i++)
	{
		cout<<"\n\n";
		for(j=0;j<c1;j++)
		{
			*(res+i*c1+j) = *(arr1+i*c1+j)  + *(arr2+i*c1+j);
			cout<<*(res+i*c1+j)<<"\t";
		}

	}

	delete [] res;
}


/************** MATRIX SUBTRACTION *******************/
template <class T>
void matop<T>::sub_mat()
{
	int i,j;

	T *res;

	if(r1!=r2 || c1!=c2)
	{
		cout<<"\n\nMATRICES CAN'T BE SUBTRACTED AS either r1!=r2 or c1!=c2 ";
		return;
	}


	res = new T[r1*c1];

	cout<<"\nTHE RESULT OF MATRIX SUBTRACTION IS:-\n\n";

	for(i=0;i<r1;i++)
	{
		cout<<"\n\n";
		for(j=0;j<c1;j++)
		{
			*(res+i*c1+j) = *(arr1+i*c1+j)  - *(arr2+i*c1+j);
			cout<<*(res+i*c1+j)<<"\t";
		}

	}
	delete [] res;
}

/************** MATRIX TRANSPOSE *******************/
template <class T>
void matop<T>::trans_mat()
{
	int i,j;

	T *res;

	res = new T[r1*c1];

	cout<<"\nTHE TRANSPOSED MATRIX IS:-\n\n";

	for(i=0;i<c1;i++)
	{
		cout<<"\n\n";
		for(j=0;j<r1;j++)
		{
			*(res+i*r1+j) = *(arr1+j*c1+i);
			cout<<*(res+i*r1+j)<<"\t";
		}

	}
	delete [] res;
}


/************** MATRIX MULTIPLICATION *******************/
template <class T>
void matop<T>::mult_mat()
{
	int i,j,k;

	T *res;

	if(c1!=r2)
	{
		cout<<"\n\nMATRICES CAN'T BE MULTIPLIED AS c1!=r2";
		return;
	}


	res = new T[r1*c2];

	cout<<"\nTHE RESULT OF MULTIPLICATION IS:-\n\n";

	for(i=0;i<r1;i++)
	{
		cout<<"\n\n";
		for(j=0;j<c2;j++)
		{
			*(res+i*c2+j) = 0;
			for(k=0;k<c1;k++)
			{
			   *(res+i*c2+j)+= *(arr1+i*c1+k) * *(arr2+k*c2+j);
			}
			cout<<*(res+i*c2+j)<<"\t";
		}
	}
	
	delete [] res;
}

