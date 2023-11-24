#include<iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int N,M;
    cin>>N>>M;
    
    int arr[101];
    for(int i=1;i<=N;i++){
        arr[i]  = i;
    }
    
    for(int i=1;i<=M;i++){
        int index1, index2;
        cin>>index1>>index2;
        swap(arr[index1], arr[index2]);
    }
    
     for(int i=1;i<=N;i++){
        cout<<arr[i]<<" ";
    }
    
    
    return 0;
}