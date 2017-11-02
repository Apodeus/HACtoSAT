#include <stdio.h>
#include <stdlib.h>

struct t_queue {
    struct t_queue* next;
    int value;
};

typedef struct t_queue* queue;

queue newQueue(int v);
queue addToQueue(queue q, int value);
queue nextInQueue(queue q);
void destroyQueue(queue q);
