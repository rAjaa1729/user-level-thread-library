#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

struct list* thread_list;
struct listentry* curr;
ucontext_t mainctx;

void mythread_init()      // Initialize threads list
{
	thread_list=list_new();
	curr=NULL;
}
ucontext_t* mythread_create(void func(void*), void* arg) // Create a new thread
{
	char st1[8192];
	ucontext_t* new_thread=(ucontext_t*)malloc(sizeof(ucontext_t));
	getcontext(new_thread);
	new_thread.uc_stack.ss_sp = st1;
    new_thread.uc_stack.ss_size =8192;
	new_thread.uc_link = &mainctx;
	makecontext(new_thread,func,0,arg);
	list_add(thread_list,(void*)new_thread);

	return new_thread;
}
void mythread_join()  // Waits for other thread to complete. It is used in case of dependent threads.
{
	struct listentry* head=thread_list->head;
	while(head!=NULL)
	{
		swapcontext(&mainctx,(ucontext_t*)head->data);
		head=head->next;
	}
}
void mythread_yield()  // Perform context switching here
{
	if(curr==NULL)
	{
		curr=thread_list->head;
	}
	else
	{
		curr=curr->next;
	}
	swapcontext(&mainctx,(ucontext_t*)curr->data);
}

struct lock 
{
	ucontext_t* ctx;
};
struct lock* lock_new()  // return an initialized lock object
{
	struct lock* new_lock=(lock*)(malloc)(sizeof(lock));
	new_lock->ctx=NULL;
	return new_lock;
}
void lock_acquire(struct lock* lk)   // Set lock. Yield if lock is acquired by some other thread.
{
	

}
int lock_release(struct lock* lk)   // Release lock
{
	
}

#endif
