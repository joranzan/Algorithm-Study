#include<iostream>

using namespace std;

//2n개 -> 2행 N열

/*
변을 공유하는 스티커 못사용함



*/

int Score[2][100000] = { 0, };
int DP[2][100000] = { 0, };

const int dr[2][4] = { {1, 1,0, 0},{-1, -1,0,0} };
const int dc[2][4] = { {1,2, 2, 3}, {1,2, 2,3} };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int test = 0; test < T; test++) {
		int N;
		cin >> N;

		for (int r = 0; r < 2; r++) {
			for (int c = 0; c < N; c++) {
				cin >> Score[r][c];
				DP[r][c] = Score[r][c];
				
			}
		}

		for (int c = 0; c < N; c++) {
			for (int r = 0; r < 2; r++) {
				for (int dir = 0; dir < 4; dir++) {
					int nextRow = r + dr[r][dir];
					int nextCol = c + dc[r][dir];

					if (nextRow < 0 || nextCol < 0 || nextRow >= 2 || nextCol >= N) continue;
					DP[nextRow][nextCol] = max(DP[nextRow][nextCol], DP[r][c] + Score[nextRow][nextCol]);
					
				}

			}
		}

		int debugging = -1;
		int Answer = 0;
		for (int r = 0; r < 2; r++) {
			for (int c = 0; c < N; c++) {
				Answer = max(Answer, DP[r][c]);
			}
		}
		cout << Answer << "\n";
	}

	

	return 0;
}