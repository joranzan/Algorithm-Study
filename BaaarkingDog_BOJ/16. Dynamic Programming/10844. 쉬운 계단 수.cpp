#include<iostream>

using namespace std;


int DP[10][101] = { 0, };

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (int i = 1; i <= 9; i++) DP[i][1] = 1;

	for (int i = 1; i <= N - 1; i++) {
		for (int j = 0; j <= 9; j++) {
			if (DP[j][i] == 0) continue;
			int next1 = j + 1;
			int next2 = j - 1;
			
			if (next1 < 10) {
				DP[next1][i + 1] += DP[j][i];
				if (DP[next1][i + 1] >= 1000000000) {
					DP[next1][i + 1] = DP[next1][i + 1] % 1000000000;
				}
			}
			if (next2 >= 0) {
				DP[next2][i + 1] += DP[j][i];
				if (DP[next2][i + 1] >= 1000000000) {
					DP[next2][i + 1] = DP[next2][i + 1] % 1000000000;
				}
			}
			
		}
	}

	int Answer = 0;

	for (int i = 0; i <= 9; i++) {
		Answer += DP[i][N];
		if (Answer >= 1000000000) {
			Answer = Answer % 1000000000;
		}
	}

	cout << Answer;

	return 0;
}