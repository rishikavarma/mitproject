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

void
main(int argc, char *argv[])
{
	int parent_fd[2],child_fd[2];
	pipe(parent_fd);
	pipe(child_fd);
	int d=fork();
	if(d>0){
		char buff[2];
		char buff1[2];
		buff[0]='c';
		write(parent_fd[1],buff,1);
		d=wait();
		read(child_fd[0],buff1,1);
		if(buff1[0]=='c'){
			printf("Received pong\n");
		}
		else{
			printf("Didnot receive pong\n");
		}
			
	}  
	else if(d==0){
		char buff[2];
		buff[0]='c';
		char buff1[2];
		read(parent_fd[0],buff1,1);
		if(buff1[0]=='c'){
			printf("Received ping\n");
		}
		else{
			printf("Didnot receive ping\n");
		}
		write(child_fd[1],buff,1);	
	}
	else{
		printf("Error:Didnot fork\n"); 
	}
	exit();
}
