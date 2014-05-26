#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>

union
{
	long n;
	char q[4];
}dd;

union
{
	unsigned int n;
	unsigned char q[2];
}wrd;


void main()
{
	unsigned char *buff;
	unsigned char *fatbuff;
	char filename[9],ext[4];

	register int rtno;
	int entry,i,cnt;
	unsigned char j;
	int flag = 0;
	int strt,temp;
	float ftemp;


	buff = new char[513];
	fatbuff = new char[4609];

	clrscr();

	asm mov al,0
	asm mov cx,9
	asm mov dx,1
	asm mov bx,fatbuff
	asm int 0x25

	printf("\nEnter the filename:-\t");
	scanf("%s",filename);

	printf("\nEnter the extension:-\t");
	scanf("%s",ext);


	for(rtno=19;rtno<33;rtno++)
	{
		asm mov al,0
		asm mov cx,1
		asm mov dx,rtno
		asm mov bx,buff
		asm int 0x25

		for(entry=0;entry<512;entry+=32)
		{
			if(!(strnicmp(filename,buff+entry,strlen(filename))) && !(strnicmp(ext,buff+entry+8,strlen(ext))))
			{
				flag = 1;
				wrd.q[0] = buff[entry+0x1a];
				wrd.q[1] = buff[entry+0x1b];
				strt = wrd.n;
				clrscr();
				break;
			}
		}

		if(flag)
			break;
	}

	if(!flag)
	{
		printf("FILE NOT FOUND");
		getch();
		return;
	}

	temp = strt;
	while(strt!=4095)
	{
		temp = 33 + strt - 2;

		asm mov al,0
		asm mov cx,1
		asm mov dx,temp
		asm mov bx,buff
		asm int 0x25

		for(i=0;i<512 && buff[i]!=0;i++)
			printf("%c",buff[i]);

		ftemp = strt * 1.5;

		wrd.q[0] = fatbuff[(int)ftemp];
		wrd.q[1] = fatbuff[(int)ftemp+1];

		if((int)ftemp == ftemp)
			strt = wrd.n & 0x0fff;

		else
			strt = wrd.n >> 4;
	}

	getch();
}