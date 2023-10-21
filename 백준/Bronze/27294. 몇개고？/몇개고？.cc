#include<iostream>

using namespace std;

int main(){

    //시간 : 0 ~ 23  11이하 : 아침 12~16이하 점심 나머지 저녁
    //술 : 먹으면 1 안먹으면 0
    
    int T, S;
    cin>>T>>S;
    
    if(S==1){
        cout<<"280\n";
    }
    else{
        if(T>=12&&T<=16) cout<<"320\n";
        else cout<<"280\n";
    }
    
    
    return 0;
}