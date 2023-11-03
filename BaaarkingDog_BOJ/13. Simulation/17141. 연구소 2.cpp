#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

//¸Ê : NxN
//¹ÙÀÌ·¯½º : M°³
//½Â¿øÀÌÀÇ ½ÅÈ£ : Start

//0: ºóÄ­
//1: º®
//2: ¹ÙÀÌ·¯½º ³õÀ» ¼ö ÀÖ´Â ºóÄ­

struct pos {
	int row;
	int col;
};

const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

int N, M;
int Map[51][51] = { 0, };
int Answer = 10000;
vector<pos> Candi;

void BFS(vector<pos> start) {

	int Distance[51][51] = { 0, };
	int maxDist = 0;
	if (M != start.size()) {
		int debugging = -1;
	}

	queue<pos> q;
	for (int i = 0; i < M; i++) {
		q.push(start[i]);
		Distance[start[i].row][start[i].col] = 1;
	}

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		//if (Distance[nowRow][nowCol] >= Answer) break;
		//maxDist = max(maxDist, Distance[nowRow][nowCol] - 1);
		for (int dir = 0; dir < 4; dir++) {
			int next_r = nowRow + dr[dir];
			int next_c = nowCol + dc[dir];

			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= N) continue;
			if (Map[next_r][next_c] == 1) continue;
			if (Distance[next_r][next_c] != 0) continue;
			Distance[next_r][next_c] = Distance[nowRow][nowCol] + 1;
			q.push({ next_r, next_c });
		}
	}
	bool flag = true;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Distance[i][j] == 0 && Map[i][j] != 1) {
				flag = false;
				break;
			}
			maxDist = max(maxDist, Distance[i][j] - 1);
		}
	}
	if (flag) Answer = min(Answer, maxDist);
}


void DFS(int index, int depth, vector<pos> temp) {
	if (depth == M) {

		BFS(temp);
		int debugging = -1;
		return;
	}

	for (int i = index; i < Candi.size(); i++) {
		temp.push_back(Candi[i]);
		DFS(i + 1, depth + 1, temp);
		temp.pop_back();
	}
}


void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 2) {
				Candi.push_back({ i,j });
			}
		}
	}
}

void solution() {
	vector<pos> t;
	DFS(0, 0, t);

	if (Answer == 10000) cout << "-1";
	else cout << Answer;
}


int main() {

	input();
	solution();

	return 0;
}

