#include<stdio.h>

int finding_balanced_pivot(int a[],int n){
    int mass_sum = 0;
    int x_sum = 0;
    for(int i = 0; i < n; i++){
        mass_sum += a[i];
        x_sum += a[i] * (i+1);
    }
    int position = 0;
    position = x_sum / mass_sum;
    return position;
}

int main(){
    int a[5] = {9, 5, 2, 2, 1};

    printf("%d", finding_balanced_pivot(a, 5));
    return 0;
}