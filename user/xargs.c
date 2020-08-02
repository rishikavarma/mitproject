#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"
#include "kernel/fcntl.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user/user.h"

void main(int argc, char *argv[]){
	int i;
	
	
	char *inp[argc];
	char c;
	top:
	
	for(i=0;i<argc-1;i++){
		inp[i]=argv[i+1];	
	}
	char buff[512];
	read(0, &c, 1);
	i=0;
	while(c!='\n'){		
		buff[i]=c;
		i++;
		read(0, &c, 1);
	}
	buff[i]='\0';
	//printf("%s\n",buff);
	inp[argc-1]=buff;
	int fd=fork();
	if(fd>0){
		fd=wait();
		goto top;
	}
	else if(fd==0){
		exec(argv[1],inp);
	}
	else{
		printf("Error\n");
	}
	exit();
}
