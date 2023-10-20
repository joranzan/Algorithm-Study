#include<iostream>

using namespace std;

int main(){
    
    
    
    int N,K;
    cin>>N>>K;
    int cnt = 0;
    bool found = false;
    for(int i=1;i<=N;i++){
        if(N%i==0) {
             cnt++;   
        }
        else{
            continue;
        }
        if(cnt==K){
            found = true;
            cout<<i<<"\n";
            break;
        }
}
    if(!found) cout<<"0\n";
    
    return 0;
}