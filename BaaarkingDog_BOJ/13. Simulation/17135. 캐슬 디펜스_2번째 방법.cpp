#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
void input();
//���� �м�

//NxM �� (N+1���࿡�� ��)

//�ü� 3�� ��ġ (���� �ִ� ĭ����)
//���� 
//1. �Ѹ�� �� �ϳ� ���� ����
//2. ���ÿ� ����
//3. ���� ��� : �Ÿ� D���� �� ���� ����� ��
	//1) ������ �� : ���� ���� 
//4. ���� ���� ���� �ü����� ���ݴ��� �� ���� 
//5. ���ݹ��� ���� ���ܵ�

//�� �̵�
//1. �Ʒ��� ��ĭ
//2. ���� �ִ� ĭ���� �̵��ϸ� ���ӿ��� ����

//��ǥ: �ü��� ������ �� �ִ� ���� �ִ� ��

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
			//�켱���� : row ū ��, col ���� ��
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
		//�ü� ��ġ �������� ���� ����
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
