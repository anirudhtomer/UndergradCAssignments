#include<stdio.h>
#include<conio.h>
#include<math.h>

union
{
	long n;
	char q[4];
}num;

void main()
{
	unsigned char *buff;
	register int rtno;
	int entry,i,cnt;
	unsigned char j;

	char fileatr[8][20] = {"READ ONLY","HIDDEN","SYSTEM","VOLUME LABEL","DIRECTORY","ARCHIVE","RESERVED","RESERVED"};

	clrscr();
	buff = new char[512];

	for(rtno=19;rtno<33;rtno++)
	{
		// total no of sectors to be read are 14
		// each sector has 512 byte & entry for each file has 32 bytes
		// so per sector we have 512/32 =  16 entries

		asm mov al,0
		asm mov cx,1
		asm mov dx,rtno
		asm mov bx,buff
		asm int 0x25

		for(entry=0;entry<512;entry+=32)
		{
				i = 0;

				if( (buff[entry+i]==0xe5) || (buff[entry+i]==0))
				{
					//root directory never used
					continue;
				}
				else
				{
					for(;i<8;i++)
						printf("%c",buff[entry+i]);
					printf(".");

					for(;i<0xb;i++)
						printf("%c",buff[entry+i]);

					for(j=1,cnt=0;j<128;j = j<<1,cnt++)
					{
						if( (buff[entry+i] & j) )
							printf("  %s",fileatr[cnt]);
					}

					i = 0x1c;

					num.q[0] = buff[entry+i];
					num.q[1] = buff[entry+i+1];
					num.q[2] = buff[entry+i+2];
					num.q[3] = buff[entry+i+3];

					printf("  %u bytes",num.n);

				}
				printf("\n\n");
		}
	}

	getch();
}
