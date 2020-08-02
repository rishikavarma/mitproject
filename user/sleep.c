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
  int n;
  if(argc<=1){
    printf("Error: No arguments passed\n");
    exit();
  }
  n=atoi(argv[1]);
  sleep(n);
  exit();
}
