#include<iostream>
#include<cmath>

using namespace std;

int arr[41] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	long long N;
	cin >> N;

	int cnt = 0;
	while (N != 0) {
		arr[cnt] = (N & 1);
		N = N >> 1;
		cnt++;
	}

	long long Answer = 0;
	long long prev = 1;
	for (int i = 0; i < cnt; i++) {
		if (arr[i] == 1) {
			Answer += prev;
		}
		prev *= 3;
	}

	cout << Answer;

	return 0;
}



/*
1 3 4 9 10 12 13 

1
10
11
100


*/