#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;


//문제 분석
//3차원 배열
//보관 후 하루 지나면 옆에 익음 -> 1일 뒤 퍼짐   (Distance -1) return
//상하좌우 위 아래 방향배열만들기
//BFS
// 맵 벗어나면 무시
//토마토 없는 -1 무시
//방문했으면 무시
//distance 최대 출력

struct pos {
	int height;
	int row;
	int col;
	
};

int M, N, H;
int Map[100][100][100] = { 0, };
int Distance[100][100][100] = { 0, };
vector<pos> Tomato;




void input() {

	//M N H
	cin >> M >> N >> H;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				cin >> Map[i][j][k];
				if (Map[i][j][k] == 1) {
					Tomato.push_back({ i,j,k });
				}
				Distance[i][j][k] = 0;
			}
		}
	}
}


int Answer = 0;
void BFS() {

	queue<pos> q;
	
	for (int i = 0; i < Tomato.size(); i++) {
		q.push(Tomato[i]);
		Distance[Tomato[i].height][Tomato[i].row][Tomato[i].col] = 1;
	}
	//위 아래 상 하 좌 우
	const int dh[6] = { -1,1,0,0,0,0 };
	const int dr[6] = { 0,0,-1,1,0,0 };
	const int dc[6] = { 0,0,0,0,-1,1 };

	while (!q.empty()) {

		pos Now = q.front();
		q.pop();

		int now_h = Now.height;
		int now_r = Now.row;
		int now_c = Now.col;

		

		for (int i = 0; i < 6; i++) {
			int next_h = now_h + dh[i];
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			if (next_h < 0 || next_h >= H) continue;
			if (next_r < 0 || next_r >= N) continue;
			if (next_c < 0 || next_c >= M) continue;
			if (Map[next_h][next_r][next_c] == -1) continue;
			if (Distance[next_h][next_r][next_c]!= 0) continue;
			Distance[next_h][next_r][next_c] = Distance[now_h][now_r][now_c] + 1;
			q.push({ next_h,next_r,next_c });
		}

	}
	bool valid = true;
	int max_value = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (Distance[i][j][k] == 0 && Map[i][j][k] == 0) {
					valid = false;
					break;
				}
				max_value = max(max_value, Distance[i][j][k]);
			}
			if (!valid) break;
 		}
		if (!valid) break;
	}
	
	if (!valid) Answer = -1;
	else Answer = max_value - 1;
}

void solution() {

	BFS();
	cout << Answer;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}