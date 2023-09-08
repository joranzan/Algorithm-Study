#include<iostream>
#include<cmath>

using namespace std;

struct pos
{
	int row;
	int col;
};

int N;
int Map[2200][2200] = { 0, };
int DAT[3] = { 0 }; //0:-1 1: 0 2: 1

void Recursion(pos start, pos end, int n) { //start end n

	if (n == 0) {
		DAT[Map[start.row][start.col] + 1]++;
		return;
	}
	//다 같은지 탐색
	bool same = true;
	int start_num = Map[start.row][start.col];

	for (int i = start.row; i <= end.row; i++) {
		for (int j = start.col; j <= end.col; j++) {
			if (start_num != Map[i][j]) {
				same = false;
			}
		}
		if (!same) break;
	}

	//같으면 cnt++ 하고 return
	if (same) {
		DAT[Map[start.row][start.col] + 1]++;
		return;
	}

	int currentLength = pow(3, n - 1);   //3
	//start.row ~ start.row+currentLength - 1
	//start.row + currentLength  ~ start.row+currentLength*2-1
	//start.row + currentLength*2  ~ start.row + currentLength*3-1 

	

	//다르면 9등분 시작

	//첫째 줄
	Recursion({ start.row, start.col }, { start.row + currentLength - 1,start.col + currentLength - 1 }, n - 1);
	Recursion({ start.row , start.col + currentLength }, { start.row + currentLength - 1, start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row, start.col + currentLength * 2 }, { start.row + currentLength - 1, start.col + currentLength * 3 - 1 }, n - 1);

	//둘째 줄
	Recursion({ start.row + currentLength, start.col }, { start.row + currentLength * 2 - 1,start.col + currentLength - 1 }, n - 1);;
	Recursion({ start.row + currentLength , start.col + currentLength }, { start.row + currentLength * 2 - 1, start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row + currentLength, start.col + currentLength * 2 }, { start.row + currentLength * 2 - 1, start.col + currentLength * 3 - 1 }, n - 1);

	//셋째 줄
	Recursion({ start.row + currentLength*2 , start.col }, { start.row + currentLength * 3 - 1,start.col + currentLength - 1 }, n - 1);;
	Recursion({ start.row + currentLength*2 , start.col + currentLength }, { start.row + currentLength * 3 - 1, start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row + currentLength*2, start.col + currentLength * 2 }, { start.row + currentLength * 3 - 1, start.col + currentLength * 3 - 1 }, n - 1);

}

int main() {

	
	//N이되기 위한 3의 지수 구하기
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
		}
	}

	int num = N;
	int power = 0;    //Recursion 횟수
	while (num != 1) {
		num = num / 3;
		power++;
	}

	Recursion({ 0,0 }, { N - 1,N - 1 }, power);

	for (int i = 0; i < 3; i++) {
		cout << DAT[i] << "\n";
	}

	return 0;
}
