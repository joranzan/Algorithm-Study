#include<iostream>

using namespace std;

int N;
// 0 ; 1
// 1 : 1
// 2 : 2
// 3 : 4
// 4 : 3+1
// 5 : 3+2
// 6 : 3+3


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	int DAT[12] = { 0, };
	DAT[0] = 1;
	DAT[1] = 1;
	DAT[2] = 2;
	for (int i = 3; i <= 11; i++) {
		DAT[i] = DAT[i - 1] + DAT[i - 2] + DAT[i - 3];
	}

	for (int test = 0; test < T; test++) {
		cin >> N;
		cout << DAT[N] << "\n";
	}


	return 0;
}