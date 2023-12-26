#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

long long DP[1000001] = { 0, };
vector<int> Query;

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	int maxN = 0;

	for (int i = 0; i < T; i++) {
		int temp;
		cin >> temp;
		Query.push_back(temp);
		maxN = max(maxN, temp);
	}


	DP[1] = 1;
	DP[2] = 2;
	DP[3] = 4;

	for (int i = 4; i <= maxN; i++) {
		DP[i] = DP[i - 1] + DP[i - 2] + DP[i - 3];
		if (DP[i] >= 1000000009) DP[i] = DP[i] % 1000000009;
	}

	for (int i = 0; i < T; i++) {
		cout << DP[Query[i]] << "\n";
	}

	return 0;
}

/*

1 
1

2
1+1 2

3
3
2+1 1+1+1
1+2 

4
3+1 2+1+1 1+1+1+1 1+2+1
2+2 1+1+2
1+3


5
4+1 3+1+1 
3+2
2+3

1 2 4 7 13 24 44 81 149 274 


*/