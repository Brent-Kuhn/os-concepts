#ifndef _THREAD_H
#define _THREAD_H_

int thread_create(void (*start_routine)(void*), void *arg);
int thread_join();

typedef struct __lock_t { int flag; } lock_t;

void lock_acquire(lock_t*);
void lock_release(lock_t*);
void lock_init(lock_t*);

#endif // _THREAD_H