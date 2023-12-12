#include<iostream>

using namespace std;

int N;
int score[301] = { 0, };
int DP[301][3] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> score[i];
	}
	DP[N][1] = DP[N][2] = score[N];
	DP[N - 1][1] = 0;
	DP[N - 1][2] = DP[N][1] + score[N - 1];

	for (int i = N-2; i >= 0; i--) {
		DP[i][1] = max(DP[i + 2][2], DP[i + 2][1]) + score[i];
		DP[i][2] = DP[i + 1][1] + score[i];
	}

	int Answer =  max(DP[0][1], DP[0][2]);
	Answer = max(Answer, DP[1][1]);
	Answer = max(Answer, DP[1][2]);

	cout << Answer;

	return 0;
}

//계단 오를때 1칸 또는 2칸
//1칸씩 3번이상 금지

//테이블 정의하기 (2차원 배열)
// 
//