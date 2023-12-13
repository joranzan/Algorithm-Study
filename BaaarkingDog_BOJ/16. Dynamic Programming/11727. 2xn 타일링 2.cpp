#include<iostream>

using namespace std;

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	int DP[1001] = { 0, };
	DP[1] = 1;
	DP[2] = 3;

	cin >> N;

	for (int i = 3; i <= N; i++) {
		DP[i] = (DP[i - 1] + DP[i - 2] * 2) % 10007;
	}

	cout << DP[N];

	return 0;
}