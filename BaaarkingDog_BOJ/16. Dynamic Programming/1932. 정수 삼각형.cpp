#include<iostream>
#include<algorithm>

using namespace std;

int N;
int arr[501][501];
int DP[501][501] = { 0, };



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			cin >> arr[i][j];
		}
	}

	DP[1][1] = arr[1][1];

	for (int i = 1; i < N; i++) {
		for (int j = 1; j <= i; j++) {
			DP[i + 1][j] = max(DP[i + 1][j], DP[i][j] + arr[i + 1][j]);
			DP[i + 1][j + 1] = max(DP[i + 1][j + 1], DP[i][j] + arr[i + 1][j + 1]);
		}
	}

	cout << *max_element(DP[N] + 1, DP[N] + N + 1);

	return 0;
}