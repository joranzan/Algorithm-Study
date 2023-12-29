#include<iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	long N;
	cin >> N;
	long C = -N;

	int cnt = 0;

	for (int i = 0; i < 32; i++) {
		if ((N & 1) != (C & 1)) cnt++;
		N >>= 1; C >>= 1;

	}

	cout << cnt;

	return 0;
}