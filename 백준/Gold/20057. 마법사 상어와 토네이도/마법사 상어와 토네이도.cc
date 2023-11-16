#include<iostream>

using namespace std;


//문제 분석
// 
// NxN 맵
// 
//토네이도 : 가운데 시작

//모래 날림
//토네이도 이동 -> 이동 방향으로 다음칸의 모래가 날라감

struct tornado {
	int row;
	int col;
	int dir;
};

int N;
int Map[500][500] = { 0, };
const int oppdir[4] = { 1,0,3,2 };
const int dr4[4] = { -1,1,0,0 };
const int dc4[4] = { 0,0,-1,1 };
const int dr8[8] = { -1,-1,0,1,1,1,0,-1 };
const int dc8[8] = { 0,1,1,1,0,-1,-1,-1 };
const double percent[4][8] = {
	{0.00,0.10,0.07,0.01,0.00,0.01,0.07,0.10},   //상 방향으로 들어올 때
	{0.00,0.01,0.07,0.10,0.00,0.10,0.07,0.01},   //하 방향으로 들어올 때
	{0.07,0.01,0.00,0.01,0.07,0.10,0.00,0.10},   //좌 방향으로 들어올 때
	{0.07,0.10,0.00,0.10,0.07,0.01,0.00,0.01}    //우 방향으로 들어올 때
};

tornado Tornado;
int OutSand = 0;
int DAT[500][500];

void moveSand() {
	
	//토네이도 상태
	int TDir = Tornado.dir;
	int TRow = Tornado.row;
	int TCol = Tornado.col;

	//날아가는 모래의 위치
	int nowRow = TRow;
	int nowCol = TCol;

	int nowValue = Map[nowRow][nowCol];
	int remainValue = nowValue;

	if (nowValue == 0) return;

	Map[nowRow][nowCol] = 0;

	for (int i = 0; i < 8; i++) {
		int nextValue = int(nowValue * percent[TDir][i]);
		if (nextValue == 0) continue;
		int nextRow = nowRow + dr8[i];
		int nextCol = nowCol + dc8[i];

		if (nextRow < 0 || nextCol<0 || nextRow >= N || nextCol >= N) {
			OutSand += nextValue;
			remainValue -= nextValue;
			continue;
		}
		Map[nextRow][nextCol] += nextValue;
		remainValue -= nextValue;
	}
	
	int nowDir = TDir;
	int oppDir = oppdir[TDir];

	for (int i = 0; i < 4; i++) {
		if (i == oppDir) continue;
		int nextRow = nowRow + dr4[i] * 2;
		int nextCol = nowCol + dc4[i] * 2;
		double p = 0.02;
		if (i == TDir) p = 0.05;
		int nextValue = int(nowValue * p);
		if (nextValue == 0) continue;

		if (nextRow < 0 || nextCol<0 || nextRow >= N || nextCol >= N) {
			OutSand += nextValue;
			remainValue -= nextValue;
			continue;
		}

		Map[nextRow][nextCol] += nextValue;
		remainValue -= nextValue;
	}

	int finalRow = nowRow + dr4[TDir];
	int finalCol = nowCol + dc4[TDir];
	if (finalRow < 0 || finalCol<0 || finalRow >= N || finalCol >= N) {
		OutSand += remainValue;
	}
	else {
		Map[finalRow][finalCol] += remainValue;
	}

}


void InitSetting(int nowRow, int nowCol, int dir, int num){
	int d_r = dr8[dir];
	int d_c = dc8[dir];
	//좌상 꼭지점
	while (1) {
		DAT[nowRow][nowCol] = num;
		nowRow += d_r;
		nowCol += d_c;
		if (nowRow < 0 || nowCol<0 || nowRow >= N || nowCol >= N) break;
	}
}


//토네이도 이동 : 대각선 값으로

void moveTornado() {
	
	int nowRow = N / 2;
	int nowCol = N / 2;
	int nowDir = 2;

	while (1) {

		nowRow += dr4[nowDir];
		nowCol += dc4[nowDir];

		Tornado.row = nowRow;
		Tornado.col = nowCol;
		Tornado.dir = nowDir;

		moveSand();
		
		if (DAT[nowRow][nowCol] != 0) {
			nowDir = DAT[nowRow][nowCol] - 1;
		}

		if (nowRow == 0 && nowCol == 0) break;

	}

}



void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
		}
	}
}


void solution() {
	//좌상
	InitSetting(N / 2, N / 2 - 1, 7, 2);
	//우상
	InitSetting(N / 2, N / 2, 1, 3);
	//좌하
	InitSetting(N / 2, N / 2, 5, 4);
	//우하
	InitSetting(N / 2, N / 2, 3, 1);
	DAT[N / 2][N / 2] = 0;

	//방향 -1 해서 가기

	moveTornado();

	int debugging = -1;

	cout << OutSand;

}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}