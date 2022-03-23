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

void is_empty(queue a){

}

void enter(xor_node **head, int student_id){
    xor_node *new_node = malloc(sizeof(xor_node));
    new_node->data = student_id;

    if(*head == NULL){
        new_node->link = NULL;
    }
    else{
        (*head)->link = xor((*head)->link, new_node);
        new_node->link = *head;
    }

    *head = new_node;
}

void leave(xor_node **head){
    if(!(*head)){
        return;
    }
    xor_node *tmp = (*head)->link;
    if(tmp){
        tmp->link = xor((*head), tmp->link);
    }
    free(*head);
    *head = tmp;
}

void go(xor_node **head){
    if (*head == NULL)
        return;
    else {
        xor_node *curr = *head;
        xor_node *prev = NULL;
        xor_node *next;

        while (xor(curr->link, prev) != NULL) {
            next = xor(prev, curr->link);
            prev = curr;
            curr = next;
        }
        if (prev != NULL){
            prev->link = xor(xor(prev->link, curr), NULL);
        }
        else{
            *head = NULL;
        }
        free(curr);
    }
}

void close(){

}

void print_waiting_line(xor_node *head){
    if(!head){
        return;
    }
    xor_node *prev = NULL;
    while(head) {
        xor_node *tmp = head;
        printf("%d ", head->data);
        head = xor(prev, head->link);
        prev = tmp;
    }
    printf("\n");
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
    for(int i = 0; i < m; i++){
        for(int j = 0; j < k; j++){
            group_priority[i][j] = -1;
        }
        group_priority_head[i] = 0;
    }
    

    char situation[10];
    char a[] = "enter";
    char b[] = "leave";
    char c[] = "go";
    char d[] = "close";
    for(int i = 0; i < n; i++){
        scanf("%s", situation);
        if(strcmp(situation, a) == 0){
            int group_id = 0;
            int student_id = 0;
            int toilet_id = 0;
            scanf("%d%d%d", &group_id, &student_id, &toilet_id);
            enter(&toilet_group_queue[toilet_id][group_id].head, student_id);
        }
        else if(strcmp(situation, b) == 0){
            int toilet_id = 0;
            scanf("%d", &toilet_id);
            leave(&toilet_group_queue[toilet_id][0].head);
        }
        else if(strcmp(situation, c) == 0){
            int toilet_id = 0;
            scanf("%d", &toilet_id);
            go(&toilet_group_queue[toilet_id][0].head);
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < k; j++){
            print_waiting_line(toilet_group_queue[i][j].head);
        }
    }


    return 0;
}