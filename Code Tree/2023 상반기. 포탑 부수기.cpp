#include<iostream>
#include<queue>
#include<deque>
#include<vector>

using namespace std;

struct Attack {
	//1. 공격자 선정
	//가장 약한 포탑
	//1) 공격력이 가장 낮은 포탑
	//2) 동률 시 가장 최근에 공격한 포탑
	//3) 동률 시 행과 열의 합이 가장 큰 포탑
	//4) 동률 시 열 값이 가장 큰 포탑
	//5) (N+M)만큼 공격력 증가
	int power;
	int time;
	int row;
	int col;

	bool operator<(Attack next) const {
		if (power < next.power) return false;
		else if (power > next.power) return true;
		else if (power == next.power) {
			if (time < next.time) return true;
			else if (time > next.time) return false;
			else if (time == next.time) {
				if (row + col < next.row + next.col) return true;
				else if (row + col > next.row + next.col) return false;
				else if (row + col == next.row + next.col) {
					if (col < next.col) return true;
					else if (col > next.col) return false;
					return false;
				}
			}
		}
	}
};
struct Target {
	
	//2. 공격자의 공격
	//가장 강한 포탑
	//1) 공격력이 가장 높은 포탑
	//2) 동률시 가장 예전에 공격한 포탑
	//3) 동률 시 행과 열의 합이 가장 작은 포탑
	//4) 동률 시 열이 가장 작은 포탑
	int power;
	int time;
	int row;
	int col;

	bool operator<(Target next) const {
		if (power < next.power) return true;
		else if (power > next.power) return false;
		else if (power == next.power) {
			if (time < next.time) return false;
			else if (time > next.time) return true;
			else if (time == next.time) {
				if (row + col < next.row + next.col) return false;
				else if (row + col > next.row + next.col) return true;
				else if (row + col == next.row + next.col) {
					if (col < next.col) return false;
					else if (col > next.col) return true;
					return false;
				}
			}
		}
	}
};
struct pos {
	int row;
	int col;
};

void input();
void init();
int N, M, K;
int Map[11][11] = { 0, };
bool Participated[11][11] = { false, };
int AttackTime[11][11] = { 0, };
int nowTime = 0;
priority_queue<Attack> pqAttack;
priority_queue<Target> pqTarget;
const int dr[4] = { 0,1,0,-1 };
const int dc[4] = { 1,0,-1,0 };
//공격방법 1순위 : 레이저 공격
//상하좌우로 이동가능
//부서진 포탑은 지날 수 없음
//가장자리에서 막힌 방향으로 진행하면 반대편으로 나옴
//최단 경로로 공격(DFS)
//우(0)하(1)좌(2)상(3) 순위
//공격자의 공격력만큼 공격력 줄어듬
//대상 경로에 있는 경우 공격력의 절반만큼 피해받음

bool Visited[11][11] = { false, };
int pathLengthMin = 1000;
vector<pos> FinalPath;
bool LasorOK = false;
void LasorDFS(int now_r, int now_c, vector<pos> path) {
	if (now_r == pqTarget.top().row && now_c == pqTarget.top().col) {
		if (pathLengthMin > path.size()) {
			FinalPath = path;
			pathLengthMin = path.size();
		}
		LasorOK = true;
		return;
	}
	if (path.size() >= pathLengthMin) return;
	for (int dir = 0; dir < 4; dir++) {
		int next_r = now_r + dr[dir];
		int next_c = now_c + dc[dir];
		if (next_r > N) next_r = 1;
		else if (next_r <= 0) next_r = N;
		if (next_c > M) next_c = 1;
		else if (next_c <= 0) next_c = M;
		if (Visited[next_r][next_c]) continue;
		if (Map[next_r][next_c] <= 0) continue;
		Visited[next_r][next_c] = true;
		path.push_back({ next_r, next_c });
		LasorDFS(next_r, next_c, path);
		path.pop_back();
		Visited[next_r][next_c] = false;
	}

}

bool LasorBFS() {

	bool success = false;
	pos tmp = { -1,-1 };
	pos Distance[11][11];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			Distance[i][j] = tmp;
		}
	}
	int start_r = pqAttack.top().row;
	int start_c = pqAttack.top().col;

	queue<pos> q;
	q.push({ start_r, start_c });
	Distance[start_r][start_c] = {start_r,start_c};

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();
		//만약 도달했다면
		if (nowRow == pqTarget.top().row && nowCol == pqTarget.top().col) {
			
			success = true;
			int temp_r = Distance[nowRow][nowCol].row;
			int temp_c = Distance[nowRow][nowCol].col;
			Map[nowRow][nowCol] -= Map[start_r][start_c];
			Participated[nowRow][nowCol] = true;
			while (1) {
				Participated[temp_r][temp_c] = true;
				if (temp_r == start_r && temp_c == start_c) break;
				Map[temp_r][temp_c] -= (Map[start_r][start_c] / 2);
				pos Next = Distance[temp_r][temp_c];
				temp_r = Next.row;
				temp_c = Next.col;
			}
			break;
		}

		//탐색
		for (int dir = 0; dir < 4; dir++) {
			int next_r = nowRow + dr[dir];
			int next_c = nowCol + dc[dir];
			if (next_r <= 0) next_r = N;
			else if (next_r > N) next_r = 1;
			if (next_c <= 0) next_c = M;
			else if (next_c > M) next_c = 1;
			if (Map[next_r][next_c] <= 0) continue;
			if (Distance[next_r][next_c].row!=-1||Distance[next_r][next_c].col!=-1) continue;
			Distance[next_r][next_c] = {nowRow,nowCol};
			q.push({ next_r, next_c });
		}
	}
	return success;
}


void BombBFS(int now_r, int now_c, int pow) {
	//공격방법 2순위 : 포탄 공격
	//레이저 공격 불가능일 때
	// 공격 대상 : 공격력만큼 피해
	//8개의 방향에 있는 포탑 : 공격력 절반만큼 피해
	//반대편으로 피해
	for (int i = now_r - 1; i <= now_r + 1; i++) {
		int temp_r = i;
		if (temp_r <= 0) temp_r = N;
		if (temp_r > N) temp_r = 1;
		for (int j = now_c - 1; j <= now_c + 1; j++) {
			int temp_c = j;
			if (temp_c <= 0) temp_c = M;
			if (temp_c > M) temp_c = 1;
			if (Map[temp_r][temp_c] <= 0) continue;
			if (temp_r == now_r && temp_c == now_c) continue;
			if (temp_r == pqAttack.top().row && temp_c == pqAttack.top().col) continue;
			Map[temp_r][temp_c] -= (pow / 2);
			Participated[temp_r][temp_c] = true;
		}
	}
	Map[now_r][now_c] -= pow;
	Participated[now_r][now_c] = true;
}


void StartAttack() {
	init();
	int attacker_r = pqAttack.top().row;
	int attacker_c = pqAttack.top().col;
	AttackTime[attacker_r][attacker_c] = nowTime;
	Participated[attacker_r][attacker_c] = true;
	Map[attacker_r][attacker_c] += (N + M);
	int attackerPow = Map[attacker_r][attacker_c];

	//Visited[attacker_r][attacker_c] = true;
	//vector<pos> temp;
	//LasorOK = false;
	//bool checkPoint1 = false;
	//bool checkPoint2 = false;
	//for (int dir = 0; dir < 4; dir++) {
	//	if (Map[attacker_r + dr[dir]][attacker_c + dc[dir]] != 0) checkPoint1 = true;
	//	if (Map[pqTarget.top().row + dr[dir]][pqTarget.top().col + dc[dir]] != 0) checkPoint2 = true;
	//	if (checkPoint1&&checkPoint2) break;
	//}
	//if (checkPoint1&&checkPoint2) {
	//	LasorDFS(attacker_r, attacker_c, temp);
	//}
	//if (LasorOK) {
	//	//cout << "Lasor\n";
	//	for (int i = 0; i < FinalPath.size(); i++) {
	//		pos Now = FinalPath[i];
	//		Participated[Now.row][Now.col] = true;
	//		if (Now.row == pqTarget.top().row && Now.col == pqTarget.top().col) {
	//			Map[Now.row][Now.col] -= attackerPow;
	//		}
	//		else {
	//			Map[Now.row][Now.col] -= (attackerPow / 2);
	//		}
	//	}
	//}
	bool LaserSucceed = LasorBFS();
	
	if(!LaserSucceed) {
		//cout << "BOMB\n";
		BombBFS(pqTarget.top().row, pqTarget.top().col, attackerPow);
	}

	//4. 포탑 정비
	//공격과 무관했던 포탑(공격피해X, 공격자X)은 공격력 1씩 증가
	while (!pqAttack.empty()) pqAttack.pop();
	while (!pqTarget.empty()) pqTarget.pop();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Map[i][j] <= 0) continue;
			if (!Participated[i][j]) {
				Map[i][j]++;
			}
			pqAttack.push({ Map[i][j], AttackTime[i][j], i, j});
			pqTarget.push({ Map[i][j], AttackTime[i][j],i,j });
			
		}
	}

}


void solution() {

	//4가지 액션 순서대로 수행 K턴 반복
	
	for (int i = 1; i <= K; i++) {
		//종료 조건 : 부서지지 않은 포탑 1개 -> 종료
		if(pqAttack.size() == 1 || pqTarget.size() == 1) break;
		nowTime = i;
		StartAttack();

		/*cout << nowTime << "번째 턴\n";
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= M; c++) {
				cout << Map[r][c] << " ";
			}
			cout << "\n";
		}
		cout << "\n";*/

	}
	cout << pqTarget.top().power;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	input();
	solution();

	//while (!pqAttack.empty()) {
	//	cout << pqAttack.top().power << " ";
	//	cout << pqAttack.top().time << " ";
	//	cout <<"(" << pqAttack.top().row << ", ";
	//	cout << pqAttack.top().col << ")\n";
	//	pqAttack.pop();
	//}

	//while (!pqTarget.empty()) {
	//	cout << pqTarget.top().power << " ";
	//	cout << pqTarget.top().time << " ";
	//	cout << "(" << pqTarget.top().row << ", ";
	//	cout << pqTarget.top().col << ")\n";
	//	pqTarget.pop();
	//}
	return 0;
}


//우선순위 큐 사용


//NxM 격자 (1,1)
//공격력 0 이하 -> 포탑 부서짐
void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] <= 0) continue;
			pqAttack.push({ Map[i][j], 0, i, j });
			pqTarget.push({ Map[i][j], 0,i,j });
		}
	}

	int debugging = -1;
}
void init() {
	pathLengthMin = 1000;
	FinalPath.clear();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			Visited[i][j] = false;
			Participated[i][j] = false;
		}
	}
}



