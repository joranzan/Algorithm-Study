#include<iostream>

using namespace std;

struct info{
	int cnt;
	int from;
};

int N;
info DP[1000001];

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	DP[1] = { 0,0 };
	
	for (int i = 2; i <= N; i++) {
		DP[i] = { DP[i - 1].cnt + 1, i - 1 };
		if (i % 2 == 0) {
			if (DP[i].cnt > DP[i / 2].cnt + 1) {
				DP[i].cnt = DP[i / 2].cnt + 1;
				DP[i].from = i / 2;
			}
		}
		if (i % 3 == 0) {
			if (DP[i].cnt > DP[i / 3].cnt + 1) {
				DP[i].cnt = DP[i / 3].cnt + 1;
				DP[i].from = i / 3;
			}
		}
	}

	cout << DP[N].cnt << "\n";

	int index = N;
	while (index != 1) {
		cout << index<<" ";
		index = DP[index].from;
	}

	cout << "1";

	return 0;
}