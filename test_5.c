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
    return 0;
}

void reverse_xor_queue(queue *q){
    xor_node *tmp;
    tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
    return;
}

void connect_two_list(queue *a, queue *b){ //b connect to a
    (a->head)->link = xor((a->head)->link, b->head);
    (b->head)->link = xor(a->head, (b->head)->link);
    a->head = b->tail;
    return;
}

void print_waiting_line(xor_node *tail){
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
    return;
}

void push(int q[], int *q_head, int *q_tail, int group_id, int q_length, int q_appearance[]){
    if(q_appearance[group_id] == 1){
        return;
    }
    else if(*q_head == -1 && *q_tail == -1){
        *q_head += 1;
        *q_tail += 1;
        q[*q_head] = group_id;
        q_appearance[group_id] = 1;
        return;
    }
    else{
        *q_head += 1;
        if(*q_head == q_length){
            *q_head = 0;
        }
        q[*q_head] = group_id;
        q_appearance[group_id] = 1;
        return;
    }
}

void pop_head(int q[], int *q_head, int*q_tail, int q_length, int q_appearance[]){ //leave
    q_appearance[q[*q_head]] = 0;
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
    return;
}

void pop_tail(int q[], int *q_head, int *q_tail, int q_length, int q_appearance[]){ //go
    q_appearance[q[*q_tail]] = 0;
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
    return;
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
    return;
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
    return;
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
    return;
}

void close(int *moving_spot, int m, int k, queue **toilet_group_queue, int toilet_id, int closed_toilet[m]){
    *moving_spot = toilet_id;
    int x = 0;
    do{
        *moving_spot -= 1;
        if(*moving_spot == -1){
            *moving_spot = m - 1;
        }
        x++;
    }while(closed_toilet[*moving_spot] == 1 && x != m-1);
    for(int i = 0; i < k; i++){
        if(toilet_group_queue[toilet_id][i].head == NULL && toilet_group_queue[toilet_id][i].tail == NULL){
            continue;
        }
        else if(toilet_group_queue[*moving_spot][i].head !=NULL && toilet_group_queue[*moving_spot][i].tail != NULL){
            connect_two_list(&toilet_group_queue[*moving_spot][i], &toilet_group_queue[toilet_id][i]);
        }
        else{
            reverse_xor_queue(&toilet_group_queue[toilet_id][i]);
            toilet_group_queue[*moving_spot][i] = toilet_group_queue[toilet_id][i];
        }
    }
    return;
}

int main(){
    int m = 0;
    int n = 0;
    int k = 0;
    scanf("%d%d%d", &m, &n, &k);
    
    queue **toilet_group_queue = malloc(sizeof(queue*)*m);
    int **group_priority = malloc(sizeof(int*)*m);
    int **group_appearance = malloc(sizeof(int*)*m);
    for(int i = 0; i < m; i++){
        toilet_group_queue[i] = malloc(sizeof(queue)*k);
        group_priority[i] = malloc(sizeof(int)*k);
        group_appearance[i] = malloc(sizeof(int)*k);
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < k; j++){
            toilet_group_queue[i][j].head = NULL;
            toilet_group_queue[i][j].tail = NULL;
        }
    }
    int closed_toilet[m];
    int group_priority_head[m];
    int group_priority_tail[m];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < k; j++){
            group_priority[i][j] = -1;
            group_appearance[i][j] = 0;
        }
        group_priority_head[i] = -1;
        group_priority_tail[i] = -1;
        closed_toilet[i] = 0;
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
            push(group_priority[toilet_id], &group_priority_head[toilet_id], &group_priority_tail[toilet_id], group_id, k, group_appearance[toilet_id]);
        }
        else if(strcmp(situation, b) == 0){
            scanf("%d", &toilet_id);     
            leave(&toilet_group_queue[toilet_id][group_priority[toilet_id][group_priority_head[toilet_id]]]);
            if(toilet_group_queue[toilet_id][group_priority[toilet_id][group_priority_head[toilet_id]]].head == NULL){
                pop_head(group_priority[toilet_id], &group_priority_head[toilet_id], &group_priority_tail[toilet_id], k, group_appearance[toilet_id]);
            }
        }
        else if(strcmp(situation, c) == 0){
            scanf("%d", &toilet_id);
            go(&toilet_group_queue[toilet_id][group_priority[toilet_id][group_priority_tail[toilet_id]]]); 
            if(toilet_group_queue[toilet_id][group_priority[toilet_id][group_priority_tail[toilet_id]]].tail == NULL){
                pop_tail(group_priority[toilet_id], &group_priority_head[toilet_id], &group_priority_tail[toilet_id], k, group_appearance[toilet_id]);
            }
        }
        else if(strcmp(situation, d) == 0){
            scanf("%d", &toilet_id);
            if(group_priority_head[toilet_id] == -1 && group_priority_tail[toilet_id] == -1){
                closed_toilet[toilet_id] = 1;
            }
            else{
                int moving_spot = 0;
                close(&moving_spot, m, k, toilet_group_queue, toilet_id, closed_toilet);
                if(group_priority_head[toilet_id] >= group_priority_tail[toilet_id]){
                    for(int i = group_priority_head[toilet_id]; i >= group_priority_tail[toilet_id]; i--){
                        push(group_priority[moving_spot], &group_priority_head[moving_spot], &group_priority_tail[moving_spot], group_priority[toilet_id][i], k, group_appearance[moving_spot]);
                    }
                }
                else{
                    for(int i = group_priority_head[toilet_id]; i >= 0; i--){
                        push(group_priority[moving_spot], &group_priority_head[moving_spot], &group_priority_tail[moving_spot], group_priority[toilet_id][i], k, group_appearance[moving_spot]);
                    }
                    for(int i = k - 1; i >= group_priority_tail[toilet_id]; i--){
                        push(group_priority[moving_spot], &group_priority_head[moving_spot], &group_priority_tail[moving_spot], group_priority[toilet_id][i], k, group_appearance[moving_spot]);
                    }
                }
                closed_toilet[toilet_id] = 1;
            }
        }
    }

    for(int i = 0; i < m; i++){
        if(group_priority_head[i] == -1 && group_priority_tail[i] == -1 || closed_toilet[i] == 1){
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