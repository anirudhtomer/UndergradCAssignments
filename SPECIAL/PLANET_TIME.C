#include<stdio.h>
void main()
{
	int ntua,ntub,i,j;
	float timea[15],timeb[15],mula,mulb;
	int itemp,itemp2;
	float pta[15],ptb[15],sumb[i],ftemp;
	float conv,conb,unia[15],unib[15],prea,preb;
	
	
	printf("Enter the number of time units on planet A:-\t");
	scanf("%d",&ntua);
	printf("\n\nNow enter the time units at planet A\n\n");
	for(i=0;i<ntua;i++)
	{
		scanf("%f",*(timea+i));
	}
	printf("Enter the number of time units on planet A:-\t");
	scanf("%d",&ntub);
	printf("\n\nNow enter the time units at planet A\n\n");
	for(i=0;i<ntub;i++)
	{
		scanf("%f",*(timeb+i));
	}

	for(i=0,mula=1.0;i<ntua;i++)
	{
		mula=mula*timea[i];
		
	}
	for(i=0,mulb=1.0;i<ntub;i++)
	{
		mulb=mulb*timeb[i];
		
	}
	conv=(float)(mulb*1.0/mula);
	printf("\nEnter the time at planet A:-\t");
	
	for(i=0;i<ntua;i++)
	{
		scanf("%f",&pta[i]);
	}
	for(i=0,prea=0.0;i<ntua;i++)
	{
		prea=prea+((mula/timea[i])*(pta[i]));
	}
	conb=conv*prea;
	for(i=0;i<ntub;i++)
	{
		for(j=i+1,sumb[i]=1.0;j<ntub;j++)
		{
			sumb[i]*=timeb[j];
		}
	}
	printf("\nTHE TIME AT PLANET B IS:\n");
	for(i=0;i<ntub;i++)
	{
		ptb[i]=conb/sumb[i];
		itemp2=(int)(conb/sumb[i]);
		ftemp=ptb[i]-itemp2;
		conb=ftemp*sumb[i];
		printf(" %d :",itemp2);
	}
	
}


in

5
14
25
60
18
19
6
7
8
9
11
13
15
9
12
44
10
4


out

4
6
0
3
10
14


		
