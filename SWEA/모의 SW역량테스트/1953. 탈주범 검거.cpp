#include<iostream>
#include<queue>

using namespace std;

//문제 분석
//탈출 1시간 뒤 지하터널에 들어감
//탈주범이 있을 수 있는 위치 계산

struct pos {
	int row;
	int col;
};

//이동 통로
// 1: 상하좌우  
// 2: 상 하
// 3: 좌 우
// 4: 상 우
// 5: 하 우
// 6: 하 좌
// 7: 상 좌



// 상하좌우 0 1 2 3
//상 과 연결되기 위해서는 1,2,5,6
//하 와 연결되기 위해서는 1,2,4,7
//좌 와 연결되기 위해서는 1,3,4,5
//우 와 연결되기 위해서는 1,3,6,7

const int DAT_valid[4][8] = {
	//   0 1 2 3 4 5 6 7
		{0,1,1,0,1,0,0,1},
		{0,1,1,0,0,1,1,0},
		{0,1,0,1,0,0,1,1},
		{0,1,0,1,1,1,0,0} 
};

const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

const int DAT[4][8] = {
	//   0 1 2 3 4 5 6 7
		{0,1,1,0,0,1,1,0},//현재 노드에서 상 방향 탐색
		{0,1,1,0,1,0,0,1},//현재 노드에서 하 방향 탐색
		{0,1,0,1,1,1,0,0},//현재 노드에서 좌 방향 탐색
		{0,1,0,1,0,0,1,1} //현재 노드에서 우 방향 탐색
};

int N, M;
int R, C;  //맨홀(시작점 위치)
int L;     //탈출 후 소요시간
int Map[51][51] = { 0, };
int Visited[51][51] = { 0, };  //시작점 1     

void init() {

	N = M = 0;
	R = C = 0;
	L = 0;
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			Visited[i][j] = 0;
			Map[i][j] = 0;
		}
	}
}
void input() {

	cin >> N >> M;
	cin >> R >> C >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
		}
	}

}

int BFS() {

	queue<pos> q;
	q.push({ R,C });
	Visited[R][C] = 1;
	int cnt = 1;

	while (!q.empty()) {

		int now_r = q.front().row;
		int now_c = q.front().col;
		q.pop();

		if (Visited[now_r][now_c] == L) continue;

		int now_value = Map[now_r][now_c];

		for (int i = 0; i < 4; i++) {
			if (DAT_valid[i][Map[now_r][now_c]] == 0) continue;
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= M) continue;
			int next_value = Map[next_r][next_c];
			//만약 다음노드와 연결통로가 끊겨있다면 (이동 불가라면)
			if (DAT[i][next_value] == 0) continue;
			//이미 방문해서 개수 반영했던 노드이면 건너뜀
			if (Visited[next_r][next_c] != 0) continue;
			//연결까지 되어있다면
			Visited[next_r][next_c] = Visited[now_r][now_c] + 1;
			q.push({ next_r,next_c });
			cnt++;
		}
	}
	return cnt;
}

int solution() {
	return BFS();
}




int main() {

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {

		init();
		input();
		int answer = solution();

		cout << "#" << test << " " << answer << "\n";

	}

	return 0;
}



//******탈출 한시간 뒤는 무조건 시작점
//이후부터
//현재 지점, 이동 가능 지점 모두 가능(가만히 있어도 됨)

//지나가는 칸 개수 세기? + 시작지점 -> Visited 배열 필요