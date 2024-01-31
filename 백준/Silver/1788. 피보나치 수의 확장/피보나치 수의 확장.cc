#include<iostream>

using namespace std;

int N;
int DP[1000001] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	int absN = abs(N);

	DP[0] = 0;
	DP[1] = 1;


	for (int i = 2; i <= absN; i++) {
		DP[i] = DP[i - 1] + DP[i - 2];
		if (DP[i] >= 1000000000) DP[i] %= 1000000000;
	}

	if (N == 0) {
		cout << "0\n";
		cout << DP[0];
	}
	else if (N > 0) {
		cout << "1\n";
		cout << DP[N];
	}
	else {
		if (absN % 2 == 0) {
			cout << "-1\n";
			cout << DP[absN];
		}
		else {
			cout << "1\n";
			cout << DP[absN];
		}
	}


	return 0;
}

/*
문제 분석

-5 -4 -3 -2 -1 0 1 2 3 4
 5 -3  2 -1  1 0 1 1 2 3 5
 
*/