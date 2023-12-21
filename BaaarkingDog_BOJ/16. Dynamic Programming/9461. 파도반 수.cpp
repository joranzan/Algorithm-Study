#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long DP[101] = { 0, };
int maxN = 0;
vector<int> tc;


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 0; test < T; test++) {
		int N;
		cin >> N;
		tc.push_back(N);
		maxN = max(N, maxN);
	}

	DP[1] = 1;
	DP[2] = 1;
	DP[3] = 1;
	DP[4] = 2;
	DP[5] = 2;

	for (int i = 6; i <= maxN; i++) {
		DP[i] = DP[i - 1] + DP[i - 5];
	}

	for (int i = 0; i < T; i++) {
		cout << DP[tc[i]] << "\n";
	}

	return 0;
}

/*

	1, 1, 1, 2, 2, 3, 4, 5, 7, 9, 12 , 16, 21  28

	 0   0  1  0  1  1  1  2  2  3   4    5  7


*/