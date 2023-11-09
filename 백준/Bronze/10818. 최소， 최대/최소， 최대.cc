#include<iostream>

using namespace std;

int main() {

	int N;
	cin >> N;

	int minValue = 2112345678;
	int maxValue = -2112345678;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		minValue = min(minValue, num);
		maxValue = max(maxValue, num);
	}

	cout << minValue << " " << maxValue;


	return 0;
}