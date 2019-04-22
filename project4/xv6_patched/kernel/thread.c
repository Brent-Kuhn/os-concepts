#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "sysfunc.h"


int sys_clone(void) {

    int fcn_addr = 0;
    int arg_addr = 0;
    int stack_addr = 0;
    void(*fcn)(void*);
    void *arg;
    void *stack;

    argint(0, &fcn_addr);
    fcn = (void(*)(void*))fcn_addr;

    argint(1, &arg_addr);
    arg = (void*)arg_addr;

    argint(2, &stack_addr);
    stack = (void**)stack_addr;

    return clone(fcn, arg, stack);
}

int sys_join(void) {

    return 0;
}

int join(void **stack) {
    return 0;
}
