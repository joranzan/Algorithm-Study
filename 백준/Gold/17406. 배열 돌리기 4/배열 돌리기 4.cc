#include<iostream>
#include<algorithm>

using namespace std;



struct rotateinfo {
	int row;
	int col;
	int offset;
};

int N, M, K;
int InputMap[51][51] = { 0, };  //2500
rotateinfo RotateInfo[6];    // 6! = 6 x 5 x 4 x 3 x 2 x 1 = 720가지의 순서
bool RotateUsed[6] = { false, };
int Answer = 2112345678;

void init() {
	cin >> N >> M;
	cin >> K;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			cin >> InputMap[r][c];
		}
	}

	for (int i = 0; i < K; i++) {
		int r, c, s;
		cin >> r >> c >> s;
		RotateInfo[i] = { r,c,s };
	}
}

int getMinValue() {

	int ret = 2112345678;

	for (int r = 1; r <= N; r++) {
		int score = 0;
		for (int c = 1; c <= M; c++) {
			score += InputMap[r][c];
		}
		ret = min(ret, score);
	}
	return ret;
}

void rotateArr(rotateinfo input) {

	int startRow = input.row - input.offset;
	int startCol = input.col - input.offset;
	int endRow = input.row + input.offset;
	int endCol = input.col + input.offset;

	while (!(startRow == endRow && startCol == endCol)) {

		//회전 로직 여기에 추가

		int temp1 = InputMap[startRow][endCol];

		for (int c = endCol; c >= startCol + 1; c--) {
			InputMap[startRow][c] = InputMap[startRow][c - 1];
		}

		int temp2 = InputMap[endRow][endCol];

		for (int r = endRow; r >= startRow + 2; r--) {
			InputMap[r][endCol] = InputMap[r - 1][endCol];
		}

		InputMap[startRow + 1][endCol] = temp1;


		int temp3 = InputMap[endRow][startCol];

		for (int c = startCol; c <= endCol - 2; c++) {
			InputMap[endRow][c] = InputMap[endRow][c + 1];
		}

		InputMap[endRow][endCol - 1] = temp2;


		
		for (int r = startRow; r <= endRow - 2; r++) {
			InputMap[r][startCol] = InputMap[r + 1][startCol];
		}
		InputMap[endRow - 1][startCol] = temp3;



		//기준점 갱신
		startRow += 1;
		startCol += 1;
		endRow -= 1;
		endCol -= 1;
	}

}

void recursion(int depth) {

	//모두 회전했다면
	if (depth >= K) {
		int ret = getMinValue();
		Answer = min(Answer, ret);
		return;
	}

	int tempMap[51][51] = { 0, };

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			tempMap[r][c] = InputMap[r][c];
		}
	}

	for (int i = 0; i < K; i++) {
		if (RotateUsed[i]) continue;
		RotateUsed[i] = true;

		rotateArr(RotateInfo[i]);

		recursion(depth + 1);

		RotateUsed[i] = false;

		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= M; c++) {
				InputMap[r][c] = tempMap[r][c];
			}
		}
	}

}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	recursion(0);

	cout << Answer;


	return 0;
}