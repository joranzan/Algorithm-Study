#include<iostream>
#include<vector>
#include<queue>
#include<deque>
#include<algorithm>

using namespace std;

struct pos {
	int row;
	int col;
};

struct info {
	int row;
	int col;
	int size;
};

const int dr[4] = { -1,0,1,0 };
const int dc[4] = { 0,-1,0,1 };
int N;
int Map[21][21]; //(0,0)
int sharkRow, sharkCol;  //상어 위치
int sharkSize = 2;
int curTime = 0;
int cnt = 0;
int eaten = 0;
vector<info> fish[7];  //물고기 위치 


int findDist(int targetRow, int targetCol) {

	int distance[21][21] = { 0 };
	queue<pos> q;
	q.push({ sharkRow, sharkCol });
	distance[sharkRow][sharkCol] = 1;

	while (!q.empty()) {

		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		if (nowRow == targetRow && nowCol == targetCol) {
			return distance[nowRow][nowCol] - 1;
		}


		for (int dir = 0; dir < 4; dir++) {
			int next_r = nowRow + dr[dir];
			int next_c = nowCol + dc[dir];
			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= N) continue;
			if (Map[next_r][next_c] > sharkSize) continue;
			if (distance[next_r][next_c] != 0) continue;
			distance[next_r][next_c] = distance[nowRow][nowCol] + 1;
			q.push({ next_r, next_c });
		}
	}
	return -1;
}

struct Select {
	int row;
	int col;
	int size;
	int dist;

	bool operator<(Select next) const {
		if (dist < next.dist) return false;
		else if (dist > next.dist) return true;
		else {
			if (row < next.row) return false;
			else if (row > next.row) return true;
			else {
				if (col < next.col) return false;
				else if (col > next.col) return true;
				else return false;
			}
		}
	}

};

void Simulation() {

	cnt = 0;
	priority_queue<Select> pq;
	
	for (int i = 1; i < min(7,sharkSize); i++) { //먹을 수 있는 애들
		for (int j = 0; j < fish[i].size(); j++) {
			int r = fish[i][j].row;
			int c = fish[i][j].col;
			if (Map[r][c] == 0) continue; //죽은 애들 제외
			int distance = findDist(r, c);
			if (distance == -1) {
				pq.push({ r,c, i, 10 });
				continue;
			}
			cnt++;
			pq.push({ r,c, i, distance });
		}
		fish[i].clear();
	}
	if (cnt == 0) return;

	int target_r = pq.top().row;
	int target_c = pq.top().col;
	curTime += pq.top().dist;
	Map[sharkRow][sharkCol] = 0;
	sharkRow = target_r;
	sharkCol = target_c;
	Map[target_r][target_c] = 9;
	eaten++;
	pq.pop();

	while (!pq.empty()) {
		fish[pq.top().size].push_back({ pq.top().row,pq.top().col, pq.top().size });
		pq.pop();
	}

	//먹으러 감

}

void input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];

			if (Map[i][j] >= 1 && Map[i][j] <= 6) {
				fish[Map[i][j]].push_back({ i,j, Map[i][j] });
			}
			else if (Map[i][j] == 9) {
				sharkRow = i;
				sharkCol = j;
			}
		}
	}

}
void solution() {

	while (1) {
		
		Simulation();
		if (cnt == 0) {
			break;
		}
		if (eaten == sharkSize) {
			eaten = 0;
			sharkSize++;
		}
	}
	cout << curTime;
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

//NxN Map (1칸에 물고기 최대 1마리)
//물고기 : M마리 , 상어 : 1마리(크기: 2)

//아기상어 이동
//상하좌우 1초에 1칸
//상어 크기 < 물고기 크기 : 못지나감
//상어 크기 == 물고기 크기 : 지나가지만 먹지 못함
//상어 크기 > 물고기 크기 : 지나가고 먹음

//이동 결정
//1) 먹을 수 있는 물고기 = 0 :  엄마한테 도움 요청 (게임 끝) 
//2) 먹을 수 있는 물고기 = 1 : 먹으러감
//3) 먹을 수 있는 물고기 > 1 : 가장 가까운 물고기
	//우선순위 : 지나야하는 칸 최소 -> 가장 위쪽(상) -> 가장 왼쪽(좌)

//먹을 때
//그 자리 물고기 빈칸
//상어 크기 == 먹은 물고기 수 : 크기 ++  (크기 커지면 Reset)