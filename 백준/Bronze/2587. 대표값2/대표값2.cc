#include<stdio.h>

int main(void){
int arr[5];
int i,j;
int avg,sum=0;
int tmp;
for(i=0;i<5;i++){
    scanf("%d",&arr[i]);
    sum+=arr[i];
}
avg = sum /5;

for(i=0;i<4;i++){
    for(j=0;j<4-i;j++){
        if(arr[j]>arr[j+1]){
            tmp = arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=tmp;
        }
    }
}
    printf("%d\n",avg);
    printf("%d",arr[2]);
    
return 0;
}