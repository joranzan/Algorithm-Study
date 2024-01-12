#include<iostream>

using namespace std;

int N;
int Cost[1001] = { 0, };
int DP[1001] = { 0, };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> Cost[i];
		DP[i] = Cost[i];
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i + j > N) break;
			DP[i + j] = max(DP[i + j], DP[i] + Cost[j]);
		}
	}

	cout << DP[N];

	return 0;
}

/*
문제 분석

1) 카드 1~N개가 포함된 카드팩

2) 돈을 최대한 많이 지불해서 카드 N개 구매


*/