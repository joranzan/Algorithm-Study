#include<iostream>

using namespace std;

int N, M;
int Coin[21] = { 0, };
int DP[10001] = { 0, };

void init() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> Coin[i];
	cin >> M;
	//DP 배열 초기화
	for (int i = 0; i <= M; i++) DP[i] = 0;
	DP[0] = 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		init();

		for (int i = 0; i < N; i++) {
			int coin = Coin[i];
			for (int j = 1; j <= M; j++) {
				if (j - coin < 0) continue;
				DP[j] += DP[j - coin];
			}
		}

		cout << DP[M] << "\n";

	}

	

	return 0;
}

/*
- T : 테스트 케이스의 개수 (1 ≤ T ≤ 10)
- N : 동전의 가지 수 (1 ≤ N ≤ 20)

- N가지 동전의 각 금액이 오름차순 (1 ≤ 금액 ≤ 10000)
- M : N가지 동전으로 만들어야 할 금액 (1 ≤ M ≤ 10000)

1, 2
1000

0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22
1 0 0 0 0 1 0 1 0 0 1   0  1  0 1   1  0  1  0  1  2 1  1


*/