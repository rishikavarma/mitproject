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




void main(){
	char buff[34]={2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,34};

	int fd[2];
	pipe(fd);

	int p=fork();
	if(p==0){
		char buff1[2];
		
top:
		if(read(fd[0],buff1,1)){
			int fd1[2],c;
			c=buff[0];
			printf("prime %d\n",c);
			pipe(fd1);
			int p1=fork();
			if(p1==0){
				fd[0]=fd1[0];
				goto top;
			}
			else if(p>0){
				while(read(fd[0],buff1,1)){
					int k=buff1[0];
					if(k%c!=0) write(fd1[1],buff1,1);
				}
				
				close(fd1[0]);
				close(fd1[1]);
			}
			else{
				printf("Error\n");
			}
		}
		
		
	}
	else if(p>0){
		write(fd[1],buff,1000);
		close(fd[1]);
		
	}
	else{
		printf("Error in forking");
	}


}
