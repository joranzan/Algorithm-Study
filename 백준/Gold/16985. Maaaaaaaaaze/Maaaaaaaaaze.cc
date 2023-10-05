#include<iostream>
#include<queue>

using namespace std;

//3차원 미로
//5x5x5
//하얀색 : 들어갈 수 있음
//검은색 : 들어갈 수 없음

//rotation 가능 (시계 or 반시계)

//출발 0,0,0   도착 4,4,4   입구,출구 막혀있으면 탈출 불가

//가장 적은 이동횟수로 탈출한 사람이 우승  //BFS

struct pos {
	int height;
	int row;
	int col;
};

int originMap[5][5][5] = { 0, };
int tempMap[5][5][5] = { 0, };
int Answer = 1000;

//미로 탈출 함수
int BFS() {
	int distance[5][5][5] = { 0, };
	queue<pos> q;
	q.push({ 0,0,0 });
	distance[0][0][0] = 1;

	int dh[6] = { -1,1,0,0,0,0};
	int dr[6] = { 0,0,-1,1,0,0 };
	int dc[6] = { 0,0,0,0,-1,1 };

	while (!q.empty()) {

		pos Now = q.front();
		q.pop();

		if (Now.height == 4 && Now.row == 4 && Now.col == 4) break;

		for (int dir = 0; dir < 6; dir++) {
			int next_h = Now.height + dh[dir];
			int next_r = Now.row + dr[dir];
			int next_c = Now.col + dc[dir];
			if (next_h < 0 || next_r < 0 || next_c < 0 || next_h >= 5 || next_r >= 5 || next_c >= 5) continue;
			if (tempMap[next_h][next_r][next_c] == 0) continue;
			if (distance[next_h][next_r][next_c] != 0) continue;
			if (distance[Now.height][Now.row][Now.col] + 1 > Answer) continue;
			distance[next_h][next_r][next_c] = distance[Now.height][Now.row][Now.col] + 1;
			q.push({ next_h,next_r,next_c });
		}
	}

	int ret = distance[4][4][4];
	if (ret <= 0) return 1000;
	else return ret-1;
}

//rotation 함수 -> 한방향으로만 돌리면서 DFS
void Rotation(int nowFloor) {
	int tempRotate[5][5] = { 0, };

	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 5; c++) {
			tempRotate[c][4 - r] = tempMap[nowFloor][r][c];
		}
	}

	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 5; c++) {
			tempMap[nowFloor][r][c] = tempRotate[r][c];
		}
	}
}


//DFS -> depth: 현재 층
void DFS(int depth) {
	if (depth >= 5) {

		//입구, 출구 막혔는지 확인 (막혔으면 return)
		if (tempMap[0][0][0] == 0 || tempMap[4][4][4] == 0) return;
		//미로찾기 BFS 시작
		Answer = min(Answer, BFS());
		return;
	}

	for (int i = 0; i < 4; i++) {
		Rotation(depth);
		DFS(depth + 1);
	}

}


//판 쌓는 함수 (DFS로 바로 쌓기)
int used_floor[5] = { 0, };   //층에 이미 판 채웠는지
void Stacking(int depth) {
	if (depth >= 5) {

		//DFS로 넘어가기
		DFS(0);

		return;
	}
	for (int i = 0; i < 5; i++) {
		if (used_floor[i] == 1) continue;
		used_floor[i] = 1;
		//해당 판 tempMap배열에 넣기
		for (int r = 0; r < 5; r++) {
			for (int c = 0; c < 5; c++) {
				tempMap[i][r][c] = originMap[depth][r][c];
			}
		}
		//다음 판 쌓으러가기
		Stacking(depth + 1);

		used_floor[i] = 0;
	}

}



void input() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				cin >> originMap[i][j][k];
			}
		}
	}
}

void solution() {

	Stacking(0);
	if (Answer >= 1000) cout << "-1";
	else cout << Answer << "\n";
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

//시간복잡도
//판 5개 쌓는 순서 : 120
//4바퀴씩 5판 : 4^5 = 256 x 4 = 1024
//125개 탐색



