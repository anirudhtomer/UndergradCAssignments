#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc,char *argv[]){
	
	int fdsource,fddest;
	int count;
	char buff[50];
	
	if(argc == 1){
		printf("missing file operand\n");
		return 1; 
		/*that is standard error returned by cp command if u do not give it parameters...try testing it
			type "cp" only on the console...ofcourse and error will come...
			not type "echo $?" to see what was the return status of the last command & u'll see "1"
		*/
	}

	if(argc == 2){
		printf("missing destination after '%s'i\n",argv[1]);
		return 1;
	}

	fdsource = open(argv[1],O_RDONLY);

	fddest = open(argv[2],O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
/*
	there is no point in using the following command

	fddest = open(argv[2],O_CREAT,0666);
	
	REASON::

	the umask on the linux is by default 0022....type umask on console to check urs...
	which means the highest permission while creating a file is rw-r--r--  becuse (0777 - 0022) == 755..or rwx-r-xr-x   
	remove xecute from that coz by default files are not made executable by the OS.....755-111 = 644 or rw-r--r--
	so even if u give 666 the OS converts it to 644 coz of the umask 
*/	
	fddest = open(argv[2],O_WRONLY); //after creating the file...open it in write mode

	while((count = read(fdsource,buff,50))!=0){
		write(fddest,buff,count);
	}

	close(fdsource);
	close(fddest);
	return 0;
}


