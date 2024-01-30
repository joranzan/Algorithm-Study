#include<iostream>
#include<unordered_map>
using namespace std;

unordered_map<string, int> um;
string s[100001];


int main(){
    
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int N, M;
    cin>>N>>M;
    
    for(int i=1;i<=N;i++){
        cin>>s[i];
        um.insert({s[i],i});
    }
    
    for(int i=1;i<=M;i++){
        string temp;
        cin>>temp;
        if(temp[0]>='A') cout<<um[temp]<<"\n";
        else cout<<s[stoi(temp)]<<"\n";
    }
    
    
    return 0;
}