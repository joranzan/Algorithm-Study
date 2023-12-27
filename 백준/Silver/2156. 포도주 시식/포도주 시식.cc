#include<iostream>

using namespace std;

int N;
int DP[2][10001] = { 0, };
int Wine[10001] = { 0, };

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> Wine[i];
		DP[0][i] = Wine[i];
	}

	int Answer = 0;

	for (int i = 1; i < N; i++) {
		int anchor1 = DP[0][i];
		int anchor2 = DP[1][i];

		DP[1][i + 1] = max(DP[1][i + 1], anchor1 + Wine[i + 1]);

		//if (anchor1 == 0) continue;

		for (int j = i + 2; j <= N; j++) {
			DP[0][j] = max(DP[0][j], anchor1 + Wine[j]);
		}


		//if (anchor2 == 0) continue;

		for (int j = i + 2; j <= N; j++) {
			DP[0][j] = max(DP[0][j], anchor2 + Wine[j]);
		}
	}

	for (int i = 1; i <= N; i++) {
		Answer = max(Answer, DP[0][i]);
		Answer = max(Answer, DP[1][i]);
	}

	cout << Answer;

	return 0;
}

//마시고 원래 위치
//연속 3잔 안됨

/*
6 10 13 9  8  1
6 10 19 19 27 20
  16 23 28 31 29

1000 1000 1000 1000 1000
1000      2000 2000 2000


*/
