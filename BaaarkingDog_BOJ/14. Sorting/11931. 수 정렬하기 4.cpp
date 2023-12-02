#include<iostream>
#include<algorithm>

using namespace std;

int arr[1000000];

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);

	for (int i = N - 1; i >= 0; i--) {
		cout << arr[i] << "\n";
	}


	return 0;
}