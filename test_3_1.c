#include<stdio.h>

typedef struct node{
    int data;
    struct node* next;
}node;

int middle_point(node *head){
    node *slow = head;
    node *fast = head;
    while(fast != NULL && (*fast).next != NULL){
        slow = (*slow).next;
        fast = (*fast).next;
        fast = (*fast).next;
    }
    return (*slow).data;
}

int main(){
    node a[100];
    node *l_head = &a[0];

    for(int i = 0; i < 99; i++){
        a[i].data = i;
        a[i].next = &a[i+1];
    }
    a[99].next = NULL;
    printf("%d", middle_point(&a[0]));
    return 0;
}