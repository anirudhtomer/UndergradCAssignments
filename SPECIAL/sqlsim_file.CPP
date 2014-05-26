
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<string.h>

class sql
{
	FILE *fp;
	char ch;
	char tempstr[30];
	int i;

	public:

	sql()
	{
		fp = fopen("e:\\dalla.txt","w");
		fclose(fp);

		fp = fopen("e:\\bhalla.txt","w");
		fclose(fp);

	}
	void select();
	void create();
	void insert();
};

int main()
{
	sql s1;
	int chmnu;


	while(1)
	{
		clrscr();
		cout<<"\n\nSQL SIMULATION";
		cout<<"\n1.CREATE\n2.INSERT\n3.SELECT\n4.EXIT";
		cout<<"\n\nenter choice:-\t";
		cin>>chmnu;

		switch(chmnu)
		{
			case 1: s1.create();
					break;

			case 2: s1.insert();
					break;

			case 3: s1.select();
					break;

			case 4: return 0;

		}
		getch();
	}

}

//insert
void sql::insert()
{
	int cnt = 0;
	char str[30];
	FILE *fc;

	cout<<"ENTER THE NAME OF THE TABLE:-\t";
	gets(str);

	fp = fopen("e:\\dalla.txt","r");
	fc = fopen("e:\\bhalla.txt","w");

	while(1)
	{
		ch = fgetc(fp);
		fputc(ch,fc);

		if(ch==EOF)
		{
			cout<<"\nNO SUCH TABLE FOUND";
			fclose(fp);
			fclose(fc);
			return;
		}

		if(ch=='#')
		{
			i = -1;
			do
			{
				tempstr[++i]=fgetc(fp);
				fputc(tempstr[i],fc);
			}while(tempstr[i]!='$');
			tempstr[i]='\0';
		}

		if(!strcmp(tempstr,str))
		{
			cout<<"TABLE FOUND\n\n\n";
			break;
		}
	}

	cnt = 1;
	while(1)
	{
		ch = fgetc(fp);

		if(ch=='$')
			cnt++;

		if(ch==';')
			break;
		fputc(ch,fc);
	}

	fputc('%',fc);
	while(cnt!=0)
	{
		cout<<"ENTER THE field:-\t";
		flushall();
		gets(tempstr);

		for(i=0;tempstr[i]!='\0';i++)
		{
			fputc(tempstr[i],fc);
		}

		cnt--;

		if(cnt!=0)
			fputc('~',fc);
	}

	fputc(';',fc);

	while(1)
	{
		ch = fgetc(fp);
		if(ch==EOF)
			break;

		fputc(ch,fc);
	}

	fclose(fp);
	fclose(fc);

	fp = fopen("e:\\dalla.txt","w");
	fc = fopen("e:\\bhalla.txt","r");

	while(1)
	{
		ch = fgetc(fc);

		if(ch==EOF)
			break;
		fputc(ch,fp);

	}

	fclose(fp);
	fclose(fc);

}

//create
void sql::create()
{
	char str[30];

	cout<<"ENTER THE NAME OF THE TABLE:-\t";
	gets(str);

	fp = fopen("e:\\dalla.txt","a+");

	while(1)
	{
		ch = fgetc(fp);

		if(ch==EOF)
			break;

		if(ch=='#')
		{
			i = -1;
			do
			{
				tempstr[++i]=fgetc(fp);
			}while(tempstr[i]!='$');
			tempstr[i]='\0';
		}

		if(!strcmp(tempstr,str))
		{
			cout<<"TABLE ALREADY PRESENT";
			fclose(fp);
			return;
		}
	}

	fseek(fp,0,SEEK_END);

	fputc('#',fp);
	for(i=0;str[i]!='\0';i++)
		fputc(str[i],fp);

	while(1)
	{
		cout<<"\nENTER THE COLUMN NAME:-\t";
		flushall();
		gets(tempstr);

		if(!strcmpi(tempstr,"exit"))
			break;

		fputc('$',fp);
		for(i=0;tempstr[i]!='\0';i++)
		{
			fputc(tempstr[i],fp);
		}
	}
	fputc(';',fp);
	fclose(fp);

}

void sql::select()
{
	char str[30];

	cout<<"ENTER THE NAME OF THE TABLE:-\t";
	gets(str);

	fp = fopen("e:\\dalla.txt","r");

	while(1)
	{
		ch = fgetc(fp);

		if(ch==EOF)
		{
			cout<<"\nNO SUCH TABLE FOUND";
			fclose(fp);
			return;
		}
		if(ch=='#')
		{
			i = -1;
			do
			{
				tempstr[++i]=fgetc(fp);
			}while(tempstr[i]!='$');
			tempstr[i]='\0';
		}

		if(!strcmp(tempstr,str))
		{
			cout<<"TABLE FOUND\n\n\n";
			break;
		}
	}

	while(1)
	{
		ch = fgetc(fp);

		if(ch=='$')
		{
			cout<<"\t";
			continue;
		}
		if(ch=='%')
			break;
		if(ch==';')
		{
			cout<<"TABLE EMPTY";
			fclose(fp);
			return;
		}

		cout<<ch;
	}

	cout<<"\n\n";
	while(1)
	{
		ch = fgetc(fp);

		if(ch==';')
			break;

		if(ch=='~')
		{
			cout<<"\t";
			continue;
		}

		if(ch=='%')
		{
			cout<<"\n";
			continue;
		}

		cout<<ch;
	}

	fclose(fp);
}