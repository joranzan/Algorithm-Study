#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int arr[101] = { 0, };
	int N, M;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		arr[i] = i;
	}

	for (int q = 0; q < M; q++) {
		int i, j;
		cin >> i >> j;

		while (i < j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	for (int i = 1; i <= N; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}

