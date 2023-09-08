#include<iostream>
#include<cmath>

using namespace std;

struct pos {
	int row;
	int col;
};

void Recursion(pos start, pos end, int n);

int N;
char Map[6562][6562] = { NULL, };
//
//
//void star(pos start, pos end) {
//
//	for (int i = start.row; i <= end.row;i++) {
//		for (int j = start.col; j <= end.col; j++) {
//			Map[i][j] = '*';
//		}
//	}
//	Map[start.row + 1][start.col + 1] = ' ';
//
//}


int main() {

	cin >> N;

	int num = N;
	int power = 0;
	while (num != 1) {
		num = num / 3;
		power++;
	}

	Recursion({ 0,0 }, { N - 1, N - 1 }, power);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] == '*') {
				cout << Map[i][j];
			}
			else cout << " ";
			
		}
		cout << "\n";
	}

	return 0;
}


void Recursion(pos start, pos end, int n) { //start end n

	if (n == 0) {
		//star(start, end);
		Map[start.row][start.col] = '*';
		return;
	}

	int currentLength = pow(3, n - 1);   //3

	//다르면 9등분 시작

	//첫째 줄
	Recursion({ start.row, start.col }, { start.row + currentLength - 1,start.col + currentLength - 1 }, n - 1);
	Recursion({ start.row , start.col + currentLength }, { start.row + currentLength - 1, start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row, start.col + currentLength * 2 }, { start.row + currentLength - 1, start.col + currentLength * 3 - 1 }, n - 1);

	//둘째 줄
	Recursion({ start.row + currentLength, start.col }, { start.row + currentLength * 2 - 1,start.col + currentLength - 1 }, n - 1);;
	//Recursion({ start.row + currentLength , start.col + currentLength }, { start.row + currentLength * 2 - 1, start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row + currentLength, start.col + currentLength * 2 }, { start.row + currentLength * 2 - 1, start.col + currentLength * 3 - 1 }, n - 1);

	//셋째 줄
	Recursion({ start.row + currentLength * 2 , start.col }, { start.row + currentLength * 3 - 1,start.col + currentLength - 1 }, n - 1);;
	Recursion({ start.row + currentLength * 2 , start.col + currentLength }, { start.row + currentLength * 3 - 1, start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row + currentLength * 2, start.col + currentLength * 2 }, { start.row + currentLength * 3 - 1, start.col + currentLength * 3 - 1 }, n - 1);

}