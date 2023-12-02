#include<iostream>

using namespace std;

int arr[1000001] = { 0, };
int arr_minus[1000001] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int maxNum = 0;
	int minNum = 1000001;
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		if (num >= 0) {
			arr[num]++;
		}
		else {
			arr_minus[abs(num)]++;
		}
		
		maxNum = max(maxNum, num);
		minNum = min(minNum, num);
	}

	for (int i = minNum; i <= maxNum; i++) {
		if (i < 0) {
			for (int j = 0; j < arr_minus[abs(i)]; j++) {
				cout << i << "\n";
			}
		}
		else {
			for (int j = 0; j < arr[i]; j++) {
				cout << i << "\n";
			}
		}
	}


	return 0;
}