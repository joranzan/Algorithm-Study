#include<iostream>

using namespace std;

int main() {

	int N;
	cin >> N;



	int fiveCnt = 0;
	int threeCnt = 0;

	//3 6 9 12 15
	//5 10 15
	

	while(N > 0) {
		if (N % 5 == 0) {
			fiveCnt += (N / 5);
			break;
		}
		N -= 3;
		if (N < 0) {
			cout << "-1";
			return 0;
		}
		threeCnt++;
	}

	if (threeCnt == 0 && fiveCnt == 0) cout << "-1";
	else cout << threeCnt + fiveCnt;

	return 0;
}