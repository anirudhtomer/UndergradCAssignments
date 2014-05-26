//PROGRAM TO PERFORM OPERATIONS ON POLYNOMIALS USING
//CIRCULAR LINK LIST
//HERE LAST NODE'S NEXT LINK IS JOINED TO HEAD WHICH COULD HAD BEEN JOINED TO HEAD->NEXT ALSO

#include<iostream.h>
#include<conio.h>
#include<math.h>

class node
{
	int coeff,expo;
	node *next;

	public:
	node()
	{
		coeff = 0;
		expo = 0;
	}

	friend class cll;
};

class cll
{
	node *head;

	public:
	cll()
	{
		head = new node;
		head->next = head;
	}

	void create();
	void add(cll &);
	void multiply(cll &);
	void evaluate();
	void sort();
	void display();

};


int main()
{
	int chmnu;

	cll c1,c2;

	clrscr();

	cout<<"ENTER THE FIRST POLYNOMIAL::\n\n";
	c1.create();
	cout<<"\n\nENTER THE SECOND POLYNOMIAL::\n\n";
	c2.create();

	cout<<"\n\nTHE FIRST POLYNOMIAL IS:-\t";
	c1.display();
	cout<<"\n\nTHE SECOND POLYNOMIAL IS:-\t";
	c2.display();

	while(1)
	{
		getch();
		clrscr();
		cout<<"\n\n\tP O L Y N O M I A L\t O P E R A T I O N S";
		cout<<"\n\n1. ADDITION\n\n2. MULTIPLICATION\n\n3. EVALUATE";
		cout<<"\n\n4. EXIT\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		clrscr();

		switch(chmnu)
		{
			case 1: c1.add(c2);
					break;

			case 2: c1.multiply(c2);
					break;

			case 3: c1.evaluate();
					break;

			case 4: return 0;
			default: cout<<"ENTER PROPER CHOICE";

		}
	}
}

//CREATE

void cll::create()
{
	char dilemma;
	node *temp;

	temp = head;

	do
	{
		temp->next = new node;
		temp = temp->next;
		temp->next = head;

		cin>>temp->coeff;
		cin>>temp->expo;
		cin>>dilemma;

		head->coeff++;
	}while(dilemma == '+');

}

//DISPLAY

void cll::display()
{
	node *temp;

	sort();

	temp = head->next;

	cout<<"\n\n";
	while(temp!=head)
	{
		if(temp->coeff)
			cout<<temp->coeff<<"X^"<<temp->expo<<" + ";

		temp = temp->next;
	}
	cout<<"\b\b ";

}

//SORT POLYNOMIAL
void cll::sort()
{
	int i,j;
	node *temp,*prev;

	//phase 1........find nodes with same coeff & add into one node
	temp = head->next;

	while(temp!=head)
	{
		prev = temp->next;
		while(prev!=head)
		{
			if(prev->expo == temp->expo)
			{
				temp->coeff +=prev->coeff;
				prev->coeff = 0;
			}
			prev = prev->next;
		}

		temp = temp->next;
	}

	//phase 2...........delete all nodes with coeff zero

	temp = head->next;
	prev = head;

	while(temp!=head)
	{
		if(!temp->coeff)
		{
			prev->next = temp->next;
			delete(temp);
			temp = prev->next;
			head->coeff--;
		}
		else
		{
			temp = temp->next;
			prev = prev->next;
		}
	}

	//phase 3.........sort it

	for(i=0;i<head->coeff-1;i++)
	{
		temp = head->next;
		prev = head;

		for(j=0;j<head->coeff-i-1;j++)
		{
			if(temp->expo > temp->next->expo)
			{
				prev->next = temp->next;
				temp->next = temp->next->next;
				prev->next->next = temp;
			}
			else
				temp = temp->next;

			prev = prev->next;

		}
	}



}

//ADDITION

void cll::add(cll & adder)
{
	node *temp1,*temp2,*res;
	cll resadd;

	res = resadd.head;
	temp1 = head->next;
	temp2 = adder.head->next;

	while(temp1!=head && temp2!=adder.head)
	{
		res->next = new node;
		res = res->next;

		resadd.head->coeff++;

		if(temp1->expo == temp2->expo)
		{
			res->expo = temp1->expo;
			res->coeff = temp1->coeff + temp2->coeff;
			temp1 = temp1->next;
			temp2 = temp2->next;
			continue;
		}

		if(temp1->expo < temp2->expo)
		{
			res->expo = temp1->expo;
			res->coeff = temp1->coeff;
			temp1 = temp1->next;
			resadd.head->coeff++;
		}
		else
		{
			res->expo = temp2->expo;
			res->coeff = temp2->coeff;
			temp2 = temp2->next;
		}

		res->next = resadd.head;
	}

	if(temp1!=head)
	{
		res->next = new node;
		res = res->next;

		res->expo = temp1->expo;
		res->coeff = temp1->coeff;
		temp1 = temp1->next;

		res->next = resadd.head;

		resadd.head->coeff++;
	}

	if(temp2!=resadd.head)
	{
		res->next = new node;
		res = res->next;

		res->expo = temp2->expo;
		res->coeff = temp2->coeff;
		temp2 = temp2->next;

		res->next = resadd.head;
		resadd.head->coeff++;
	}

	cout<<"THE FIRST POLYNOMIAL IS ::\n\n";
	display();

	cout<<"\n\n\nSECOND POLYNOMIAL IS::\n\n";
	adder.display();

	cout<<"\n\n\nTHE RESULT OF ADDITION IS::\n\n";
	resadd.display();

	//now delete everything
	temp1 = resadd.head->next;

	while(temp1!=resadd.head)
	{
		temp2 = temp1->next;
		delete(temp1);
		temp1 = temp2;
	}
	delete(temp1);

}

//MULTIPLICATION

void cll::multiply(cll & multer)
{
	node *temp1,*temp2,*res;
	cll resmult;

	res = resmult.head;
	temp1 = head->next;

	while(temp1!=head)
	{
		temp2 = multer.head->next;
		while(temp2!=multer.head)
		{
			res->next = new node;
			res = res->next;

			res->coeff = temp1->coeff*temp2->coeff;
			res->expo = temp1->expo+temp2->expo;

			temp2 = temp2->next;
			resmult.head->coeff++;
			res->next = resmult.head;
		}
		temp1 = temp1->next;
	}

	cout<<"THE FIRST POLYNOMIAL IS ::\n\n";
	display();

	cout<<"\n\n\nSECOND POLYNOMIAL IS::\n\n";
	multer.display();

	cout<<"\n\n\nTHE RESULT OF MULTIPLICATION IS::\n\n";
	resmult.display();

	//now delete everything
	temp1 = resmult.head->next;

	while(temp1!=resmult.head)
	{
		temp2 = temp1->next;
		delete(temp1);
		temp1 = temp2;
	}
	delete(temp1);

}

//EVALUATION OF POLYNOMIAL

void cll::evaluate()
{
	int value,sum=0;
	node *temp;

	temp = head->next;

	cout<<"ENTER THE VALUE OF THE VARIABLE \"X\":-\t";
	cin>>value;

	while(temp!=head)
	{
		sum +=  temp->coeff* (pow(value,temp->expo));

		temp = temp->next;
	}

	cout<<"\n\nTHE RESULT OF EVALUATION IS :-\t"<<sum;
}