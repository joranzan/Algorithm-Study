#include<iostream>
#include<cmath>

using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int N;
    cin>>N;
    
    
    int cnt = 0;
    for(int i=0;i<N;i++){
        int num;
        cin>>num;
        if(num==1) continue;
        bool prime = true;
        for(int j=2;j<=sqrt(num);j++){
            if(num%j==0){
                prime = false;
                break;
            }
        }
        if(prime) cnt++;
    }
    
    cout<<cnt;
    
    return 0;
}
