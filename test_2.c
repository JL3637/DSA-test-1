#include<stdio.h>

int main(){
    int a;
    char y;
    int b[10000];
    int c[10000];
    int i = 0;
    while(scanf("%d", &a) != EOF){
        b[i] = a;
        i++;
    }
    for(int i = 0; i < i; i++){
        printf("%d\n", b[i]);
    }
}