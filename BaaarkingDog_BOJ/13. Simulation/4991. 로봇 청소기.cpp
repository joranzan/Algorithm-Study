#include<iostream>
#include<vector>
#include<queue>

using namespace std;


//로봇 청소기 
// 더러운 칸 -> 깨끗하게
//가구 이동 불가
//같은 칸 여러번 가능
// 필요한 이동 횟수

//10! 362880

struct pos {
	int row;
	int col;
};
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
int W, H;
char Map[20][20];
int Answer = 2112345678;
int DAT[11][11] = { 0, };
int Visited[11] = { 0, };
int startRow, startCol;
vector<pos> Dirty;


void BFS(int start_r, int start_c, int num) {

	int Distance[20][20] = { 0, };

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
			if (nextRow < 0 || nextCol < 0 || nextRow >= H || nextCol >= W) continue;
			if (Map[nextRow][nextCol] == 'x') continue;
			if (Distance[nextRow][nextCol] != 0) continue;
			Distance[nextRow][nextCol] = Distance[nowRow][nowCol] + 1;
			q.push({ nextRow,nextCol });
		}
	}

	DAT[num][0] = Distance[startRow][startCol];
	for (int i = 0; i < Dirty.size(); i++) {
		int r = Dirty[i].row;
		int c = Dirty[i].col;
		DAT[num][i + 1] = Distance[r][c] - 1;
	}



}


void DFS(int now, int sum, int depth) {
	if (depth == Dirty.size()) {
		Answer = min(Answer, sum);
		return;
	}

	for (int i = 0; i < Dirty.size(); i++) {
		if (Visited[i + 1] == 1) continue;
		Visited[i + 1] = 1;
		DFS(i + 1, sum + DAT[now][i + 1], depth + 1);
		Visited[i + 1] = 0;
	}
}

int simulation() {

	BFS(startRow, startCol, 0);
	for (int i = 1; i <= Dirty.size(); i++) {
		if (DAT[0][i] <= 0) return -1;
	}

	for (int i = 0; i < Dirty.size(); i++) {
		BFS(Dirty[i].row, Dirty[i].col, i + 1);
	}

	Visited[0] = 1;
	DFS(0, 0, 0);

	return Answer;

}

void input() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 'o') {
				startRow = i;
				startCol = j;
			}
			else if (Map[i][j] == '*') {
				Dirty.push_back({ i,j });
			}
		}
	}
}


void init() {
	Answer = 2112345678;
	Dirty.clear();
	for (int i = 0; i < 11; i++) {
		Visited[i] = 0;
		for (int j = 0; j < 11; j++) {
			DAT[i][j] = -1;
		}
	}
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (1) {
		cin >> W >> H;
		if (W == 0 && H == 0) break;
		init();
		input();
		cout << simulation() << "\n";

	}


	return 0;
}