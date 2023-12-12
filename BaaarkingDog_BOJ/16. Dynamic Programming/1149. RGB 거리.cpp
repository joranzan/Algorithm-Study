#include<iostream>

using namespace std;

//문제 분석
//RGB  0 1 2
//1번 집의 색은 2번 집의 색과 같지 않아야함
//N번 집은 N-1번 집과 같지 않아야함

int N;
int cost[1001][3] = { 0, };
int DP[1001][3] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	}

	for (int i = 0; i < 3; i++) DP[1][i] = cost[1][i];

	for (int i = 2; i <= N; i++) {
		DP[i][0] = min(DP[i - 1][1], DP[i - 1][2]) + cost[i][0];
		DP[i][1] = min(DP[i - 1][0], DP[i - 1][2]) + cost[i][1];
		DP[i][2] = min(DP[i - 1][0], DP[i - 1][1]) + cost[i][2];
	}

	int Answer = min(DP[N][0], DP[N][1]);
	Answer = min(Answer, DP[N][2]);

	cout << Answer;

	return 0;
}