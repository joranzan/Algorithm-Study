#include<iostream>

#include<algorithm>


using namespace std;


pair<int,int> arr[1000001];

pair<int,int> cnt[1000001];


int main(){

 

ios::sync_with_stdio(false); 

cin.tie(NULL); cout.tie(NULL);


int N;

cin>>N;


//1000 999 1000 999 1000 999

for(int i=0;i<N;i++){

cin>>arr[i].first;

arr[i].second = i;

}


sort(arr,arr+N);


cnt[0].first = arr[0].second;

cnt[0].second = 0;


for(int i=1;i<N;i++){

cnt[i].first = arr[i].second;

if(arr[i-1].first==arr[i].first) {

cnt[i].second = cnt[i-1].second;

}

else{

cnt[i].second = cnt[i-1].second + 1;

}

}


sort(cnt,cnt+N);


for(int i=0;i<N;i++){

cout<<cnt[i].second<<"\n";

}



return 0;
}