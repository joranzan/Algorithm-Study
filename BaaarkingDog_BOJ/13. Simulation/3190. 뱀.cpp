#include<iostream>
#include<queue>

using namespace std;

//문제 분석
//사과를 먹으면 뱀 길이가 늘어남
//자기 몸 또는 벽에 부딪히면 게임 종료


//게임 시작 조건
//(1,1)에서 시작, 길이: 1
//오른쪽을 향함

//게임 플레이
//1. 머리를 다음칸에 위치시킴
//2. 다음칸이 벽 또는 자기 몸이면 Game Over
//3. 움직인 칸에 사과가 있다면 사과는 없어지고 꼬리는 그대로
//4. 움직인 칸에 사과가 없다면 꼬리가 위치한 칸을 비움


//몇 초안에 게임이 끝나는지?

struct ChangeDir {
	int time;
	char c;
};
struct pos {
	int row;
	int col;
};

int N, K, L;
int Board[101][101] = { 0, };  //사과 1, 뱀 몸 : -1
queue<ChangeDir> query;  //방향 변환 정보 큐
// 상(0) 하(1) 좌(2) 우(3)
int nowDir = 3;
int nowTime = 0;
void input();

void direction(char c) {

	if (c == 'L') {  //반시계
		if (nowDir == 0) {
			nowDir = 2;
		}
		else if (nowDir == 1) {
			nowDir = 3;
		}
		else if (nowDir == 2) {
			nowDir = 1;
		}
		else if (nowDir == 3) {
			nowDir = 0;
		}
	}
	else if (c == 'D') { //시계
		if (nowDir == 0) {
			nowDir = 3;
		}
		else if (nowDir == 1) {
			nowDir = 2;
		}
		else if (nowDir == 2) {
			nowDir = 0;
		}
		else if (nowDir == 3) {
			nowDir = 1;
		}
	}

}

void Simulation() {

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };
	
	queue<pos> Snake;
	Snake.push({ 1,1 });
	int headRow = Snake.front().row;
	int headCol = Snake.front().col;
	while (1) {
						
		if (!query.empty()&&nowTime == query.front().time) {
			direction(query.front().c);
			query.pop();
		}

		int next_headRow = headRow + dr[nowDir];
		int next_headCol = headCol + dc[nowDir];
		nowTime++;
		if (next_headRow <= 0 || next_headCol <= 0 || next_headRow > N || next_headCol > N) break;
		if (Board[next_headRow][next_headCol] == -1) break;
		//사과 없는 경우
		else if (Board[next_headRow][next_headCol] == 0) {
			Snake.push({ next_headRow, next_headCol });
			Board[next_headRow][next_headCol] = -1;
			Board[Snake.front().row][Snake.front().col] = 0;
			Snake.pop();
			headRow = next_headRow;
			headCol = next_headCol;
		}
		//사과 있는 경우
		else if (Board[next_headRow][next_headCol] == 1) {
			Snake.push({ next_headRow, next_headCol });
			Board[next_headRow][next_headCol] = -1;
			headRow = next_headRow;
			headCol = next_headCol;
		}

	}

}


void solution() {
	Simulation();
	cout << nowTime << "\n";
}

int main() {

	input();
	solution();


	return 0;
}

//입력
//N(NxN)
//K(사과의 개수)
//사과의 위치 (행,열)
//L(방향 변환 횟수)
//X(게임시작하고 X초 지난 시점) C(L:시계반대, D: 시계)


void input() {
	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		int row, col;
		cin >> row >> col;
		Board[row][col] = 1;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int X;
		char C;
		cin >> X >> C;
		query.push({ X,C });
	}

}