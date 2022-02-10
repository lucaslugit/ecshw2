//
// Created by luhao on 2/5/2022.
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct Element {

    void* singledata;
    struct Element* NextElement;
};
struct queue {

    struct Element* head;
    struct Element* end;
    int size;
};

queue_t queue_create(void)
{
    queue_t  Ourqueue = malloc(sizeof(struct queue));
    /* TODO */
    Ourqueue->head=NULL;
    Ourqueue->end=NULL;
    Ourqueue->size=0;
     //if(Ourqueue->size!=0){
     //return -1;
    //}
    return Ourqueue;


}

int queue_destroy(queue_t queue)
{
    /* TODO */
    if (queue == NULL ){
        return -1;
    }
    free(queue);
    return 0;

}

int queue_enqueue(queue_t queue, void *data)
{
    /* TODO */
    if(queue->head==NULL){
        struct Element* newelement = malloc(sizeof(struct Element));
        newelement->singledata=data;
        newelement->NextElement=NULL;
        queue->head=newelement;
        queue->end=newelement;
        queue->size=1;
    }
    else{
        struct Element* newelement = malloc(sizeof(struct Element));
        newelement->singledata=data;
        newelement->NextElement=NULL;
        queue->end->NextElement=newelement;
        queue->end=newelement;
        queue->size+=1;
    }
    if(queue->head==NULL || data==NULL){
        return -1;
    }
    return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
    /* TODO */
    if(queue==NULL&&queue->head==NULL){
        return -1;
    }
    //struct Element* temelement = malloc(sizeof(struct Element));
    *data=queue->head->singledata;
    queue->head=queue->head->NextElement;
    queue->size-=1;

    return 0;


}

int queue_delete(queue_t queue, void *data)
{
    /* TODO */
    if(queue==NULL){
        return -1;
    }
    struct Element*temelement=queue->head;
    int loopsnum=0;
    struct Element*lastlement;
    while(temelement->singledata!=NULL){

        if(temelement->singledata==data){
            if(loopsnum==0){
                temelement=temelement->NextElement;
                queue->head=temelement;
                queue->size-=1;
                break;
            }
            else{
                lastlement->NextElement=temelement->NextElement;
                //queue->head=temelement;
                queue->size-=1;
                break;
            }

        }
        lastlement=temelement;
        loopsnum++;
        temelement=temelement->NextElement;
        if(temelement==NULL){
            break;
        }

    }
    if(loopsnum==sizeof(queue)){
        return -1;
    }
    else {
        return 0;
    }


}

int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
    if(queue==NULL || func==NULL){
        return -1;
    }
    struct Element* tem=queue->head;
    while(tem!=NULL){

        if(func(queue,tem->singledata,arg)==1){
            if(data!=NULL) {
                *data = tem->singledata;
                break;
            }
        }

        tem=tem->NextElement;
        if(tem==NULL){
            break;
        }
    }
    return 0;
}

void printq(queue_t queue){
    struct Element* tem=queue->head;
    while(tem->singledata!=NULL){
        /*
        if(func(queue,tem->singledata,arg)==1){
            break;
        }
         */
        char *data=tem->singledata;
        printf("it is %d",*data);
        tem=tem->NextElement;
        if(tem==NULL){
            break;
        }
    }

}

int queue_length(queue_t queue)
{
    /* TODO */
    return queue->size;
}
void q(){
    printf("fasfsafsafasf!\n");

}

