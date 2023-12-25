#include<iostream>

using namespace std;

int N;
int Info[2][1501000] = { 0, };
int DP[1501000] = { 0, };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> Info[0][i] >> Info[1][i];
	}
	
	int Answer = 0;

	for (int i = 1; i <= N; i++) {

		int deadline = i + Info[0][i] - 1;
		if (deadline <= N) {
			DP[deadline] = max(DP[deadline], Answer + Info[1][i]);
		}
		Answer = max(Answer, DP[i]);
	}

	
	cout << Answer;

	return 0;
}