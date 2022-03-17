#include<stdio.h>

typedef struct q_node{
    int group;
    int id;
    struct q_node* LR_ptr;
}q_node;


int situation_case(char situation[]){
    char a[]="enter";
    char b[]="leave";
    char c[]="go";
    char d[]="close";
    if(strcmp(situation, a) == 0){
        return 1;
    }
    else if(strcmp(situation, b) == 0){
        return 2;
    }
    else if(strcmp(situation, c) == 0){
        return 3;
    }
    else if(strcmp(situation, d) == 0){
        return 4;
    }
    else{
        return 0;
    }
}

void is_empty(){

}

void enqueue(){

}

void dequeue(){

}

void enter(){

}

void leave(){

}

void go(){

}

void close(){

}


int main(){
    int m = 0;
    int n = 0;
    int k = 0;
    scanf("%d%d%d", &m, &n, &k);
    char situation[10];

    /*for(int i = 0; i < n; i++){
        scanf("%s", situation);
    }*/





    return 0;
}