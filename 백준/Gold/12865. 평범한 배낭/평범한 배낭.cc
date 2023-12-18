#include<iostream>
#include<algorithm>

using namespace std;

int weight[101] = { 0, };
int value[101] = { 0, };
int DP[100001][101] = { 0, };

int main(){

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T = 1;
	//cin >> T;
	for (int test = 1; test <= T; test++) {
		int N, K;
		cin >> N >> K;

		for (int i = 1; i <= N; i++) {
			cin >> weight[i] >> value[i];
		}

		for (int i = 1; i <= N; i++) {
			for (int k = 0; k <= K; k++) {
				if(k<weight[i]) DP[k][i] = DP[k][i - 1];
				else {
					DP[k][i] = max(DP[k][i - 1], DP[k - weight[i]][i - 1] + value[i]);
				}
			}
		}

		//int Answer = 0;

		//for (int i = 0; i <= K; i++) {
		//	Answer = max(Answer, DP[i][N]);
		//}

		//cout << "#" << test << " " << DP[K][N] << "\n";
		cout << DP[K][N];
	}


	return 0;
}

/*

1
4 5
1 2
3 2
4 4
2 3

*/