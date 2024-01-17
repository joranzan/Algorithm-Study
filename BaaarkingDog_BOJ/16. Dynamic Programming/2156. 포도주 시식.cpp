#include<iostream>

using namespace std;

int N;
int DP[10001] = { 0, };
int Wine[10001] = { 0, };

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> Wine[i];
	}

	DP[1] = Wine[1];
	DP[2] = DP[1] + Wine[2];


	for (int i = 3; i <= N; i++) {
		
		int a = DP[i - 2] + Wine[i];
		int b = DP[i - 3] + Wine[i - 1] + Wine[i];
		int c = DP[i - 1];

		DP[i] = max(a, max(b, c));
	}


	cout << DP[N];

	return 0;
}

//마시고 원래 위치
//연속 3잔 안됨

/*
마시거나 안마시거나

OOX
OXX -> 비교 할 필요없음
XOX -> 비교할 필요없음
XXX  -> 비교 할 필요없음

XXO  -> 비교 할 필요없음
XOO
OXO


DP[i] = DP[i-3] + Wine[i-1] + Wine[i]
DP[i] = DP[i-2] + Wine[i]


*/
