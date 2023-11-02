#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

//문제 분석
//맵: NxM
//최단 경로 (시작칸과 끝칸 포함)

//벽 1개까지 부술 수 있음

struct pos {
	int row;
	int col;
};

//상하좌우
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

vector<pos> wall;

int Map[1001][1001] = { 0, };
int DAT[1001][1001] = { 0, };
int DAT2[1001][1001] = { 0, };
int Distance[1001][1001] = { 0, };
int Path = 2000000;
int N, M;
//0개 부술때 최단 거리
void BFS0(int start_r, int start_c) {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			Distance[i][j] = 2000000;
		}
	}
	queue<pos> q;
	q.push({ start_r,start_c });
	Distance[start_r][start_c] = 1;

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {

			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nowCol > M) continue;
			if (Map[nextRow][nextCol] == 1) {
				if (DAT[nextRow][nextCol] == 0) {
					DAT[nextRow][nextCol] = Distance[nowRow][nowCol] + 1;
				}
				continue;
			}
			if (Distance[nextRow][nextCol] != 2000000) continue;
			Distance[nextRow][nextCol] = Distance[nowRow][nowCol] + 1;
			q.push({ nextRow,nextCol });
		}
	}
	Path = min(Path, Distance[N][M]);
}



void BFS1(int start_r, int start_c, int target_r, int target_c) {

	

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			Distance[i][j] = 2000000;
		}
	}
	queue<pos> q;
	q.push({ start_r,start_c });
	Distance[start_r][start_c] = 1;

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {

			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nowCol > M) continue;
			if (Map[nextRow][nextCol] == 1) {
				if (DAT[nextRow][nextCol] != 0&&DAT2[nextRow][nextCol]==0) {
					DAT2[nextRow][nextCol] = Distance[nowRow][nowCol];
				}
				continue;
			}
			if (Distance[nextRow][nextCol] != 2000000) continue;
			Distance[nextRow][nextCol] = Distance[nowRow][nowCol] + 1;
			q.push({ nextRow,nextCol });
		}
	}

}

void input() {
	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		string s;
		cin >> s;
		for (int j = 1; j <= M; j++) {
			Map[i][j] = s[j - 1] - '0';
			if (Map[i][j] == 1) {
				wall.push_back({ i,j });
			}
		}
	}
}

void solution() {

	BFS0(1, 1);
	BFS1(N, M, 1, 1);
	for (int i = 0; i < wall.size(); i++) {
		int destroy_r = wall[i].row;
		int destroy_c = wall[i].col;
		if (DAT[destroy_r][destroy_c] == 0 || DAT2[destroy_r][destroy_c] == 0) continue;
		Path = min(Path, DAT[destroy_r][destroy_c] + DAT2[destroy_r][destroy_c]);
	}

	if (Path == 2000000) cout << "-1";
	else cout << Path;
}


int main() {

	input();
	solution();

	return 0;
}