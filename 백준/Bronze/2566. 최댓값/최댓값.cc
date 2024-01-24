#include<iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int maxValue = -1;
    int maxR = 0;
    int maxC = 0;
    
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            int temp;
            cin>>temp;
            if(temp>maxValue){
                maxValue = temp;
                maxR = i;
                maxC = j;
            }
        }
    }
    
    cout<<maxValue<<"\n"<<maxR<<" "<<maxC;
    
    return 0;
}