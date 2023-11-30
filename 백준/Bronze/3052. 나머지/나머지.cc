#include<iostream>

using namespace std;



int main() {

	int DAT[41] = { 0, };

	for (int i = 0; i < 10; i++) {
		int num;
		cin >> num;
		DAT[num % 42] = 1;
	}
	int cnt = 0;
	for (int i = 0; i < 42; i++) {
		if (DAT[i] == 1) cnt++;
	}

	cout << cnt;

	return 0;
}