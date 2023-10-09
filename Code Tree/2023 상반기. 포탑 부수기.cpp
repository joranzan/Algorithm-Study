#include<iostream>
#include<queue>
#include<deque>
#include<vector>

using namespace std;

struct Attack {
	//1. ������ ����
	//���� ���� ��ž
	//1) ���ݷ��� ���� ���� ��ž
	//2) ���� �� ���� �ֱٿ� ������ ��ž
	//3) ���� �� ��� ���� ���� ���� ū ��ž
	//4) ���� �� �� ���� ���� ū ��ž
	//5) (N+M)��ŭ ���ݷ� ����
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
	
	//2. �������� ����
	//���� ���� ��ž
	//1) ���ݷ��� ���� ���� ��ž
	//2) ������ ���� ������ ������ ��ž
	//3) ���� �� ��� ���� ���� ���� ���� ��ž
	//4) ���� �� ���� ���� ���� ��ž
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
//���ݹ�� 1���� : ������ ����
//�����¿�� �̵�����
//�μ��� ��ž�� ���� �� ����
//�����ڸ����� ���� �������� �����ϸ� �ݴ������� ����
//�ִ� ��η� ����(DFS)
//��(0)��(1)��(2)��(3) ����
//�������� ���ݷ¸�ŭ ���ݷ� �پ��
//��� ��ο� �ִ� ��� ���ݷ��� ���ݸ�ŭ ���ع���

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
		//���� �����ߴٸ�
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

		//Ž��
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
	//���ݹ�� 2���� : ��ź ����
	//������ ���� �Ұ����� ��
	// ���� ��� : ���ݷ¸�ŭ ����
	//8���� ���⿡ �ִ� ��ž : ���ݷ� ���ݸ�ŭ ����
	//�ݴ������� ����
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

	//4. ��ž ����
	//���ݰ� �����ߴ� ��ž(��������X, ������X)�� ���ݷ� 1�� ����
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

	//4���� �׼� ������� ���� K�� �ݺ�
	
	for (int i = 1; i <= K; i++) {
		//���� ���� : �μ����� ���� ��ž 1�� -> ����
		if(pqAttack.size() == 1 || pqTarget.size() == 1) break;
		nowTime = i;
		StartAttack();

		/*cout << nowTime << "��° ��\n";
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


//�켱���� ť ���


//NxM ���� (1,1)
//���ݷ� 0 ���� -> ��ž �μ���
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



