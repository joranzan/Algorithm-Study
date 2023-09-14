#include<iostream>

using namespace std;

int N;
bool ColVisited[16] = { false, }; //해당 열에 이미 퀸이 있는지 Check
bool LeftDiagVisited[35] = { false, }; //좌하 Check
bool RightDiagVisited[35] = { false, }; //우하 Check
int cnt = 0;

void BackTracking(int nowRow) {  

	if (nowRow >= N) {
		cnt++;
		return;
	}

	for (int i = 0; i < N; i++) {  //해당 nowRow에 놓을 수 있는 자리 다 탐색

		int nextRow = nowRow; //애초에 0번째 Row부터 시작
		int nextCol = i;
		int leftDiag = nextRow + nextCol;
		int rightDiag = N - 1 - (nextRow - nextCol);
		//어차피 Map 벗어날 일 없음
		if (ColVisited[i]) continue; //Col check
		if (LeftDiagVisited[leftDiag]) continue; //좌하 Check
		if (RightDiagVisited[rightDiag]) continue; //우하 Check
		
		ColVisited[i] = true;
		LeftDiagVisited[leftDiag] = true;
		RightDiagVisited[rightDiag] = true;
		
		BackTracking(nowRow + 1);
		//다시 원상복귀
		ColVisited[i] = false;
		LeftDiagVisited[leftDiag] = false;
		RightDiagVisited[rightDiag] = false;

	}

}

int main() {

	cin >> N;

	BackTracking(0);

	cout << cnt;

	return 0;
}

//설계

//row당 퀸 하나밖에 못놓음 -> 한 row씩 검색해 나가자

//BackTracking(int nowRow, int nowCol, )
//if(nowRow>=N) -> 마지막 row까지 다 놨으면 
//cnt++ , return 

//대각선 좌하 우하 계산
// 좌하
// row + col
// 우하
// row - col   4 3 2 1 0 -1 -2 -3 -4  -> N-1 -(row-col) 0 1 2 3 4 5 6 7 8
//아래 계산  
// col check