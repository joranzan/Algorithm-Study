#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
void input();
//문제 분석

//NxM 맵 (N+1번행에는 성)

//궁수 3명 배치 (성이 있는 칸에만)
//공격 
//1. 한명당 적 하나 공격 가능
//2. 동시에 공격
//3. 공격 대상 : 거리 D이하 중 가장 가까운 적
	//1) 동률일 때 : 가장 왼쪽 
//4. 같은 적이 여러 궁수에게 공격당할 수 있음 
//5. 공격받은 적은 제외됨

//적 이동
//1. 아래로 한칸
//2. 성이 있는 칸으로 이동하면 게임에서 제외

//목표: 궁수가 제거할 수 있는 적의 최대 수

struct pos {
	int row;
	int col;
};

struct far {
	int row;
	int col;
	int dist;
	bool operator<(far next) {
		if (dist < next.dist) return false;
		else if (dist > next.dist) return true;
		else {
			//우선순위 : row 큰 순, col 작은 순
			if (col < next.col) return false;
			else return true;
		}
	}
};

int N, M, D;
int Map[17][17] = { 0, };
int tempMap[17][17] = { 0, };
vector<pos> Attacker;
int enemyCnt = 0;
int Answer = 0;
int killed = 0;

void Attack(int lastRow) {

	vector<pos> gotAttacked;
	for (int a = 0; a < 3; a++) {
		int attackerRow = Attacker[a].row;
		int attackerCol = Attacker[a].col;
		Attacker[a].row--;

		far Candi = { 0, M, 250 };

		for (int r = lastRow; r >= 1; r--) {
			for (int c = 1; c <= M; c++) {
				if (tempMap[r][c] == 0) continue;
				int dist = abs(attackerRow - r) + abs(attackerCol - c);
				if (Candi.dist < dist || dist > D) continue;
				far next = { r,c, dist };
				if (Candi < next) Candi = next;
			}
		}
		if (Candi.dist == 250) continue;
		gotAttacked.push_back({ Candi.row, Candi.col });
	}


	for (int i = 0; i < gotAttacked.size(); i++) {
		if (tempMap[gotAttacked[i].row][gotAttacked[i].col] == 1) {
			tempMap[gotAttacked[i].row][gotAttacked[i].col] = 0;
			killed++;
			enemyCnt--;
		}
	}

	for (int i = 1; i <= M; i++) {
		if (tempMap[lastRow][i] == 1) enemyCnt--;
	}
}


void DFS(int depth, int index) {

	if (depth >= 3) {

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				tempMap[i][j] = Map[i][j];
				if (Map[i][j] == 1) enemyCnt++;
			}
		}
		killed = 0;
		bool flag = false;
		while (Attacker[0].row!=0) {
			Attack(Attacker[0].row - 1);
			if (Answer > killed + enemyCnt) {
				flag = true;
				break;
			}
		}
		//cout << "\n";
		//궁수 위치 정했으면 공격 개시
		if (!flag) {
			Answer = max(Answer, killed);
		}
		
		for (int i = 0; i < 3; i++) {
			Attacker[i].row = N + 1;
		}
		return;
	}

	for (int i = index; i <= M; i++) {
		Attacker.push_back({ N + 1, i });
		DFS(depth + 1, i + 1);
		Attacker.pop_back();
	}
}


void solution() {

	DFS(0, 1);
	cout << Answer;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

void input() {
	cin >> N >> M >> D;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> Map[i][j];
		}
	}
}
