#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "sysfunc.h"


int sys_clone(void) {

    return 0;
}

int sys_join(void) {

    return 0;
}


int clone(void(*fcn)(void*), void *arg, void *stack) {

    return 0;
}

int join(void **stack) {
    return 0;
}
