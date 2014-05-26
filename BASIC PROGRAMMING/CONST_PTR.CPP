//PROGRAM TO CLEAR THE CONCEPTS OF CONSTANT POINTERS

/*	difference between
		int n=5;
		int *const ptr=&n;
and     int const *ptr=&n;		*/

#include<iostream.h>
#include<conio.h>

void main()
{
	int n=5,*const ptr1=&n,m=7;  //ptr1 is constant pointer to integer
	int const *ptr2=&m;   //ptr2 is pointer to constant integer
	//const int *ptr2=&m is also valid
	int *ptr3;

	clrscr();


	/* 1. we can't write " int n=5,*const ptr1=&m,m=7;"
	   because m isn't yet defined. */

//***********OPERATIONS ON  " ptr1  "**************


	cout<<"value in \"n\":-\t"<<n;
	cout<<"\naddress of \"n\":-\t"<<&n;
	cout<<"\nvalue in \"ptr1\":-\t"<<ptr1<<"\tequal to address of \"n\"";

//2.	cout<<"\naddress of \"ptr1\":-\t"<<&ptr1;

/*   you will surely face an error while executing statement 2
but if replace "&ptr1" by "&ptr2" or by "&ptr3" you won't.  */

	cout<<"\nvalue at the address stored at \"ptr1\":-\t"<<*ptr1<<"   same as value in \"n\"";
	*ptr1=6;
	cout<<"\n\nvalue in \"n\":-\t"<<n;
	cout<<"\nvalue in \"ptr1\":-\t"<<*ptr1;
	cout<<"\n\ni have just changed value at *ptr1 & value at n is also changed";
//3.	ptr1=&m;

/*   you will surely face an error while executing statement 3
as it's a constant address pointer which means
"THE ADDRESS STORED IN "ptr1" CAN'T BE CHANGED"
although the initial address stored at "ptr1" is "&n" but you can't
again put "&n" in "ptr1"  */




//***********OPERATIONS ON  " ptr2  "**************
//int const *ptr2=&m;    and value in m=7

	cout<<"\n\n\n\nvalue in \"m\":-\t"<<m;
	cout<<"\naddress of \"m\":-\t"<<&m;
//4.	cout<<"\nvalue in \"ptr2\":-\t"<<ptr2<<"\tequal to address of \"m\"";

/* error for statement 4 ,  replace "ptr2" by "ptr1" or "ptr"
 you won't get.   I don't know why babe!   */
	cout<<"\naddress of \"ptr2\":-\t"<<&ptr2;

	cout<<"\nvalue at the address stored at \"ptr2\":-\t"<<*ptr2<<"   same as value in \"m\"";
	ptr2=&n;
	cout<<"\nvalue at the address stored at \"ptr2\":-\t"<<*ptr2;
//5.	*ptr2=m;

/*   you will surely face an error while executing statement 5
 as it's a constant value pointer which means
"THE VALUE STORED IN "ptr2" CAN'T BE CHANGED BUT ADDRESS CAN BE CHANGED"
but you can change value indirectly by changing the address at "ptr2"   */


	getch();

}