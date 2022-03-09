#include<stdio.h>
#include<string.h>

#define stack_len 10000
#define array_len 10000

void push(long long int stack[],long long int data, int *stack_top){
    *stack_top += 1;
    stack[*stack_top] = data; 
}

int pop(long long int stack[], int *stack_top){
    int data = stack[*stack_top];
    stack[*stack_top] = 0;
    *stack_top -= 1;
    return data;
}

int is_operator(char symbol){
    if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%'){
        return 1;
    }
    else{
        return 0;
    }
}

int prime_num(char symbol){
    if(symbol == '*' || symbol == '/' || symbol == '%'){
        return 2;
    }
    else if(symbol == '+' || symbol == '-'){
        return 1;
    }
}

void caculate_stack(long long int stack[],long long int operater_sign[], int *stack_top, long long int stack_ans[], int *stack_ans_top){
    int a = 0;
    int b = 0;
    int c = 0;
    for(int i = 0; i <= *stack_top; i++){
        if(operater_sign[i] == 0){
            push(stack_ans, stack[i], stack_ans_top);
        }
        else if(operater_sign[i] == 1){
            if(stack[i] == '+'){
                a = pop(stack_ans, stack_ans_top);
                b = pop(stack_ans, stack_ans_top);
                c = b + a;
                push(stack_ans, c, stack_ans_top);
            }
            else if(stack[i] == '-'){
                a = pop(stack_ans, stack_ans_top);
                b = pop(stack_ans, stack_ans_top);
                c = b - a;
                push(stack_ans, c, stack_ans_top);
            }
            else if(stack[i] == '*'){
                a = pop(stack_ans, stack_ans_top);
                b = pop(stack_ans, stack_ans_top);
                c = b * a;
                push(stack_ans, c, stack_ans_top);
            }
            else if(stack[i] == '/'){
                a = pop(stack_ans, stack_ans_top);
                b = pop(stack_ans, stack_ans_top);
                c = b / a;
                push(stack_ans, c, stack_ans_top);
            }
            else if(stack[i] == '%'){
                a = pop(stack_ans, stack_ans_top);
                b = pop(stack_ans, stack_ans_top);
                c = b % a;
                push(stack_ans, c, stack_ans_top);
            }
        }
    }

}

int main(){
    long long int stack_1[stack_len] = {0};
    int stack_1_top = -1;
    long long int stack_2[2][stack_len] = {{0}};
    int stack_2_top = -1;
    long long int stack_ans[stack_len] = {0};
    int stack_ans_top = -1;
    char string[array_len];
    scanf("%s", &string);

    int index = 0;
    long long int num = 0;
    for(int i = 0; i < strlen(string); i++){
        if(string[i] - '0' > 0 && string[i] - '0' <= 9){
            num = num * 10 + (string[i] - '0');
            index = 1;
        }
        else if(is_operator(string[i])){
            if(index == 1){
                push(stack_2[0], num, &stack_2_top);
                num = 0;
                index = 0;
            }
            while(1){
                if(stack_1_top == -1 || stack_1[stack_1_top] == '('){
                    push(stack_1, string[i], &stack_1_top);
                    break;
                }
                else if(prime_num(string[i]) > prime_num(stack_1[stack_1_top])){
                    push(stack_1, string[i], &stack_1_top);
                    break;
                }else if(prime_num(string[i]) <= prime_num(stack_1[stack_1_top])){
                    int data = pop(stack_1, &stack_1_top);
                    push(stack_2[0], data, &stack_2_top);
                    stack_2[1][stack_2_top] = 1;
                }
            }
        }
        else if(string[i] == '('){
            if(index == 1){
                push(stack_2[0], num, &stack_2_top);
                num = 0;
                index = 0;
            }
            push(stack_1, string[i], &stack_1_top);
        }
        else if(string[i] == ')'){
            if(index == 1){
                push(stack_2[0], num, &stack_2_top);
                num = 0;
                index = 0;
            }
            while(stack_1[stack_1_top] != '('){
                int data = pop(stack_1, &stack_1_top);
                push(stack_2[0], data, &stack_2_top);
                stack_2[1][stack_2_top] = 1;
            }
            int data = pop(stack_1, &stack_1_top); //pop '('
        }
        else if(string[i] == '='){
            if(index == 1){
                push(stack_2[0], num, &stack_2_top);
                num = 0;
                index = 0;
            }
            while(stack_1_top != -1){
                int data = pop(stack_1, &stack_1_top);
                push(stack_2[0], data, &stack_2_top);
                stack_2[1][stack_2_top] = 1;
            }
            caculate_stack(stack_2[0], stack_2[1], &stack_2_top, stack_ans, &stack_ans_top);
            printf("Print: %lld\n", stack_ans[0]);
            num = stack_ans[0];
            stack_2_top = -1;
            stack_1_top = -1;
            index = 1;
        }
    }

    return 0;
}