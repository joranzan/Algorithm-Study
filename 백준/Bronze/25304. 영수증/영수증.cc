#include<iostream>

using namespace std;

int main() {

	int X, N;
	cin >> X >> N;

	int sum = 0;

	for (int i = 0; i < N; i++) {
		int price, num;
		cin >> price >> num;
		sum += (price * num);
	}
	if (sum == X) cout << "Yes";
	else cout << "No";

	return 0;
}
