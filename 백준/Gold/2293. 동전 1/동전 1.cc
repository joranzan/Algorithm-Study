#include<iostream>

using namespace std;

int Coin[101] = { 0, };
int DP[10001] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, K;
	cin >> N >> K;

	int nowIndex = 0;
	
	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;

		if (temp > K) continue;
		Coin[nowIndex] = temp;
		nowIndex++;
	}

	//coin 개수 nowIndex개 (0 ~ nowIndex-1)
	DP[0] = 1;
	for (int i = 0; i < nowIndex; i++) {
		for (int k = 0; k <= K; k++) {
			if (k - Coin[i] < 0) continue;
			DP[k] += DP[k - Coin[i]];
		}
	}

	cout << DP[K];

	return 0;
}

/*
0 1 2 3 4 5 6 7 8 9 10
1 1 2 2 3 4 5 6 7 8 10  

111
21
12

1111
211
22
112
*/