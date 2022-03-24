#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct xor_node{
    int data;
    struct xor_node *link;
}xor_node;

typedef struct queue{
    xor_node *head;
    xor_node *tail;
}queue;

xor_node* xor(xor_node* a, xor_node* b){
    return (xor_node*)((unsigned long)(a) ^ (unsigned long)(b));
}

int is_queue_emty(queue q){
    if(q.head == NULL && q.tail == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void enter(queue *toilet_group_queue, int student_id){
    xor_node *new_node = malloc(sizeof(xor_node));
    new_node->data = student_id;

    if(is_queue_emty(*toilet_group_queue)){
        new_node->link = NULL;
        toilet_group_queue->tail = new_node;
    }
    else{
        (toilet_group_queue->head)->link = xor((toilet_group_queue->head)->link, new_node);
        new_node->link = toilet_group_queue->head;
    }

    toilet_group_queue->head = new_node;
}

void leave(queue *toilet_group_queue){
    xor_node *tmp = (toilet_group_queue->head)->link;
    if(tmp){
        tmp->link = xor((toilet_group_queue->head), tmp->link);
    }
    free(toilet_group_queue->head);
    toilet_group_queue->head = tmp;
    if(toilet_group_queue->head == NULL){
        toilet_group_queue->tail = NULL;
    }
}

void go(queue *toilet_group_queue){
    xor_node *tmp = (toilet_group_queue->tail)->link;
    if(tmp){
        tmp->link = xor(tmp->link, (toilet_group_queue->tail));
    }
    free(toilet_group_queue->tail);
    toilet_group_queue->tail = tmp;
    if(toilet_group_queue->tail == NULL){
        toilet_group_queue->head = NULL;
    }
}

void close(){

}

void print_waiting_line(xor_node *tail){
    if(!tail){
        return;
    }
    xor_node *prev = NULL;
    while(tail){
        xor_node *tmp = tail;
        printf("%d", tail->data);
        tail = xor(tail->link, prev);
        prev = tmp;
        if(tail){
            printf(" ");
        }
    }

}

void push(int q[], int *q_head, int *q_tail, int group_id, int q_length){
    if(*q_head == -1 && *q_tail == -1){
        *q_head += 1;
        *q_tail += 1;
        q[*q_head] = group_id;
        return;
    }

    if(*q_head >= *q_tail){
        for(int i = *q_tail; i <= *q_head; i++){
            if(q[i] == group_id){
                return;
            }
        }
        *q_head += 1;
        if(*q_head == q_length){
            *q_head = 0;
        }
        q[*q_head] = group_id;
    }
    else if(*q_head < *q_tail){
        for(int i = *q_tail; i <= q_length-1; i++){
            if(q[i] == group_id){
                return;
            }
        }
        for(int i = 0; i <= *q_head; i++){
            if(q[i] == group_id){
                return;
            }
        }
        *q_head  += 1;
        q[*q_head] = group_id;
    }
}

void pop_head(int q[], int *q_head, int*q_tail, int q_length){ //leave
    if(*q_head == *q_tail){
        q[*q_head] = -1;
        *q_head = -1;
        *q_tail = -1;
        return;
    }
    q[*q_head] = -1;
    *q_head -= 1;
    if(*q_head == -1){
        *q_head = q_length-1;
    }
}

void pop_tail(int q[], int *q_head, int *q_tail, int q_length){ //go
    if(*q_head == *q_tail){
        q[*q_head] = -1;
        *q_head = -1;
        *q_tail = -1;
        return;
    }
    q[*q_tail] = -1;
    *q_tail += 1;
    if(*q_tail == q_length){
        *q_tail = 0;
    }
}

int main(){
    int m = 0;
    int n = 0;
    int k = 0;
    scanf("%d%d%d", &m, &n, &k);

    queue toilet_group_queue[m][k];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < k; j++){
            toilet_group_queue[i][j].head = NULL;
            toilet_group_queue[i][j].tail = NULL;
        }
    }

    int group_priority[m][k];
    int group_priority_head[m];
    int group_priority_tail[m];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < k; j++){
            group_priority[i][j] = -1;
        }
        group_priority_head[i] = -1;
        group_priority_tail[i] = -1;
    }
    
    char situation[10];
    char a[] = "enter";
    char b[] = "leave";
    char c[] = "go";
    char d[] = "close";

    int group_id = 0;
    int student_id = 0;
    int toilet_id = 0;

    for(int i = 0; i < n; i++){
        scanf("%s", situation);
        if(strcmp(situation, a) == 0){
            scanf("%d%d%d", &group_id, &student_id, &toilet_id);
            enter(&toilet_group_queue[toilet_id][group_id], student_id);
            push(group_priority[toilet_id], &group_priority_head[toilet_id], &group_priority_tail[toilet_id], group_id, k);
        }
        else if(strcmp(situation, b) == 0){
            scanf("%d", &toilet_id);     
            leave(&toilet_group_queue[toilet_id][group_priority[toilet_id][group_priority_head[toilet_id]]]);
            if(toilet_group_queue[toilet_id][group_priority[toilet_id][group_priority_head[toilet_id]]].head == NULL){
                pop_head(group_priority[toilet_id], &group_priority_head[toilet_id], &group_priority_tail[toilet_id], k);
            }
        }
        else if(strcmp(situation, c) == 0){
            scanf("%d", &toilet_id);
            go(&toilet_group_queue[toilet_id][group_priority[toilet_id][group_priority_tail[toilet_id]]]); 
            if(toilet_group_queue[toilet_id][group_priority[toilet_id][group_priority_tail[toilet_id]]].tail == NULL){
                pop_tail(group_priority[toilet_id], &group_priority_head[toilet_id], &group_priority_tail[toilet_id], k);
            }
        }
    }
    for(int i = 0; i < m; i++){
        if(group_priority_head[i] == -1 && group_priority_tail[i] == -1){
            printf("\n");
            continue;
        }
        if(group_priority_head[i] >= group_priority_tail[i]){
            for(int j = group_priority_tail[i]; j <= group_priority_head[i]; j++){
                print_waiting_line(toilet_group_queue[i][group_priority[i][j]].tail);
                if(j != group_priority_head[i]){
                    printf(" ");
                }
            }
        }
        else{
            for(int j = group_priority_tail[i]; j < k; j++){
                print_waiting_line(toilet_group_queue[i][group_priority[i][j]].tail);
                printf(" ");
            }
            for(int j = 0; j <= group_priority_head[i]; j++){
                print_waiting_line(toilet_group_queue[i][group_priority[i][j]].tail);
                if(j != group_priority_head[i]){
                    printf(" ");
                }
            }
        }
        printf("\n");
    }


    return 0;
}