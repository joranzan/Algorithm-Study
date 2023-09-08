#include<iostream>
#include<cmath>

using namespace std;

struct pos {
	int row;
	int col;
};

int N;
int Map[64][64] = { 0, };

void Recursion(pos start, pos end, int n) {

	if (n == 0) {
		cout << Map[start.row][start.col];
		return;
	}
	
	bool same = true;
	int start_num = Map[start.row][start.col];
	for (int i = start.row; i <= end.row; i++) {
		for (int j = start.col; j <= end.col; j++) {
			if (start_num != Map[i][j]) {
				same = false;
				break;
			}
		}
		if (!same) break;
	}

	if (same) {
		cout << start_num;
		return;
	}

	int currentLength = pow(2, n - 1);
	cout << "(";
	Recursion({ start.row,start.col }, { start.row + currentLength - 1,start.col + currentLength - 1 }, n - 1);
	Recursion({ start.row,start.col + currentLength }, { start.row + currentLength - 1,start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row + currentLength,start.col }, { start.row + currentLength * 2 - 1,start.col + currentLength - 1 }, n - 1);
	Recursion({ start.row + currentLength, start.col + currentLength }, { start.row + currentLength * 2 - 1,start.col + currentLength * 2 - 1 }, n - 1);
	cout << ")";
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < N; j++) {
			Map[i][j] = int(s[j]-'0');
		}
	}

	int num = N;
	int power = 0;

	while (num != 1) {
		num = num / 2;
		power++;
	}

	Recursion({ 0,0 }, { N - 1,N - 1 }, power);


	return 0;
}