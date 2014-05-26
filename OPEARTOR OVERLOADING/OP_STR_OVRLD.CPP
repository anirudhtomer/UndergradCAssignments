//ANIRUDH TOMER....SE 42028....SE COMP-I
//OPERATOR OVRELOADING

#include<iostream.h>
#include<conio.h>
#include<string.h>

class overloading
{
	char *str;

	public:

	overloading()  //default constructor
	{
		str = new char[20];
	   //	strcpy(str,NULL);
	}

	//COPY
	void operator ==(overloading &obj2)
	{
		int i;

		for(i=0;str[i]!='\0';i++)
			obj2.str[i]=str[i];

		obj2.str[i]='\0';
	}

	//CONACATINATE
	void operator +(overloading &obj2)
	{
		int i,l=strlen(str);

		for(i=0;obj2.str[i];i++,l++)
			str[l] = obj2.str[i];

		str[l]='\0';
	}
	//EQUALITY
	int operator =(overloading &obj2)
	{
		if(strlen(str)!=strlen(obj2.str))
			return 0;

		int i;

		for(i=0;str[i]!='\0';i++)
			if(str[i]!=obj2.str[i])
				return 0;
		return 1;
	}
	//REVERSE

	void operator !()
	{
		overloading on;
		int i,j=strlen(str);

		strcpy(on.str,str);

		for(i=0;on.str[i]!='\0';i++)
			str[--j]=on.str[i];
	}
	//PALINDORME

	int operator -()
	{
		char *ptr,*ntr;

		ptr=str;
		ntr=str+strlen(str)-1;

		while(*ptr!='\0')
		{
			if(*ptr!=*ntr)
				return 0;
			ptr++;
			ntr--;
		}

		return 1;
	}

	//SUBSTRING
	int operator [] (overloading &obj2)
	{
		int cnt=0;
		char *ptr1,*ptr2;

		ptr1=str;
		while(*ptr1!='\0')
		{
			ptr2=obj2.str;
			while(*ptr2!='\0' && *ptr1!='\0')
			{
				if(*ptr1!=*ptr2)
					break;

				ptr1++;
				ptr2++;
			}

			if(*ptr2=='\0')
				cnt++;
			else if(*ptr1!='\0')
				ptr1++;
		}

		return cnt;
	}

	//display
	friend void operator >>(istream &enter,overloading &str_ing);
	//enter
	friend void operator <<(ostream &disp,overloading &str_ing);

};

int main()
{
	char chmnu;
	overloading o1,o2;

	clrscr();
	cout<<"\n\nENTER THE FIRST STRING:-\t";
	cin>>o1;

	cout<<"\n\nENTER THE SECOND STRING:-\t";
	cin>>o2;

	while(1)
	{
		clrscr();
		cout<<"\n\n\t\t*************** M E N U ***************\n\n";
		cout<<"1.COPY (==)\n2.CONCAT (+)\n3.EQUALITY (=)\n";
		cout<<"4.REVERSE (!)\n5.PALINDROME (-)\n6.SUBSTRING (>=)\n";
		cout<<"7.DISPLAY (<<)\n8.ENTER NEW SET OF STRINGS (>>)\n\n9.EXIT";
		cout<<"\n\nEnter Choice:-\t";
		cin>>chmnu;

		switch(chmnu)
		{
			case '1': o1==o2;
				    cout<<"\n\nTHE COPYED STRING IS:-\t";
				    cout<<o2;
				    break;

			case '2': o1+o2;
					cout<<"\n\nTHE CONCATINATED STRING IS:-\t";
					cout<<o1;
					break;

			case '3': chmnu=o1=o2;

					if(chmnu)
					cout<<"\n\nTHE STRINGS ARE EQUAL";
					else
					cout<<"\n\nTHE STRINGS ARE NOT EQUAL";
					break;

			case '4': !o1;
					cout<<"\n\nTHE REVERSED FIRST STRING IS:-\t";
					cout<<o1;
					break;

			case '5': chmnu=-o1;
					if(chmnu)
						cout<<"\n\nTHE STRING IS A PALINDROME";
					else
						cout<<"\n\nTHE STRING IS NOT A PALINDROME";
					break;

			case '6': chmnu= o1[o2];
					  chmnu += 48;
					  cout<<"\n\nTHE SECOND STRING IS PRESENT "<<chmnu<<" TIMES";
					  break;

			case '7': cout<<"\n\nTHE FIRST STRING IS:-\t";
					cout<<o1;

				    cout<<"\n\nTHE SECOND STRING IS:-\t";
				    cout<<o2;
				    break;

			case '8': cout<<"\n\nENTER THE FIRST STRING:-\t";
				    cin>>o1;

				    cout<<"\n\nENTER THE SECOND STRING:-\t";
				    cin>>o2;
				    break;

			case '9': return 0;
			default:cout<<"\n\nENTER PROPER CHOICE";
		}
		getch();
	}

}
/***********DEFINITION OF THE FRIEND FUNCTION FOR DISPLAY**********/

void operator >> ( istream &enter , overloading &str_ing)
{
	enter>>str_ing.str;
}

void operator << (ostream &disp , overloading &str_ing)
{
	disp<<str_ing.str;
}