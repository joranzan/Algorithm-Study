#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    
    int a,b,c;
    cin>>a>>b>>c;
    int money = 0;
    if(a==b&&b==c){
        money+=(10000+a*1000);
    } 
    else if(a==b||b==c||c==a){
        if(a==b) money+=(1000+a*100);
        else if(b==c) money+=(1000+b*100);
        else money+=(1000+c*100);
    }
    else{
        int num = max(a,b);
        num = max(num, c);
        money+=(num*100);
    }
    
    cout<<money;
    
    
    return 0;
}