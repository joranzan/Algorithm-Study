#include<iostream>

using namespace std;
/*
문제 분석

15가지 참석 방법

ABCD

1. 열쇠는 단 하나 
	1) 열쇠를 가진 사람은 무조건 활동에 참여
	2) 활동 겹치는(내일도 참여하는) 사람한테 열쇠 넘겨줄 수 있음

2. 첫째날 : A가 가지고 있음

3. 각 날마다 책임자가 있음 -> 꼭 참석해야함

*/

int Always[10001] = { 0, };
int DP[16][10001] = { 0, };
string s;
int dayTotal = 0;
int Answer = 0;


void init() {

	dayTotal = s.size();
	Answer = 0;
	for (int i = 1; i <= dayTotal; i++) {
		int temp = 1 << (3- int(s[i - 1] - 'A'));
		Always[i] = temp;
		for (int j = 1; j <= 15; j++) DP[j][i] = 0;
	}
}

void solution() {

	for (int i = 1; i <= 15; i++) {
		int temp = i & Always[1];
		if (!temp) continue;
		temp = i & (1 << 3);
		if (!temp) continue;
		DP[i][1]++;
	}

	for (int i = 2; i <= dayTotal; i++) {

		for (int j = 1; j <= 15; j++) {

			if (DP[j][i - 1] == 0) continue;
			else {
				for (int k = 1; k <= 15; k++) {
					if ((j & k) == 0) continue;
					if ((k & Always[i]) == 0) continue;
					DP[k][i] += DP[j][i - 1];
					if (DP[k][i] >= 1000000007) DP[k][i] -= 1000000007;
				}
			}
		}
	}

	for (int i = 1; i <= 15; i++) {
		Answer += DP[i][dayTotal];
		if (Answer >= 1000000007)Answer = Answer % 1000000007;
	}

	int debugging = -1;
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> s;
		init();
		solution();
		cout << "#" << test << " " << Answer << "\n";
	}
	return 0;
}

