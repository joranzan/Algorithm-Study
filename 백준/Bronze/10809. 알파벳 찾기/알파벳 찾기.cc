#include<iostream>
#include<cstring>
#include<string>

using namespace std;

int main(){
    
    string s;
    cin>>s;
    
    for(char c='a';c<='z';c++){
        int index = -1;
        for(int i=0;i<s.length();i++){
            if(s[i]==c){
                index = i;
                break;
            }
            
        }
        cout<<index<<" ";
    }
    
    return 0;
}