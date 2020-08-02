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


/*void sink() {
	int pd[2];
	int p;			
	while(1) {
		read(0, &p, sizeof(p));
		printf("%d\n", p);
		pipe(pd);
		
		if(fork() > 0) {
			dup2(pd[0], 0);
			close(pd[0]);
			close(pd[1]);
			continue;
		} 

		else if(fork() < 0) {
			printf("Fork failed");
		}

		else {
			dup2(pd[1], 1);
			close(pd[0]);
			close(pd[1]);
			int n;
			while(1) {
				read(0, &n, sizeof(n));
				if(n%p != 0) {
					write(1, &n, sizeof(n));
				}
			}
		}
	}
}

int main() {

	int pd[2];		
	pipe(pd);

	if(fork() > 0) {		
		dup3(pd[0], 0);
		close(pd[0]);
		close(pd[1]);
		sink();
	} 

	else if(fork() == 0) {		
		dup2(pd[1], 1);
		close(pd[0]);
		close(pd[1]);
		
		int n = 2;
		while(1) {
			write(1, &n, sizeof(n));
			n++;
		}
	}

	else {
		printf ("Fork failed");
	}

	return 0;
}
*/
// Concurrent version of prime sieve of Eratosthenes.
// Invented by Doug McIlroy, inventor of Unix pipes.
// See http://plan9.bell-labs.com/~rsc/thread.html.
// The picture halfway down the page and the text surrounding it
// explain what's going on here.
//
// Since NENVS is 1024, we can print 1022 primes before running out.
// The remaining two environments are the integer generator at the bottom
// of main and user/idle.

//#include "lib.h"

int
primeproc(int fd)
{
	int i, id, p, pfd[2], wfd, r;

	// fetch a prime from our left neighbor
top:
	if ((r=read(fd, &p, 4)) != 4)
		printf("primeproc could not read initial prime: %d, %e", r, r >= 0 ? 0 : r);

	printf("%d\n", p);

	// fork a right neighbor to continue the chain
	if ((i=pipe(pfd)) < 0)
		printf("pipe: %e", i);
	if ((id = fork()) < 0)
		printf("fork: %e", id);
	if (id == 0) {
		close(fd);
		close(pfd[1]);
		fd = pfd[0];
		goto top;
	}

	close(pfd[0]);
	wfd = pfd[1];

	// filter out multiples of our prime
	for (;;) {
		if ((r=read(fd, &i, 4)) != 4)
			printf("primeproc %d readn %d %d %e", p, fd, r, r >= 0 ? 0 : r);
		if (i%p)
			if ((r=write(wfd, &i, 4)) != 4)
				printf("primeproc %d write: %d %e", p, r, r >= 0 ? 0 : r);
	}
}

void
umain(void)
{
	int i, id, p[2], r;

	

	if ((i=pipe(p)) < 0)
		printf("pipe: %e", i);

	// fork the first prime process in the chain
	if ((id=fork()) < 0)
		printf("fork: %e", id);

	if (id == 0) {
		close(p[1]);
		primeproc(p[0]);
	}

	close(p[0]);

	// feed all the integers through
	for (i=2;; i++)
		if ((r=write(p[1], &i, 4)) != 4)
			printf("generator write: %d, %e", r, r >= 0 ? 0 : r);
}

