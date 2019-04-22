/* join argument checking */
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
   printf(1, "%s: stack = %d\n", __func__, stack);

   int arg = 42;
   int clone_pid = clone(worker, &arg, stack);
   printf(1,"%s: clone_pid = %d\n", __func__, clone_pid);
   assert(clone_pid > 0);

   printf(1, "%s: sbrk(PGSIZE) = %d\n", __func__, sbrk(PGSIZE));
   void **join_stack = (void**) ((uint)sbrk(0) - 4);
   printf(1, "%s: join_stack = %d\n", __func__, join_stack);
   assert(join((void**)((uint)join_stack + 2)) == -1);
   assert(join(join_stack) == clone_pid);
   assert(stack == *join_stack);
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
