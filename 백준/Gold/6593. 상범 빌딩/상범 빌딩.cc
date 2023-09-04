#include<iostream>
#include<queue>

using namespace std;

//문제 분석
//이동
//금: 지나갈 수 없음   비어있음: 지나갈 수 있음
//상하좌우앞뒤 -> 3차원 배열 탐색

//입력
//금: #   빈칸: .   시작점: S   출구 : E

struct pos {
	int height;
	int row;
	int col;
};

int L, R, C;  //높이 행 열
char Map[30][30][30];
int Visited[30][30][30];
pos start;
pos target;

void init() {

	for (int i = 0; i < L; i++) {
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < C; k++) {
				Visited[i][j][k] = 0;
			}
		}
	}
}
void input() {
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < C; k++) {
				cin >> Map[i][j][k];
				if (Map[i][j][k] == 'S') {
					start = { i,j,k };
				}
				else if (Map[i][j][k] == 'E') {
					target = { i,j,k };
				}
			}
		}
	}
}
//마지막에 Visited에서 1빼고 출력
int BFS() {
	queue<pos> q;
	q.push(start);
	Visited[start.height][start.row][start.col] = 1;

	const int dh[6] = { -1,1,0,0,0,0 };
	const int dr[6] = { 0,0,-1,1,0,0 };
	const int dc[6] = { 0,0,0,0,-1,1 };

	while (!q.empty()) {
		pos now = q.front();
		q.pop();

		int now_h = now.height;
		int now_r = now.row;
		int now_c = now.col;

		if (Map[now_h][now_r][now_c] == 'E') {
			return Visited[now_h][now_r][now_c] - 1;
		}

		for (int i = 0; i < 6; i++) {
			int next_h = now_h + dh[i];
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			if (next_h < 0 || next_h >= L) continue;
			if (next_r < 0 || next_r >= R) continue;
			if (next_c < 0 || next_c >= C) continue;
			if (Visited[next_h][next_r][next_c] != 0) continue;
			if (Map[next_h][next_r][next_c] == '#') continue;
			Visited[next_h][next_r][next_c] = Visited[now_h][now_r][now_c] + 1;
			q.push({ next_h, next_r, next_c });
		}
	}


	return -1;
}




int main() {

	
	while (1) {
		cin >> L >> R >> C;
		if (L == 0 && R == 0 && C == 0) break;
		init();
		input();
		int ans = BFS();
		if (ans < 0) {
			cout << "Trapped!" << "\n";
		}
		else {
			cout << "Escaped in " << ans << " minute(s).\n";
		}
	}


	return 0;
}