#include<iostream>
#include<vector>

using namespace std;
//시계방향
// 0
//3 1
// 2

//CCTV 5가지 종류
//1번: 1
//2번: 1 3     //2번 회전    
//3번: 0 1
//4번: 0 1 3
//5번: 0 1 2 3  //안돌려도 됨

struct pos {
	int row;
	int col;
	int info;
};

int N, M;
int Map[8][8] = { 0, }; 
int Result[8][8] = { 0, }; //CCTV가 바라보는 곳 1로 바꾸기
int Answer = 2112345678;
vector<pos> CCTV;   //CCTV 좌표
void FloodFill(int row, int col, int dir);


int Rotation[6][7] = {  // 0 1 2 3 0 1 2
	{0,0,0,0,0,0,0},
	{0,1,0,0,0,1,0},
	{0,1,0,1,0,1,0},  //사실 1만큼만 돌리면 됨
	{1,1,0,0,1,1,0},
	{1,1,0,1,1,1,0},
	{1,1,1,1,0,0,0}   //안돌려도 됨
};
//상 우 하 좌
const int dr[4] = { -1,0,1,0 };
const int dc[4] = { 0,1,0,-1 };

//BackTracking
void BackTracking(int depth) {

	if (depth >= CCTV.size()) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (Result[i][j] == 0) cnt++;
			}
		}
		Answer = min(Answer, cnt);
		return;
	}

	int cctvNum = CCTV[depth].info;
	int nowRow = CCTV[depth].row;
	int nowCol = CCTV[depth].col;

	int Result_temp[8][8] = { 0, };  //원래 Result값 담아두는 배열

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Result_temp[i][j] = Result[i][j];
		}
	}

	if (cctvNum == 2) {  //1만큼만 돌리기
		for (int i = 0; i < 2; i++) {
			for (int dir = i; dir < i + 4; dir++) { //네바퀴 돌리기
				if (Rotation[cctvNum][dir] == 0) continue;

				//해당 방향 채우는 함수
				FloodFill(nowRow, nowCol, dir - i);
			}
			BackTracking(depth + 1);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					Result[i][j] = Result_temp[i][j];
				}
			}
		}
	}
	else if (cctvNum == 5) { //안돌려도됨
		for (int dir = 0; dir < 4; dir++) { //네바퀴 돌리기
			if (Rotation[cctvNum][dir] == 0) continue;

			//해당 방향 채우는 함수
			FloodFill(nowRow, nowCol, dir);
		}
		BackTracking(depth + 1);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				Result[i][j] = Result_temp[i][j];
			}
		}
	}
	else { //네바퀴 다 돌려야함
		for (int i = 0; i < 4; i++) {
			for (int dir = i; dir < i + 4; dir++) { //네바퀴 돌리기
				if (Rotation[cctvNum][dir] == 0) continue;
				
				//해당 방향 채우는 함수
				FloodFill(nowRow, nowCol, dir - i);
			}
			BackTracking(depth + 1);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					Result[i][j] = Result_temp[i][j];
				}
			}
		 }
	}
}

void FloodFill(int row, int col, int dir) {

	int nowRow = row;
	int nowCol = col;
	while (1) {

		int nextRow = nowRow + dr[dir];
		int nextCol = nowCol + dc[dir];
		if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M) break;
		if (Map[nextRow][nextCol] == 6) break;
		Result[nextRow][nextCol] = 1;
		nowRow = nextRow;
		nowCol = nextCol;
	}
}


int main() {


	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] >= 1 && Map[i][j] <= 5) {
				CCTV.push_back({ i,j, Map[i][j]});
				Result[i][j] = 1;
			}
			else if (Map[i][j] == 6) {
				Result[i][j] = -1;
			}
		}
	}

	BackTracking(0);
	cout << Answer;

	return 0;
}