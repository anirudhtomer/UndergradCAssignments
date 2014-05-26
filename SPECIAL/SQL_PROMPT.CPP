//ANIRUDH TOMER....TE COMP-1...42037

#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define SIZECMD 100
#define SIZETAB 20
#define SIZEVARCHAR 20

#define STR_SELECT "select * from"
#define STR_INSERT "insert into"
#define STR_CREATE "create table"

#define NUMBER "number"
#define VARCHAR "varchar"
#define FLOAT "float"

#define DT_NUM 0
#define DT_FLT 1
#define DT_VAR 2

class tuple
{
	public:

	static int n_int,n_flt,n_str;

	long *ptr_int;
	float *ptr_flt;
	char *ptr_str;

	tuple *nxt_tpl;

	tuple()
	{
		ptr_int = NULL;
		ptr_flt = NULL;
		ptr_str = NULL;
		nxt_tpl = NULL;
	}
};

int tuple::n_int = 0;
int tuple::n_flt = 0;
int tuple::n_str = 0;

class node
{
	public:

	tuple *t1;

	char *tabname;

	node *next;

	node(char *name)
	{
		tabname = new char[SIZETAB];
		strcpy(tabname,name);
		next = NULL;
		t1 = new tuple();
	}
};

class list_tab
{
	public:

	node *head;

	list_tab()
	{
		head = new node("HEAD");
	}

	node* addtab(char *);

};

class sql
{
	list_tab l1;

	const int CREATE,INSERT,SELECT;

	char *str,*tempname,*tempstr;


	public:
	sql():CREATE(1),INSERT(2),SELECT(3)
	{
		str = new char[SIZECMD];
		tempstr = new char[SIZECMD];
		tempname = new char[SIZETAB];

		cout<<"oracle tcc_edition COPYRIGHTED @ TEAM R1...\n\n";
		cout<<"TYPE \"exit\" TO GET THE HELL OUT OF HERE";

		cout<<"\n\n";

	}

	~sql()
	{
		delete []tempname;
		delete []str;
		delete []tempstr;

		str = NULL;
		tempname = NULL;
		tempstr = NULL;
	}

	int cmd_check()
	{
		return 0;
	}

	void gen_syntax()
	{
		cout<<"THE COMMAND U ENTERED HAS WRONG SYNTAX";
	}

	void gen_nosuchtable()
	{
		cout<<"NO SUCH TABLE PRESENT";
	}

	//controlling the prompt
	int prompt_control();

	//COMMANDS OF SQL TO BE IMPLEMENTED
	int create_table();
	int insert_into();
	int select_all();
};

int main()
{
	clrscr();
	return (new sql()->prompt_control());
}

//CONTROLLING THE PROMPT
int sql::prompt_control()
{
	int i,j,flag;

	while(1)
	{
		strcpy(str,"");
		strcpy(tempstr,"");

		flag = 0;
		i=2;

		cout<<"\nSQL>";

		//get one complete command till ;
		while(strstr(tempstr,";")==NULL)
		{
			flushall();
			gets(tempstr);

			strcat(str,tempstr);

			if(!strncmpi(str,"exit",strlen("exit")))
				exit(1);

			if(strstr(tempstr,";")==NULL)
			{
				cout<<"\n  "<<i++<<") ";
				strcat(str," ");
			}
		}

		//remove all spaces before first occurance of a character
		for(i = 0 ;str[i]!='\0';i++)
			if(str[i] != ' ')
				break;

		if(str[i]==';')
		{
			gen_syntax();
			continue;
		}

		for(j=0 ;str[i]!='\0';i++)
		{
			if(str[i]==' ' && (str[i+1]==' ' ||str[i+1] == '\0'))
				continue;

			tempstr[j++] = str[i];

		}
		tempstr[j] = '\0';

		if(tempstr[strlen(tempstr)-2]==' ')
		{
			tempstr[strlen(tempstr)-2] = ';';
			tempstr[strlen(tempstr)-1] = '\0';
		}

		strcpy(str,tempstr);

		//check for exit
		if(!strncmpi(str,"exit",strlen("exit")))
			return 0;

		//check for select * from
		if(!strncmpi(str,STR_SELECT,strlen(STR_SELECT)))
		{
			flag = select_all();
		}

		//check for insert into
		else if(!strncmpi(str,STR_INSERT,strlen(STR_INSERT)))
		{
			flag = insert_into();
		}

		//check for create table
		else if(!strncmpi(str,STR_CREATE,strlen(STR_CREATE)))
		{
			flag = create_table();
		}

		if(!flag)
			gen_syntax();
	}
}

//CREATE TABLE
int sql::create_table()
{
	int i,j,k,sum;
	node * temp;

	//check for the name now
	if(str[strlen(STR_CREATE)]!=' ')
		return 0;

	for(i = strlen(STR_CREATE) + 1,j=0;str[i]!='(' && str[i]!=';';i++)
	{
		if(str[i]!=' ')
			tempname[j++] = str[i];
	}

	tempname[j] = '\0';

	if(str[i]==';')
		return 0;

	j=0;
	for(j=0;str[i]!=';';i++)
	{
		if(str[i]=='(')
		{
			j++;
			continue;
		}
		if(str[i]==')')
			j--;
	}

	if(j!=0)
		return 0;

	//now name is in tempname
	temp = l1.addtab(tempname);

	strcpy(tempname,"");

	str = strchr(str,'(');

	j = 0; //to calculate the number of commas
	for(i=0,sum=0;str[i]!=';';i++) //to calc number of fields & allocate mem
	{

		if(str[i]==',')
			j++;

		strcpy(tempname,"");
		strncpy(tempname,str+i,strlen(VARCHAR));

		if(!strncmpi(tempname,NUMBER,strlen(NUMBER)))
		{
			temp->t1->n_int++;
			sum++;
			continue;
		}

		if(!strncmpi(tempname,FLOAT,strlen(FLOAT)))
		{
			temp->t1->n_flt++;
			sum++;
			continue;
		}

		if(!strncmpi(tempname,VARCHAR,strlen(VARCHAR)))
		{
			temp->t1->n_str++;
			sum++;
		}
	}

	if(j!=sum-1)
		return 0;

	if(sum)
	{
		temp->t1->ptr_flt = new float(sum);
		temp->t1->ptr_int = new long[sum];
		temp->t1->ptr_str = new char[sum *  SIZEVARCHAR];
	}

	j=0;
	for(i=0;str[i]!=';';i++)
	{
		while(str[i]==' '||str[i]=='('||str[i]==')')
			i++;

		k=0;
		while(str[i]!=' ')
		{
			*(temp->t1->ptr_str + j*SIZEVARCHAR + k++) = str[i];
			i++;
		}
		*(temp->t1->ptr_str + j*SIZEVARCHAR +k) = '\0';

		i++;

		if(str[i]=='n' ||str[i] == 'N')
			temp->t1->ptr_int[j++] = DT_NUM;

		else if(str[i]=='f' ||str[i] == 'F')
			temp->t1->ptr_int[j++] = DT_FLT;

		else if(str[i]=='v' ||str[i] == 'V')
			temp->t1->ptr_int[j++] = DT_VAR;
		else
			return 0;

		while(str[i]!=',' && str[i]!=';')
			i++;
		if(str[i]==';')
			break;

	}

	cout<<"\n\nTABLE CREATED SUCCESSFULLY";

	return 1;
}

//INSERT INTO
int sql::insert_into()
{
	int i,j,k,nint=0,nflt=0,nstr=0,l=0;
	float sum;
	node * temp = NULL;
	tuple *nxt;

	//check for the name now
	for(i = strlen(STR_INSERT) + 1,j=0;(str[i]!='(' && str[i]!=' ');i++)
	{
		tempname[j++] = str[i];
	}
	tempname[j] = '\0';

	if(str[i]=='(')
		return 0;
	i++;

	if(strncmpi(str+i,"values",strlen("values")))
		return 0;

	//search this name in the list of all tables
	temp = l1.head->next;

	while(temp!=NULL)
	{
		if(!strcmp(tempname,temp->tabname))
			break;
		temp = temp->next;
	}

	if(temp == NULL)
	{
		cout<<"NO SUCH TABLE FOUND";
		return 1;
	}

	str = strchr(str,'(');

	for(i=0,j=0,k=0;str[i]!=';';i++)
	{
		if(str[i]==',')
			j++;
		if(str[i]=='(')
			k++;
		if(str[i]==')')
			k--;
	}

	if(k) //the number of ( & ) & not maintained
		return 0;
	if(j!=(int)(*temp->t1->ptr_flt) -1) //the number of arguments are less
		return 0;

	nxt = temp->t1;

	while(nxt->nxt_tpl!=NULL)
		nxt = nxt->nxt_tpl;

	nxt->nxt_tpl = new tuple();
	nxt = nxt->nxt_tpl;

	if(nxt->n_int)
		nxt->ptr_int = new long[nxt->n_int];

	if(nxt->n_flt)
		nxt->ptr_flt = new float[nxt->n_flt];

	if(nxt->n_str)
		nxt->ptr_str = new char[nxt->n_str * SIZEVARCHAR];


	j=0;
	for(i=1;str[i]!=';';i++)
	{
		k=0;

		while(str[i]!=',' && str[i]!=')')
		{
			tempname[k++] = str[i];
			i++;
		}
		tempname[k]='\0';

		sum=0;
		switch(*(temp->t1->ptr_int + j++))
		{
			case DT_NUM: for(k=0;tempname[k]!='\0';k++)
							sum +=  (tempname[k]-48) * pow(10,strlen(tempname)-k-1);
						 nxt->ptr_int[nint++] = sum;

						 break;

			case DT_FLT: if(strstr(tempname,".")==NULL)
						 {
							for(k=0;tempname[k]!='\0';k++)
								sum +=  (tempname[k]-48) * pow(10,strlen(tempname)-k-1);
							nxt->ptr_flt[nflt++] = sum;

							break;

						 }
						 for(k=0,l=0;tempname[k]!='.';k++)
							l++;

						 for(k=0;tempname[k]!='.';k++)
							sum +=  (tempname[k]-48) * pow(10,l-k-1);

						 for(++k,l=1;tempname[k]!='\0';k++,l++)
								sum +=  (tempname[k]-48) * pow(10,-l);

						 nxt->ptr_flt[nflt++] = sum;

						 break;

			case DT_VAR:strcpy( (nxt->ptr_str + nstr++ * SIZEVARCHAR),tempname);

						break;
		}


	}

	cout<<"\n\nVALUES INSERTED";
	return 1;
}

//SELECT *
int sql::select_all()
{
	int i,nint =0,nflt = 0,nstr=0;
	node *temp;
	tuple *nxt;

	//check if whole command is typed

	strcpy(tempname,"");
	str = str + strlen(STR_SELECT);

	if(*str!=' ')
		return 0;

	while(*str==' ')
		str++;

	for(i=0;str[i]!=';';i++)
	{
		tempname[i] = str[i];
	}
	tempname[i] = '\0';

	if(!strcmp(tempname,""))
	{
		gen_syntax();
		cout<<"\n";
		gen_nosuchtable();
		return 1;
	}

	temp = l1.head->next;

	while(temp!=NULL)
	{
		if(!strcmp(temp->tabname,tempname))
			break;

		temp = temp->next;
	}

	if(temp==NULL)
	{
		gen_nosuchtable();
		return 1;
	}

	//now display all tuples & table
	cout<<"\n\t\t****"<<temp->tabname<<"****\n\n";

	nxt = temp->t1;

	//display all tuples
	for(i=0;i<*temp->t1->ptr_flt;i++)
		cout<<nxt->ptr_str + i*SIZEVARCHAR<<"\t";

	//display all data
	while(nxt->nxt_tpl!=NULL)
	{
		cout<<"\n";
		nxt = nxt->nxt_tpl;
		nint=0;
		nflt=0;
		nstr=0;
		for(i=0;i<*temp->t1->ptr_flt;i++)
		{
			switch(*(temp->t1->ptr_int + i))
			{
				case DT_NUM:cout<<*(nxt->ptr_int + nint++)<<"\t";
							break;

				case DT_FLT:cout<<*(nxt->ptr_flt + nflt++)<<"\t";
							break;

				case DT_VAR:cout<<nxt->ptr_str +(nstr++)*SIZEVARCHAR<<"\t";

			}
		}
	}

	return 1;
}

//ADD A NEW LIST TO SQL
node* list_tab::addtab(char *name)
{
	node * temp;
	temp = head;
	while(temp->next!=NULL)
		temp = temp->next;

	temp->next = new node(name);
	temp = temp->next;

	return temp;
}
