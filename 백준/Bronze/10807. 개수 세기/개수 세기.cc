#include<iostream>

using namespace std;

int main(){
    
    int N;
    cin>>N;
    int arr[101];
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
    int v;
    cin>>v;
    int cnt=0;
    for(int i=0;i<N;i++){
        if(arr[i]==v) cnt++;
    }
    
    cout<<cnt;
    
    return 0;
}