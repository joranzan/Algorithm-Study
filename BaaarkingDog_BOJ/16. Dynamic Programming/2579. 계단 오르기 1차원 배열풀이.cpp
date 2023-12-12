#include<iostream>

using namespace std;

//밟은 계단의 최댓값 구하기
// => 밟지 않은 계단의 최소값 구하기

int N;
int Score[301] = { 0, };
int sum = 0;
int DP[301] = { 0, };

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> Score[i];
		sum += Score[i];
	}

	DP[0] = 0;
	DP[1] = Score[1];
	DP[2] = Score[2];
	DP[3] = Score[3];

	for (int i = 4; i <= N - 1; i++) {
		DP[i] = Score[i] + min(DP[i - 2], DP[i - 3]);
	}

	cout << sum - min(DP[N - 2], DP[N - 1]);

	return 0;
}