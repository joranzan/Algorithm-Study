#include<stdio.h>

int main(void){
    
    int arr[1000]={};
    int n;
    int i,j;
    scanf("%d",&n);
    
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    
    
    
    for(i=0;i<n;i++){
        int min=99999;
        int index;
        for(j=i;j<n;j++){
            if(min>arr[j]){
                min=arr[j];
                index = j;                
            }            
        }
        arr[index]=arr[i];
        arr[i]=min;
    }
    for(i=0;i<n;i++){
        printf("%d\n",arr[i]);
    }
    
    return 0;
}