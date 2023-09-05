#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//문제 분석

//이동
//벽 통과 X
//불 옮겨질 칸, 불 붙으려는 칸 이동 못함

//얼마나 빨리 탈출 가능?

//시간복잡도: 테케당 100만
struct pos {
	int row;
	int col;
};

int W, H;
char Map[1000][1000];
int Visited[1000][1000] = { 0, };
vector<pos> fire;
vector<pos> sk;


const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

void init() {
	fire.clear();
	sk.clear();
}

void input() {

	cin >> W >> H;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Map[i][j];
			Visited[i][j] = 0;
			if (Map[i][j] == '@') {
				sk.push_back({ i,j });
				Visited[i][j] = 1;
			}
			else if (Map[i][j] == '*') {
				fire.push_back({ i,j });
			}
		}
	}
}

void BFS_Fire() {
	queue<pos> q_fire;
	//fire에 있는 애들 꺼내서 퍼뜨린 후
	for (int i = 0; i < fire.size(); i++) {
		q_fire.push(fire[i]);
	}
	fire.clear();

	while (!q_fire.empty()) {
		int now_r = q_fire.front().row;
		int now_c = q_fire.front().col;
		q_fire.pop();

		for (int i = 0; i < 4; i++) {
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			if (next_r < 0 || next_c < 0 || next_r >= H || next_c >= W) continue;
			if (Map[next_r][next_c] == '#') continue;
			if (Map[next_r][next_c] == '*') continue;
			Map[next_r][next_c] = '*';
			fire.push_back({ next_r,next_c });
		}
	}
}

void BFS() {

	queue<pos> q;
	//fire에 있는 애들 꺼내서 퍼뜨린 후
	for (int i = 0; i < sk.size(); i++) {
		q.push(sk[i]);
	}
	sk.clear();

	while (!q.empty()) {
		int now_r = q.front().row;
		int now_c = q.front().col;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			if (next_r < 0 || next_c < 0 || next_r >= H || next_c >= W) continue;
			if (Map[next_r][next_c] == '#') continue;
			if (Map[next_r][next_c] == '*') continue;
			if (Visited[next_r][next_c] != 0) continue;
			Visited[next_r][next_c] = Visited[now_r][now_c] + 1;
			sk.push_back({ next_r,next_c });
		}
	}
}

int solution() {

	while (1) {
		if (sk.size() == 0) return -1;
		for (int i = 0; i < sk.size(); i++) {
			if (sk[i].row == 0 || sk[i].row == H - 1 || sk[i].col == 0 || sk[i].col == W - 1) {
				return Visited[sk[i].row][sk[i].col];
			}
		}			
		BFS_Fire();
		BFS();
	}
	return -1;
}


int main() {

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {

		init();
		input();
		int ans = solution();
		if (ans < 0) cout << "IMPOSSIBLE\n";
		else cout << ans << "\n";
	}


	return 0;
}