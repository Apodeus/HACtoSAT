#include "queue.h"

queue newQueue(int v){
    queue q = (queue) malloc(sizeof(struct t_queue));
    q->next = NULL;
    q->value = v;

    return q;
}

queue addToQueue(queue q, int value){
    queue l = q;
    if (l == NULL){
        *q = *(newQueue(value));
        return NULL;
    }
    if (l->value == value)
        return NULL;

    while (l->next != NULL){
        l = l->next;
        if (l->value == value)
            return NULL;
    }

    l->next = newQueue(value);

    return q;
}

queue nextInQueue(queue q){
    queue result = q->next;
    free(q);
    return result;
}
