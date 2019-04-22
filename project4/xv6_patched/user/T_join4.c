/* join, not wait, should handle threads */
#include "types.h"
#include "user.h"
#include "syscall.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 1;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   void *stack = malloc(PGSIZE*2);
   assert(stack != NULL);
   if((uint)stack % PGSIZE)
     stack = stack + (4096 - (uint)stack % PGSIZE);

   int arg = 42;
   int clone_pid = clone(worker, &arg, stack);
   printf(1,"%s: clone_pid = %d\n", __func__, clone_pid);
   assert(clone_pid > 0);

   sleep(1);
   assert(wait() == -1);

   void *join_stack;
   int join_pid = join(&join_stack);
   printf(1,"%s: clone_pid = %d, join_pid = %d\n", __func__, clone_pid, join_pid);
   assert(join_pid == clone_pid);
   assert(stack == join_stack);
   printf(1,"%s: global = %d\n", __func__, global);
   assert(global == 2);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   int arg = *(int*)arg_ptr;
   assert(arg == 42);
   assert(global == 1);
   global++;
   exit();
}
