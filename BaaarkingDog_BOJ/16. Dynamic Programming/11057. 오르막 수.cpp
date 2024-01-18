#include<iostream>

using namespace std;

int DAT[10] = { 0, };
int DP[10][1002] = { 0, };
int N;

int Recursion(int digit, int num) {
	if (digit == N) return DP[num][digit];

	if (DP[num][digit] != 0) return DP[num][digit];

	long long cnt = 0;
	for (int i = num; i < 10; i++) {
		cnt += Recursion(digit + 1, i);
		if (cnt >= 10007) cnt %= 10007;
	}
	DP[num][digit] = cnt;
	return cnt;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	DAT[9] = 1;
	
	for (int i = 0; i <= 9; i++) {
		DP[i][N] = 1;
	}


	//规过 1) Recursion
	// 
	//long long Answer = 0;
	//for (int i = 0; i <= 9; i++) {
	//	int ret = Recursion(1, i);
	//}
	//
	//for (int i = 0; i <= 9; i++) {
	//	Answer += DP[i][1];
	//	if (Answer >= 10007) Answer %= 10007;
	//}

	//cout << Answer;



	//规过 2) Bottom-up

	for (int digit = N; digit >= 1; digit--) {

		if (digit != N) {
			for (int num = 0; num <= 9; num++) {
				DP[num][digit] = DP[num][digit + 1];
			}
		}
		
		for (int num = 8; num >= 0; num--) {
			DP[num][digit] += DP[num + 1][digit];
			if (DP[num][digit] >= 10007) DP[num][digit] %= 10007;
		}
	}

	cout << DP[0][1];



	return 0;
}