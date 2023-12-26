#include<iostream>

using namespace std;

int T, W;

int DP[3][31][1001] = { 0, };
int Score[3][1001] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> T >> W;

	for (int i = 1; i <= T; i++) {

		int num;
		cin >> num;

		Score[num][i] = 1;
	}
	
	DP[1][0][1] = Score[1][1];
	DP[2][1][1] = Score[2][1];

	for (int i = 2; i <= T; i++) {
		for (int j = 0; j <= W; j++) {
			for (int now = 1; now <= 2; now++) {

				if (now == 1) {
					DP[now][j][i] = max(DP[now][j][i], DP[now][j][i - 1] + Score[now][i]);
					if (j + 1 <= W) {
						DP[2][j + 1][i] = max(DP[2][j + 1][i], DP[now][j][i] + Score[2][i]);
					}
				}
				else if (now == 2) {
					DP[now][j][i] = max(DP[now][j][i], DP[now][j][i - 1] + Score[now][i]);
					if (j + 1 <= W) {
						DP[1][j + 1][i] = max(DP[1][j + 1][i], DP[now][j][i] + Score[1][i]);
					}
				}
			}

		}
	}
	int Answer = 0;
	for (int i = 0; i <= W; i++) {
		for (int j = 1; j <= 2; j++) {
			Answer = max(Answer, DP[j][i][T]);
		}
	}

	cout << Answer;

	return 0;
}

/*
문제분석

매초마다 두개의 나무중 하나의 나무에서 열매 떨어짐

최대 30번 움직임

2 1 1 2 2 1 1

0 1 1 0 0 1 1
1 0 0 1 1 0 0

0 1 2 0 0 1 1
1 1 1 2 3 3 3
  2 3 3 3 4 4
    2 4 5 5 5
        5 5 5	  
*/