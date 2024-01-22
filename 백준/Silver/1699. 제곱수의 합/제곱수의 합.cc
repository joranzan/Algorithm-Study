#include<iostream>
#include<cmath>

int DP[100001] = { 0, };

using namespace std;

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	int maxN = int(sqrt(N));
	
	//Greedy로 풀면 안됨...
	/*
	int cnt = 0;

	for (int i = maxN; i >= 1; i--) {
		int square = i * i;
		while (N >= square) {
			cnt++;
			N -= square;
		}
	}

	cout << cnt;
	*/

	for (int i = 1; i <= N; i++) DP[i] = i;

	for (int i = maxN; i >= 2; i--) {
		int square = i * i;
		for (int j = 0; j < N; j++) {
			if (j + square > N) break;
			DP[j + square] = min(DP[j + square], DP[j] + 1);
		}
	}

	cout << DP[N];


	return 0;
}