#ifndef _THREAD_H
#define _THREAD_H_

int thread_create(void (*start_routine)(void*), void *arg);
int thread_join();

#endif // _THREAD_H