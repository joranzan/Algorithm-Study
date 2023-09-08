#include<iostream>
#include<cmath>

using namespace std;

//문제 분석

//종이를 색깔별로 자른다

//색칠 안되어있으면 4등분

// 하얀색: 0  파랑색: 1

struct pos {
	int row;
	int col;
};

int N;
int Map[130][130] = { 0, };
int DAT[2] = { 0 };

void Recursion(pos start, pos end, int n) {

	if (n == 0) {
		DAT[Map[start.row][start.col]]++;
		return;
	}
	
	//같은게 있는지 확인하는 부분
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

	//다 같으면 개수 추가
	if (same) {
		DAT[start_num]++;
		return;
	}

	//4등분 재귀
	int currentLength = pow(2, n - 1);
	Recursion({ start.row,start.col }, { start.row + currentLength - 1, start.col + currentLength - 1 }, n - 1);
	Recursion({ start.row, start.col + currentLength }, { start.row + currentLength - 1, start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row + currentLength, start.col }, { start.row + currentLength * 2 - 1, start.col + currentLength - 1 }, n - 1);
	Recursion({ start.row + currentLength, start.col + currentLength }, { start.row + currentLength * 2 - 1,start.col + currentLength * 2 - 1 }, n - 1);

}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			cin >> Map[i][j];
		}
	}

	int num = N;
	int power = 0;

	while (num != 1) {
		num = num / 2;
		power++;
	}

	Recursion({ 0,0 }, { N - 1,N - 1 }, power);

	for (int i = 0; i < 2; i++) {
		cout << DAT[i] << "\n";
	}

	return 0;
}

//만약 n=0이면 파랑 또는 흰색 개수 늘린후 return

//탐색해서 다 같은지 flag 두기

//