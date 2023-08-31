#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    int N;
    cin>>N;
    vector<int> Num(N);
    for(int i=0;i<N;i++)
    {
        cin>>Num[i];
    }
    
    sort(Num.begin(), Num.end());  
    cout<<Num[N/2];
    

    return 0;
}
