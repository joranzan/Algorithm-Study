#include<iostream>
#include<queue>

using namespace std;


int Answer = 2112345678;

struct pos {
	int cost;
	int row;
	int col;
	int dir;
	bool operator<(pos next) const {
		if (cost < next.cost) return false;
		if (cost > next.cost) return true;
		return false;
	}
};

int H, W;
char Map[101][101];
int start_r, start_c;
int target_r, target_c;

void dijkstra(int start_dir) {

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };
	int distance[101][101] = { 0, };

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			distance[i][j] = 2112345678;
		}
	}

	distance[start_r][start_c] = 0;
	priority_queue<pos> pq;
	pq.push({ 0, start_r, start_c, start_dir });


	while (!pq.empty()) {
		int nowCost = pq.top().cost;
		int nowRow = pq.top().row;
		int nowCol = pq.top().col;
		int nowDir = pq.top().dir;
		pq.pop();

		if (nowCost > distance[nowRow][nowCol]) continue;

		for (int i = 0; i < 4; i++) {
			int next_r = nowRow + dr[i];
			int next_c = nowCol + dc[i];
			if (next_r < 0 || next_c < 0 || next_r >= H || next_c >= W) continue;
			if (Map[next_r][next_c] == '*') continue;
			int next_cost = 0;

			if (nowDir == i) {
				next_cost = 0;
			}
			else {
				next_cost++;
			}
			if (distance[next_r][next_c] <= distance[nowRow][nowCol] + next_cost) continue;
			distance[next_r][next_c] = distance[nowRow][nowCol] + next_cost;
			pq.push({ distance[next_r][next_c], next_r, next_c, i });
		}
	}

	int debugging = -1;
	Answer = min(Answer, distance[target_r][target_c]);
}

void input() {

	int inputCnt = 0;
	cin >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 'C') {
				if (inputCnt == 0) {
					start_r = i;
					start_c = j;
					inputCnt++;
				}
				else if (inputCnt == 1) {
					target_r = i;
					target_c = j;
				}
			}
		}
	}
}

void solution() {
	for (int i = 0; i < 4; i++) {
		dijkstra(i);
	}

	cout << Answer << "\n";
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	input();
	solution();


	return 0;
}