#include<iostream>
#include<algorithm>
#include<set>
using namespace std;

int arr[500000] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	
	cin >> N;


	for (int i = 0; i < N; i++) {     //500000
		cin >> arr[i];
	}

	sort(arr, arr + N);

	int M;
	cin >> M;

	for (int i = 0; i < M; i++) {    //500000 
		int num;
		cin >> num;
		//20
		if (binary_search(arr, arr+N, num)) cout << "1 ";
		else cout << "0 ";
	}


	return 0;
}