#include<iostream>
#include<algorithm>



using namespace std;

int Arr[1001] = { 0, };
int DP[1001] = { 0, };

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Arr[i];
		DP[i] = 1;
	}

	int Answer = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			if(Arr[j]>Arr[i]) DP[j] = max(DP[i] + 1, DP[j]);
		}
		Answer = max(Answer, DP[i]);
	}

	cout << Answer;

	return 0;
}