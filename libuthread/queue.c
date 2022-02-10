#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "queue.h"


typedef struct node_ptr {
	void *address;
	struct node_ptr* next;
}node_ptr;
typedef struct node_ptr* node;

typedef struct queue {
	/* TODO */
	node front;
	node rear;
	int queue_length;
}queue;

node new_node(void *data){
	node new;
	new = (node)malloc(sizeof(node_ptr));
	new->address = data;
	new->next = NULL;
	return new;
}

queue_t queue_create(void)
{
	queue_t queue_q;
	queue_q = (queue_t)malloc(sizeof(queue));
	queue_q->front = NULL;
	queue_q->rear = NULL;
	queue_q->queue_length = 0;
	return queue_q;
	/* TODO */
	return NULL;
}

int queue_destroy(queue_t queue)
{
	/* TODO */
	if(queue->front!=NULL){
		return -1;
	}
	else{
		free(queue);
		return 0;
	}
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO */
	if(!data){
		return -1;
	}

	node n = new_node(data);

	queue->queue_length = queue->queue_length + 1;
	if(queue->front==NULL){
		queue->front = n;
		queue->rear = n;
	}
	else{
		queue->rear->next = n;
		queue->rear = n;
	}

	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO */
	if(!data){
		return -1;
	}
	if(queue->front==NULL){
		return -1;
	}

	node node_old = queue->front;
	*data = queue->front->address;
	if(queue->front->next!=NULL){
		queue->front = queue->front->next;
	}
	else{
		queue->front = NULL;
		queue->rear = NULL;
	}
	free(node_old);
	queue->queue_length = queue->queue_length -1;

	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO */
	if(!data||queue->front==NULL){
		return -1;
	}

	node find_data = queue->front;
	if(queue->front->address == data){
		queue->front = queue->front->next;
		free(find_data);
		queue->queue_length--;
		return 0;
	}

	while(find_data->next!=NULL){
		if(find_data->next->address == data){
			node find_it = find_data->next;
			if(find_data->next!=queue->rear){
				find_data->next = find_data->next->next;
			}
			else{
				queue->rear = find_data;
				find_data->next = NULL;
			}
			free(find_it);
			queue->queue_length--;
			return 0;
		}
		find_data = find_data->next;
	}
	return -1;
}

int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
	/* TODO */
	if(queue->front==NULL||func==NULL){
		return -1;
	}

	int return_value;
	node current_data = queue->front;

	while(current_data->next!=NULL){
		return_value = func(queue,current_data->address,arg);
		if(return_value==1){
			if(data!=NULL){
				*data = current_data->address;
				break;
			}
		}
		current_data = current_data->next;
	}
	
	return_value = func(queue,current_data->address,arg);
	if(return_value==1){
		if(data!=NULL){
			*data = current_data->address;
		}
		return 0;
	}

	return 0;
}

int queue_length(queue_t queue)
{
	/* TODO */
	if(queue->front==NULL){
		return -1;
	}
	else{
		return queue->queue_length;
	}
}

int queue_print(queue_t queue){
	node start = queue->front;
	while(start!=NULL){
		printf("print: %d\n",*(int*)start->address);
		start = start->next;
	}
	return 0;
}

