#include<stdio.h>

int finding_miss_num(int a[], int n){
    int i = 0;
    while(i < n){
        if(a[i] <= n && a[i] != a[a[i]-1]){
            int temp = a[a[i]-1];
            a[a[i]-1] = a[i];
            a[i] = temp;
        }
        else{
            i++;
        }
    }
    for(int i = 0; i < n; i++){
        if(a[i] != i + 1){
            return (i+1);
        }
    }
    return (n + 1);
}

int main(){
    int a[8] = {2,5,8,3,4,7,1,6};
    printf("%d", finding_miss_num(a, 8));

    return 0;
}