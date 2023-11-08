#include<iostream>
#include<string>

using namespace std;

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int num;
        string s;
        cin>>num>>s;
        for(int j=0;j<s.length();j++){
            for(int k=0;k<num;k++){
                cout<<s[j];
            }
        }
        cout<<"\n";
    }
    
    
    return 0;
}