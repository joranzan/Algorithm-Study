#include<iostream>

using namespace std;

int DAT[1000001] = { 0, };
int N;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	DAT[1] = 0;

	for (int i = 2; i <= N; i++) {
		DAT[i] = DAT[i - 1] + 1;
		if (i % 2 == 0) DAT[i] = min(DAT[i], DAT[i / 2] + 1);
		if (i % 3 == 0) DAT[i] = min(DAT[i], DAT[i / 3] + 1);
	}

	cout << DAT[N];

	return 0;
}