#include<iostream>

using namespace std;

int arr[1000] = { 0, };
int DP[1000] = { 0, };

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		DP[i] = arr[i];
	}

	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			if (arr[i] < arr[j]) {
				DP[j] = max(DP[j], DP[i] + arr[j]);
			}
		}
	}
	int Answer = 0;
	for (int i = 0; i < N; i++) {
		Answer = max(Answer, DP[i]);
	}

	cout << Answer;

	return 0;
}