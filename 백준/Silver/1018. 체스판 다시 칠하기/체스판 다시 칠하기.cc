#include<iostream>
#include<queue>

using namespace std;

//문제분석
//8x8 어떻게 할지 -> 완전탐색
//정사각형 하나 고른 뒤 -> 왼쪽 위 흰, 검 두가지 경우 돌리기 (BFS
//

struct pos {
	int row;
	int col;
};

int N, M;
char Map[50][50];
char DAT[3] = { ' ', 'B','W' };

int BFS(pos start, pos end, int start_index) {

	int cnt = 0;
	queue<pos> q;
	int Visited[50][50] = { 0, };
	q.push({ start.row,start.col });
	Visited[start.row][start.col] = start_index;
	if (Map[start.row][start.col] != DAT[start_index]) cnt++;

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	while (!q.empty()) {

		int now_r = q.front().row;
		int now_c = q.front().col;
		char now_value = Visited[now_r][now_c];
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int next_r = now_r + dr[dir];  //2
			int next_c = now_c + dc[dir];  //0
			if (next_r<start.row || next_c<start.col|| next_r>end.row || next_c>end.col) continue;
			if (Visited[next_r][next_c] != 0) continue;
			if (Map[next_r][next_c] == DAT[now_value]) {
				if (now_value == 1) {
					Visited[next_r][next_c] = 2;
					cnt++;
				}
				else if(now_value==2) {
					Visited[next_r][next_c] = 1;
					cnt++;
				}
			}
			else {
				if (Map[next_r][next_c] == 'B') {
					Visited[next_r][next_c] = 1;
				}
				else if (Map[next_r][next_c] == 'W') {
					Visited[next_r][next_c] = 2;
				}
			}
			q.push({ next_r,next_c });
		}
	}
	if (cnt == 28) {
		int de = -1;
	}
	return cnt;
}

int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
		}
	}

	int Answer = 3000;

	for (int i = 0; i <= N - 8; i++) {
		for (int j = 0; j <= M - 8; j++) {
			if (i == 1 && j == 0) {
				int de = -1;
			}
			Answer = min(Answer, BFS({ i,j }, { i + 7,j + 7 }, 1));
			Answer = min(Answer, BFS({ i,j }, { i + 7,j + 7 }, 2));
		}
	}

	cout << Answer;

	return 0;
}