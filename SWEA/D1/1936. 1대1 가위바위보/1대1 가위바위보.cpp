/////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>

using namespace std;

int main()
{
    int A,B;
    cin>>A>>B;
    
    if(A==1)
    {
        if(B==2) cout<<"B";
        else cout<<"A";
    }
    else if(A==2)
    {
         if(B==3) cout<<"B";
        else cout<<"A";
    }
    else //A==3
    {
         if(B==1) cout<<"B";
        else cout<<"A";
    } 
        
    
    
    return 0;
}