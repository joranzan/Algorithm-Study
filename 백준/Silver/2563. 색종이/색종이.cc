#include<iostream>

using namespace std;



int main() {

	int Map[100][100] = { 0, };
	int N;
	int cnt = 0;
	cin >> N;

	for (int i = 0; i < N; i++) {

		int col, row;
		cin >> col >> row;

		for (int r = row; r < row + 10; r++) {
			for (int c = col; c < col + 10; c++) {
				if (Map[r][c] == 0) {
					cnt++;
					Map[r][c] = 1;
				}
			}
		}



	}
	cout << cnt;

	return 0;
}