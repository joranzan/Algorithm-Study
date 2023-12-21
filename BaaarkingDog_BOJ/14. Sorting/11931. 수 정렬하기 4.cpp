#include<iostream>
#include<vector>

using namespace std;

int DP[10001] = { 0, };
vector<int> A;


int main()
{

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, K;
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		int value;
		cin >> value;
		A.push_back(value);
	}
	for (int i = 0; i < A.size(); i++) {
		if (A[i] > K) continue;
		DP[A[i]] = 1;
	}
	//for (int i = 0; i < B.size(); i++) DP[B[i]] = 1;

	for (int i = 0; i <= K; i++) {
		if (DP[i] == 0) continue;
		for (int j = 0; j < A.size(); j++) {
			if (A[j] > K) continue;
			int next = i + A[j];
			if (next > K) continue;
			if (DP[next] == 0) DP[next] = DP[i] + 1;
			else DP[next] = min(DP[next], DP[i] + 1);
		}
	}

	if (DP[K] == 0) cout << "-1";
	else cout << DP[K];

	return 0;
}