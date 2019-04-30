#include "types.h"
#include "user.h"
#include "syscall.h"
#include "thread.h"

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   exit(); \
}

int thread_create(void (*start_routine)(void*), void *arg)
{
    int pgsz = 4096;
    void *stack = malloc(pgsz*2);
    assert(stack != NULL);
    if((uint)stack % pgsz)
        stack = stack + (pgsz - (uint)stack % pgsz);

    int clone_pid = clone(start_routine, (void*)&arg, stack);
    return clone_pid;
}

int thread_join()
{
     void *join_stack;
     int join_pid = join(&join_stack);
     return join_pid;
}
