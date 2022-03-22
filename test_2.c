#include<stdio.h>

void push(int stack[], int data, int *stack_top){
    *stack_top += 1;
    stack[*stack_top] = data; 
}

int pop(int stack[], int *stack_top){
    int data = stack[*stack_top];
    stack[*stack_top] = 0;
    *stack_top -= 1;
    return data;
}

int check_intersects(int couples[], int stack[], int *stack_top, int n){
    push(stack, couples[0], stack_top);
    for(int i = 1; i < 2 * n; i++){
        if(stack[*stack_top] == couples[i]){
            pop(stack, stack_top);
        }
        else{
            push(stack, couples[i], stack_top);
        }
    }
    if(stack[0] == 0){
        return 0;
    }
    else{
        return 1;
    }
}


int main(){
    int n = 0;
    scanf("%d", &n);
    int stack[2 * n];
    int stack_top = -1;
    int couples[2 * n];
    for(int i = 0; i < 2 * n; i++){
        scanf("%d", &couples[i]);
    }
    printf("%d", check_intersects(couples, stack, &stack_top, n));

    return 0;
}