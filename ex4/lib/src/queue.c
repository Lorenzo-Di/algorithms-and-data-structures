#include "queue.h"
#include <stdlib.h>

typedef struct node {
    void *data;
    struct node *next;
} *Node;

struct queue {
    Node front;
    Node rear;
    int size;
};

Queue queue_create() {
    Queue q = malloc(sizeof(struct queue));
    if(!q) return NULL;
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void queue_free(Queue q) {
    if(!q) { return; }
    Node curr = q->front;
    while(curr) {
        Node temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(q);
}

bool queue_enqueue(Queue q, void *data) {
    if(!q) { return false; }
    
    Node n = malloc(sizeof(struct node));
    if(!n) { return false; }
    
    n->data = data;
    n->next = NULL;
    
    if(!q->front) { q->front = n; }
    else { q->rear->next = n; }
    q->rear = n;
    q->size++;
    return true;
}

bool queue_dequeue(Queue q, void **res) {
    if(!q || !q->front) { return false; }
    
    Node temp = q->front;
    *res = temp->data;
    
    q->front = q->front->next;
    if(!q->front) { q->rear = NULL; }
    
    free(temp);
    q->size--;
    return true;
}

bool queue_is_empty(Queue q) {
    return (!q || q->size == 0);
}

int queue_size(Queue q) {
    if(!q) { return 0; }
    return q->size;
}