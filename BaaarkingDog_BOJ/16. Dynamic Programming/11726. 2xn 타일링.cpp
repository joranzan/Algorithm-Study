#include<iostream>

using namespace std;

//피보나치 수열에서 1000번째 수는 무려 209자리
//그니깐 10007을 뺴주면서 연산하기

int DP[1001] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	DP[1] = 1;

	if (N == 1) {
		cout << DP[1];
		return 0;
	}

	DP[2] = 2;
	if (N == 2) {
		cout << DP[2]; 
		return 0;
	}

	for (int i = 3; i <= N; i++) {
		DP[i] = DP[i - 1] + DP[i - 2];
		if (DP[i] >= 10007) DP[i] -= 10007;
	}

	cout << DP[N];



	return 0;
}