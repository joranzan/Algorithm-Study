//���� �ð� : 19:30
//���� �ð� : 
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

struct pos {
	int row;
	int col;
};

struct turret {
	int id;
	pos nowPos;
	int power;
	int attackTime = 0;
	bool activated = true;

	bool operator<(turret next) const {
		if (power < next.power) return true;
		else if (power > next.power) return false;
		else {
			if (attackTime < next.attackTime) return false;
			else if (attackTime > next.attackTime) return true;
			else {
				if (nowPos.row + nowPos.col < next.nowPos.row + next.nowPos.col) return false;
				else if (nowPos.row + nowPos.col > next.nowPos.row + next.nowPos.col) return true;
				else {
					if (nowPos.col < next.nowPos.col) return false;
					else if (nowPos.col > next.nowPos.col) return true;
					else return false;
				}
			}
		}
		return false;
	}
	/*
	1. ������ ����
		1) ������ : ���� ���� ��ž (�ڵ�ĸ N+M ���ݷ� ����)
			- ��������
				- ���ݷ� ���� ���� ��ž
				- ������ ��� : ���� �ֱ� ������ ��ž
				- ������ ��� : �� + �� ���� ū ��ž
				- ������ ��� : �� ���� ���� ū ��ž

	2. ���� : ���� ���� ��ž ����

		1) ���ݴ�� : ���� ����
			- ���ݷ��� ���� ���� ��ž
			- ������ ��� : ���� ���� �� ������ ��ž
			- ������ ��� : �� + �� ���� ���� ��ž
			- ������ ��� : �� ���� ���� ���� ��ž
	*/
};

int N, M, K;    // K : 1000 , ���ݷ� : 5000

turret TurretMap[11][11] = { 0, };  //��ž ID ���� 
bool isChangedMap[11][11] = { false, };

void init() {

	cin >> N >> M >> K;
	int TurretNum = 0;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			TurretNum++;
			cin >> TurretMap[r][c].power;
			TurretMap[r][c].id = TurretNum;
			TurretMap[r][c].nowPos.row = r;
			TurretMap[r][c].nowPos.col = c;
			if (TurretMap[r][c].power <= 0) TurretMap[r][c].activated = false;
		}
	}
}


bool LaserAttack(pos attackerPos, pos targetPos) {


	int AttackRow = attackerPos.row;
	int AttackCol = attackerPos.col;
	int TargetRow = targetPos.row;
	int TargetCol = targetPos.col;

	//(��, ��, ��, ��)
	const int dr[4] = { 0,1,0,-1 };
	const int dc[4] = { 1,0,-1,0 };
	bool foundPath = false;
	//BFS�� Ž��

	//�湮 �迭 �ʱ�ȭ
	pos Visited[11][11];
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			Visited[r][c].row = -1;
			Visited[r][c].col = -1;
		}
	}

	queue<pos> q;
	q.push({ AttackRow, AttackCol });
	Visited[AttackRow][AttackCol] = { AttackRow, AttackCol };

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();



		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow <= 0) nextRow = N;
			if (nextCol <= 0) nextCol = M;
			if (nextRow > N) nextRow = 1;
			if (nextCol > M) nextCol = 1;
			//���� ��ž ��������
			if (TurretMap[nextRow][nextCol].power <= 0) continue;
			//�湮 ��� ����
			if (!(Visited[nextRow][nextCol].row == -1 && Visited[nextRow][nextCol].col == -1)) continue;

			Visited[nextRow][nextCol] = { nowRow, nowCol };
			if (nextRow == TargetRow && nextCol == TargetCol) {
				//cout << "Laser Attack ���\n";
				//cout << "(" << nextRow << ", " << nextCol << ") ";
				int tempRow = nextRow;
				int tempCol = nextCol;
				foundPath = true;
				while (!(tempRow == AttackRow && tempCol == AttackCol)) {
					int tempnextRow = Visited[tempRow][tempCol].row;
					int tempnextCol = Visited[tempRow][tempCol].col;
					//cout << "(" << tempnextRow << ", " << tempnextCol << ") ";
					if (tempnextRow == AttackRow && tempnextCol == AttackCol) {
						//cout << "\n";
						break;
					}
					TurretMap[tempnextRow][tempnextCol].power -= (TurretMap[AttackRow][AttackCol].power / 2);
					isChangedMap[tempnextRow][tempnextCol] = true;
					tempRow = tempnextRow;
					tempCol = tempnextCol;
				}
				if (foundPath) break;
			}
			q.push({ nextRow, nextCol });
		}

		if (foundPath) break;
	}

	if (foundPath) {

		isChangedMap[AttackRow][AttackCol] = true;
		isChangedMap[TargetRow][TargetCol] = true;
		TurretMap[TargetRow][TargetCol].power -= TurretMap[AttackRow][AttackCol].power;
		return true;
	}

	return false;
}


void BombAttack(pos attackerPos, pos targetPos) {

	const int dr[8] = { -1,1,0,0,-1,-1,1,1 };
	const int dc[8] = { 0,0,-1,1,-1,1,-1,1 };

	int TargetRow = targetPos.row;
	int TargetCol = targetPos.col;

	for (int dir = 0; dir < 8; dir++) {
		int nextRow = TargetRow + dr[dir];
		int nextCol = TargetCol + dc[dir];
		if (nextRow <= 0) nextRow = N;
		if (nextCol <= 0) nextCol = M;
		if (nextRow > N) nextRow = 1;
		if (nextCol > M) nextCol = 1;

		if (TurretMap[nextRow][nextCol].power <= 0) continue;
		if (!TurretMap[nextRow][nextCol].activated) continue;
		if (nextRow == attackerPos.row && nextCol == attackerPos.col) continue;
		//cout << "(" << nextRow << ", " << nextCol << ") ";
		TurretMap[nextRow][nextCol].power -= (TurretMap[attackerPos.row][attackerPos.col].power / 2);
		isChangedMap[nextRow][nextCol] = true;
	}

	isChangedMap[attackerPos.row][attackerPos.col] = true;
	isChangedMap[TargetRow][TargetCol] = true;
	//cout << "(" << TargetRow << ", " << TargetCol << ")\n";
	TurretMap[TargetRow][TargetCol].power -= TurretMap[attackerPos.row][attackerPos.col].power;

}

void Attack(pos attackerPos, pos targetPos) {

	//������ ���� �Ǻ�
	bool laserSuccess = LaserAttack(attackerPos, targetPos);


	if (!laserSuccess) {
		BombAttack(attackerPos, targetPos);
		//cout << "Bomb Attack\n";
	}
}



void solution() {



	for (int k = 1; k <= K; k++) {
		//cout << "---------------------------------------------------------------------\n";
		//cout << k << "��° ��\n";

		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= M; c++) {
				//cout << TurretMap[r][c].power << " ";
			}
			//cout << "\n";
		}

		//cout << "\n";

		//������ ����
		//���� ��� ����
		turret attacker = TurretMap[0][0];
		turret target = TurretMap[0][0];
		attacker.power = 2112345678;
		target.power = -2100000000;

		bool findMin = true;
		bool findMax = true;

		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= M; c++) {
				isChangedMap[r][c] = false;
				if (!TurretMap[r][c].activated) continue;
				if (TurretMap[r][c].power <= 0) continue;
				if (TurretMap[r][c] < attacker) attacker = TurretMap[r][c];
				if (target < TurretMap[r][c]) target = TurretMap[r][c];
			}
		}

		if (target.power == -2100000000 || attacker.power == 2112345678) {
			int debuggging = -1;
		}

		if (attacker.id == target.id) break;

		//�ڵ�ĸ & ���ݽñ� ����
		TurretMap[attacker.nowPos.row][attacker.nowPos.col].power += (N + M);
		TurretMap[attacker.nowPos.row][attacker.nowPos.col].attackTime = k;

		//cout << "������ ��ġ: (" << attacker.nowPos.row << ", " << attacker.nowPos.col << ")\n";
		//cout << "���ݴ�� ��ġ : (" << target.nowPos.row << ", " << target.nowPos.col << ")\n";
		//cout << "���ݷ� : " << TurretMap[attacker.nowPos.row][attacker.nowPos.col].power << "\n";
		//cout << "�ֺ� ���ݷ� : " << TurretMap[attacker.nowPos.row][attacker.nowPos.col].power / 2 << "\n";
		//����
		Attack(attacker.nowPos, target.nowPos);

		//���� ��ž ó��
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= M; c++) {
				if (!TurretMap[r][c].activated) continue;
				if (TurretMap[r][c].power <= 0) {
					TurretMap[r][c].activated = false;
					TurretMap[r][c].power = 0;
				}
			}
		}

		//cout << "\n����� ��ž" << "\n";
		//����
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= M; c++) {
				if (!TurretMap[r][c].activated) continue;
				if (isChangedMap[r][c]) continue;
				//cout << "(" << r << ", " << c << ") ";
				TurretMap[r][c].power++;
			}
		}

		//cout << "\n\n\n";
	}

	int Answer = 0;



	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			//cout << TurretMap[r][c].power << " ";
			if (!TurretMap[r][c].activated) continue;
			Answer = max(Answer, TurretMap[r][c].power);
		}
		//cout << "\n";
	}

	cout << Answer;

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	init();
	solution();

	return 0;
}


/*
���� �м�

�� : N x M
��ž ����
	- ���ݷ� (��Ȳ�� ���� �����)
		- 0���� �μ��� (���� ����)
		- ���� 0 ����

4���� �׼� K�� �ݺ�

1. ������ ����
	1) ������ : ���� ���� ��ž (�ڵ�ĸ N+M ���ݷ� ����)
		- ��������
			- ���ݷ� ���� ���� ��ž
			- ������ ��� : ���� �ֱ� ������ ��ž
			- ������ ��� : �� + �� ���� ū ��ž
			- ������ ��� : �� ���� ���� ū ��ž

2. ���� : ���� ���� ��ž ����

1) ���ݴ�� : ���� ����
	- ���ݷ��� ���� ���� ��ž
	- ������ ��� : ���� ���� �� ������ ��ž
	- ������ ��� : �� + �� ���� ���� ��ž
	- ������ ��� : �� ���� ���� ���� ��ž


2-1) ������ ���� ���� �õ� (�ִ� ��η� ����)

	1) �����¿� 4���� ���� ������ �� ���� (��, ��, ��, ��)
	2) �μ��� ��ž ��������
	3) ���� �� -> �ݴ������� ����
	4) ��� ���� ��
		1) (���ݴ�� ���ݷ� - �������� ���ݷ�)
		2) (����� ���ݷ� - (�������� ���ݷ�/2))


	Flag �ʿ� (������ �����ߴ��� ����)

2-2) ��ź ���� �õ�

	1) ���� ��󿡰� ��ź ���� (�������� ���ݷ¸�ŭ ����)
	2) ������ 8������ ��ž�� (�������� ���ݷ�/2 ��ŭ ����)
		(���� ����� ��� �ݴ�������)




3) ��ž �μ��� (���ݷ� 0���ϸ� �μ���)


4) ��ž ����

	(���� �ȹ��� ��ž���� ���ݷ� +1)
	���� : ������ x , ���� ��� x , �� ���� x




5) ��ž �� ���� ���� ��ž�� ���ݷ��� ���
*/