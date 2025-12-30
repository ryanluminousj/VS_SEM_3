#include<stdio.h>

void binary(int);
int main(){
    int n;
    printf("Enter a number:");
    scanf("%d",&n);
    printf("\n The hex equivalent is %x", n);
    printf("\n The binary equivalent is ");
    binary(n);
    printf("\n The 1's complement is ");
    binary(-n-1);
    printf("\n The 2's complement is ");
    binary(-n);
    return 0;
}

void binary(int a){
    int i, k;
    for(i=3;i>=0;i--){
        k=(a>>i);
        printf("%d",k);
    }
}