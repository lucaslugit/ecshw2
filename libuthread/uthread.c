#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "queue.h"
#include "private.h"
#include "uthread.h"
#define bool int
#define ture 1
#define false 0
#define Max_size 100

/* TODO */

/*elements in uthread*/
typedef struct uthread_tcb {
	uthread_t tid;
	char state[Max_size];
	void *stack;
	uthread_ctx_t* context;
	uthread_func_t func;
}uthread_tcb;
//typedef struct uthread_tcb* uthread_tcb;


uthread_t uthread_tid = 0;
queue_t queue;
uthread_tcb* current_thread;

int uthread_start(int preempt)
{
	/* TODO */
	queue = queue_create();

	if(queue&&preempt==0){
		return 0;
	}
	return -1;
}

int uthread_stop(void)
{
	/* TODO */
	if(queue_destroy(queue)==0){
		return 0;
	}
	return -1;
}

int uthread_create(uthread_func_t func)
{
	/* TODO */
	uthread_tcb* new_thread;
	uthread_ctx_t* new_thread_context;
	new_thread = (uthread_tcb*)malloc(sizeof(uthread_tcb));
	new_thread_context = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));

	if(new_thread==NULL||new_thread_context==NULL){
		return -1;
	}

	new_thread->tid = uthread_tid++;
	strcpy(new_thread->state, "ready");
	new_thread->stack = uthread_ctx_alloc_stack();
	new_thread->func = func;
	
	if(new_thread->stack == NULL){
		return -1;
	}

	uthread_ctx_init(new_thread_context,new_thread->stack,func);
	new_thread->context = new_thread_context;

	queue_enqueue(queue,new_thread);
	if(queue_length(queue)==1){
		current_thread = new_thread;
	}

	return(uthread_tid);
}

void uthread_yield(void)
{
	/* TODO */
	uthread_tcb* next_thread;
	queue_dequeue(queue,(void**)&next_thread);
	uthread_tcb* now_thread;
	
	now_thread = current_thread;//get current thread
	strcpy(now_thread->state, "ready");
	if(next_thread){
		strcpy(next_thread->state, "running");
		uthread_ctx_switch(now_thread->context,next_thread->context);
		current_thread = next_thread;
	}
	queue_enqueue(queue,now_thread);
	//get values of current thread ,dequeue it
	//put it into the end, enqueue it
}


uthread_t uthread_self(void)
{
	/* TODO */
	if(current_thread){
		return current_thread->tid;
	}

	return -1;
}

void uthread_exit(int retval) //exit current thread
{
	/* TODO */
	printf("%d\n",retval);
	if(strncmp(current_thread->state,"running",Max_size)==0){
		uthread_tcb* exit_thread = current_thread;
		strcpy(exit_thread->state, "zombie");
		uthread_tcb* next_thread;

		queue_dequeue(queue,(void**)&next_thread);
		if(next_thread){
			strcpy(next_thread->state, "running");
			uthread_ctx_switch(exit_thread->context,next_thread->context);
			current_thread = next_thread;
		}
	}
}

int uthread_join(uthread_t tid, int *retval)
{
	/* TODO */
	printf("%d\n",tid);
	printf("%d\n",*retval);
	while(current_thread!=NULL){
		uthread_yield();
	}
	return -1;
}

