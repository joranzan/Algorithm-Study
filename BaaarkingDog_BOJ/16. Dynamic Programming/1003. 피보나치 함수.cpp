#include<iostream>
#include<vector>

using namespace std;

struct mystruct {
	int zero;
	int one;
};

mystruct DP[41] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	DP[0] = { 1,0 };
	DP[1] = { 0,1 };

	int T;
	cin >> T;
	
	int maxNum = 0;
	vector<int> v;

	for (int i = 0; i < T; i++) {
		int temp;
		cin >> temp;
		v.push_back(temp);
		maxNum = max(maxNum, temp);
	}

	for (int i = 2; i <= maxNum; i++) {
		DP[i].zero = DP[i - 1].zero + DP[i - 2].zero;
		DP[i].one = DP[i - 1].one + DP[i - 2].one;
	}

	for (int i = 0; i < v.size(); i++) {
		cout << DP[v[i]].zero << " " << DP[v[i]].one << "\n";
	}

	return 0;
}