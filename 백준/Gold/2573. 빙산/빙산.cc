#include<iostream>
#include<queue>

using namespace std;

struct pos {
	int row;
	int col;
};

int N, M;
int Map[301][301] = { 0, };
int tempMap[301][301] = { 0, };
int Visited[301][301] = { 0, };
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

void BFS(pos start) {

	queue<pos> q;
	Visited[start.row][start.col] = 1;
	q.push(start);

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M) continue;
			if (Map[nextRow][nextCol] == 0) continue;
			if (Visited[nextRow][nextCol] == 1) continue;
			Visited[nextRow][nextCol] = 1;
			q.push({ nextRow, nextCol });
		}
	}

}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> Map[r][c];
		}
	}


	int year = 0;

	while (1) {
		
		year++;

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				tempMap[r][c] = Map[r][c];
				Visited[r][c] = 0;
			}
		}

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (Map[r][c] == 0) continue;
				int cnt = 0;
				for (int dir = 0; dir < 4; dir++) {
					int nextRow = r + dr[dir];
					int nextCol = c + dc[dir];
					if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M) continue;
					if (Map[nextRow][nextCol] == 0) cnt++;
				}

				tempMap[r][c] = Map[r][c] - cnt;
			}
		}


		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				Map[r][c] = tempMap[r][c];
				if (Map[r][c] < 0) Map[r][c] = 0;
			}
		}

		bool iszero = true;
		int glacierCnt = 0;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (Map[r][c] == 0) continue;
				iszero = false;
				if (Visited[r][c] == 1) continue;
				BFS({ r,c });
				glacierCnt++;
				if (glacierCnt >= 2) break;
			}
			if (glacierCnt >= 2) break;
		}



		if (iszero) {
			cout << "0";
			break;
		}
		if (glacierCnt >= 2) {
			cout << year;
			break;
		}
	}


	return 0;
}


/*
문제 분석

0: 바다
양수 : 빙산 높이

상하좌우 접한 빙산 개수만큼 높이 줄어듬
0까지 가면 바다로 바뀜

2덩어리 이상으로 분리되는 최초 시간 구하기

다 녹았는데 2덩어리 이상 안되면 0 출력


*/