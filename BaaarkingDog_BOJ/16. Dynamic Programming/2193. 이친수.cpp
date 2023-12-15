#include<iostream>

using namespace std;

//이친수의 성질
//1. 0으로 시작하지 않는다
//2. 1이 두번 연속으로 나타나지 않는다

//DP Table 2차원?
// 
//목표)
//N자리 이친수 개수

long long DP[2][91] = { 0, };
//0번 인덱스 -> 전 숫자가 0
//1번 인덱스 -> 전 숫자가 1

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	DP[0][1] = 0;
	DP[1][1] = 1;

	for (int i = 2; i <= N; i++) {
		DP[0][i] = DP[0][i - 1] + DP[1][i - 1];
		DP[1][i] = DP[0][i - 1];
	}

	cout << DP[0][N] + DP[1][N];

	return 0;
}