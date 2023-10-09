#include<iostream>
using namespace std;

int main(){
    
    int hour, min;
    cin>>hour >>min;
    int time;
    cin>>time;
    min += time;
    int add_hour = min/60;
    min = min % 60;
    hour += add_hour;
    
    hour = hour%24;
    cout<< hour << " " <<min;
    return 0;
}