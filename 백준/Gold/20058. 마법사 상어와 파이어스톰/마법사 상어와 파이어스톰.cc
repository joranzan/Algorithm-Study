#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

void input();

//시계방향 rotation

struct pos {
	int row;
	int col;
};
vector<int> Query;
int Map[65][65] = { 0, };
int Temp[65][65] = { 0, };
int Visited[65][65] = { 0, };
int N, Q;
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

int Sum = 0;

void iceBreaking() {



	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] == 0) {
				Temp[i][j] = 0;
				continue;
			}
			int cnt = 0;
			for (int dir = 0; dir < 4; dir++) {
				int nextRow = i + dr[dir];
				int nextCol = j + dc[dir];
				if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) continue;
				if (Map[nextRow][nextCol] == 0) continue;
				cnt++;
			}
			if (cnt >= 3) Temp[i][j] = Map[i][j];
			else if (cnt < 3) Temp[i][j] = Map[i][j] - 1;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Map[i][j] = Temp[i][j];
		}
	}
}

void Rotation(int row, int col, int nowSize) {

	for (int i = 0; i < nowSize; i++) {
		for (int j = 0; j < nowSize; j++) {
			int nowRow = row + i;
			int nowCol = col + j;
			Temp[nowRow][nowCol] = Map[nowRow][nowCol];
		}
	}

	for (int i = 0; i < nowSize; i++) {
		for (int j = 0; j < nowSize; j++) {
			int nowRow = row + i;
			int nowCol = col + j;
			Map[row + j][col + nowSize -1 - i] = Temp[nowRow][nowCol];
			
		}
	}

	int debugging = -1;

}


int BFS(int row, int col) {
	int cnt = 0;

	queue<pos> q;
	q.push({ row,col });

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		Sum += Map[nowRow][nowCol];
		cnt++;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextRow = nowRow + dr[i];
			int nextCol = nowCol + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) continue;
			if (Visited[nextRow][nextCol] == 1) continue;
			if (Map[nextRow][nextCol] <= 0) continue;
			Visited[nextRow][nextCol] = 1;
			q.push({ nextRow,nextCol });
		}
	}

	return cnt;
}

void findAnswer() {


	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] <= 0) continue;
			if (Visited[i][j] == 1) continue;
			Visited[i][j] = 1;
			cnt = max(cnt,BFS(i, j));
		}
	}

	cout << Sum << "\n" << cnt;

}

void solution() {
	for (int i = 0; i < Q; i++) {

		if (Query[i] != 0) {
			int nowSize = int(pow(2, Query[i]));
			int divCnt = N / nowSize;

			for (int r = 0; r < divCnt; r++) {
				for (int c = 0; c < divCnt; c++) {
					int nowRow = 0 + r * nowSize;
					int nowCol = 0 + c * nowSize;
					Rotation(nowRow, nowCol, nowSize);
				}
			}
		}
		iceBreaking();
	}

	findAnswer();

	int debugging = -1;
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}


void input() {

	cin >> N >> Q;

	N = int(pow(2, N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
		}
	}

	for (int i = 0; i < Q; i++) {
		int L;
		cin >> L;
		Query.push_back(L);
	}
}