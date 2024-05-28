#include<iostream>

using namespace std;

int DP[1001][10] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	
	for (int i = 1; i <= N; i++) DP[i][0] = 1;

	for (int i = 0; i < 10; i++) DP[1][i] = i + 1;

	for (int i = 2; i <= N; i++) {
		for (int j = 1; j < 10; j++) {
			DP[i][j] += (DP[i - 1][j] + DP[i][j - 1]);
			if (DP[i][j] >= 10007) DP[i][j] %= 10007;
		}
	}
	
	cout << DP[N][9];


	/*
	  0 1 2 3 4 5 6 7 8 9
    0 0 0 0 0 0 0 0 0 0 0
	1 1 2 3 4 5 6 7 8 9 10
	2 1 3 6 10 5 6 7 8 9 10
	3 1 
	4 1
	5 1
	6 1
	7 1
	8 1
	9 1
   10 1
	
	
	*/





}