#include <thread.h>

int TestAndSet(int *old_ptr, int new){
	int old = *old_ptr;	// fetch old value at old_ptr
	*old_ptr = new;		// store 'new' into old_ptr
	return old;		// return the old value
}

void lock_acquire(lock_t* lock){
	while (TestAndSet(&lock->flag, 1) == 1)
		; //spin-wait (do nothing)
}

void lock_release(lock_t* lock){
	lock->flag = 0;
}

void lock_init(lock_t* lock){
	// 0 indicates that lock is available, 1 that it is held
	lock->flag = 0;
}
