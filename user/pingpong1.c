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
	int parent_fd[2];
	int child_fd[2];
	pipe(parent_fd);
	pipe(child_fd);
	int p= fork(); 
	if( p < 0 ) {
		printf("Fork failed\n");
	}

	else if( p > 0 ){
		close(parent_fd[0]);
		write(parent_fd[1], "a", 1);
		close(parent_fd[1]);

		wait();
		char str1[2];

		close(child_fd[1]);
		read(child_fd[0], str1, 1);

		if(str1[0]=='b'){
			printf("Received pong \n");
		}
		else{
			printf("no\n");
		}
	}

	else {
		close(parent_fd[1]);
		char str2[2];
		read(parent_fd[0], str2, 1);

		if(str2[0]=='a'){
			printf("Received ping \n");
		}
		else{
			printf("no\n");
		}

		close(parent_fd[0]);
		close(child_fd[0]);

		write(child_fd[1], "b", 1);
	}

	exit();
}
