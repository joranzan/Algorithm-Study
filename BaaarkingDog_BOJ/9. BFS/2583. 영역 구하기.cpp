#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int M, N, K;
int Map[101][101] = { 0, };
int Visited[101][101] = { 0, };

struct pos {
	int row;
	int col;
};


int BFS(int start_r, int start_c) {
	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	int area = 1;

	queue<pos> q;
	q.push({ start_r, start_c });
	Visited[start_r][start_c] = 1;

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow < 0 || nextCol < 0 || nextRow >= M || nextCol >= N) continue;
			if (Map[nextRow][nextCol] != 0) continue;
			if (Visited[nextRow][nextCol] != 0) continue;
			Visited[nextRow][nextCol] = 1;
			area++;
			q.push({ nextRow, nextCol });
		}
	}

	return area;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> M >> N >> K;

	for (int i = 0; i < K; i++) {
		int left_r, left_c, right_r, right_c;
		cin >> left_c >> left_r >> right_c >> right_r;

		for (int r = left_r; r < right_r; r++) {
			for (int c = left_c; c < right_c; c++) {
				Map[r][c] = 1;
			}
		}
	}

	vector<int> result;

	for (int r = 0; r < M; r++) {
		for (int c = 0; c < N; c++) {
			if (Map[r][c] != 0) continue;
			if (Visited[r][c] != 0) continue;
			result.push_back(BFS(r,c));
		}
	}

	sort(result.begin(), result.end());
	cout << result.size() << "\n";
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}

	return 0;
}