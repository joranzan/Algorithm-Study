#include<iostream>

using namespace std;

int Arr[100000] = { 0, };
int DP[100000] = { 0, };


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	int Answer = Arr[0];

	for (int i = 0; i < N; i++) {
		cin >> Arr[i];
		if (i == 0) {
			Answer = Arr[0];
		}
		else if (Arr[i - 1] < 0) {
			Arr[i] = max(Arr[i - 1] + Arr[i], Arr[i]);
		}
		else {
			Arr[i] += Arr[i - 1];
		}

		Answer = max(Answer, Arr[i]);
	}

	//DP[0] = Arr[0];
	//for (int i = 1; i < N; i++) {

	//	if (DP[i - 1] < 0) {
	//		DP[i] = Arr[i];
	//	}
	//	else if (Arr[i] < 0) {
	//		DP[i] = max(DP[i - 1] + Arr[i], Arr[i]);
	//	}
	//	else {
	//		DP[i] = Arr[i] + DP[i - 1];
	//	}
	//	Answer = max(Answer, DP[i]);
	//}

	cout << Answer;

	return 0;
}