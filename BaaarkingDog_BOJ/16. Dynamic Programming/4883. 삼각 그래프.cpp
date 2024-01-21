#include<iostream>

using namespace std;

int N;
int Cost[100001][3] = { 0, };
int DP[100001][3] = { 0, };




int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int test = 1;

	while (1) {
		
		int N;
		cin >> N;
		if (N == 0) break;

		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> Cost[i][j];
				DP[i][j] = 2100000000;
			}
		}

		DP[1][0] = 2100000000;
		DP[1][1] = Cost[1][1];
		DP[1][2] = Cost[1][1] + Cost[1][2];

		for (int i = 1; i < N; i++) {

			//0열
			DP[i][1] = min(DP[i][1], DP[i][0] + Cost[i][1]);
			DP[i + 1][0] = min(DP[i + 1][0], DP[i][0] + Cost[i + 1][0]);
			DP[i + 1][1] = min(DP[i + 1][1], DP[i][0] + Cost[i + 1][1]);

			//1열

			DP[i][2] = min(DP[i][2], DP[i][1] + Cost[i][2]);
			DP[i + 1][1] = min(DP[i + 1][1], DP[i][1] + Cost[i + 1][1]);
			DP[i + 1][2] = min(DP[i + 1][2], DP[i][1] + Cost[i + 1][2]);
			DP[i + 1][0] = min(DP[i + 1][0], DP[i][1] + Cost[i + 1][0]);

			//2열
			DP[i + 1][2] = min(DP[i + 1][2], DP[i][2] + Cost[i + 1][2]);
			DP[i + 1][1] = min(DP[i + 1][1], DP[i][2] + Cost[i + 1][1]);
		}

		DP[N][1] = min(DP[N][1], DP[N][0] + Cost[N][1]);

		cout << test << ". " << DP[N][1] << "\n";
		
		test++;

		//초기화
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < 3; j++) {
				DP[i][j] = 2100000000;
			}
		}
	}



	return 0;
}