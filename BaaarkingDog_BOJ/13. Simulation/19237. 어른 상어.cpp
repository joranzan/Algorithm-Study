#include<iostream>
#include<vector>

using namespace std;

//NxN Map
//M���� ĭ�� ����

//��� ����
//1. 1~M ��ȣ
//2. 1�� ��� ���� ����


//��� �̵�
//1. �ڽ��� ������ �ش� ��ġ�� �Ѹ�
//2. 1�ʸ��� �����¿� �̵�
//	//1) �ƹ� ���� ���� ĭ�� ����
	//2) ���ٸ� �ڽ��� ������ �ִ� ĭ�� �������� (���� �켱���� �ٸ�)
	//3) ��� ���� : �ʱⰪ �־��� -> �̵� �� �̵��� ����
//3. �̵� �� ���� �ٽ� �Ѹ�
//4. K�� �̵� �� ���� �����
// 
//��� ��� �̵� ��
	//4) ��ĭ�� �������� ��� : ��ȣ ������ ���� ���� 

//�����¿�
const int DR[5] = { 0,-1,1,0,0 };
const int DC[5] = { 0,0,0,-1,1 };

struct shark {
	int row;
	int col;
	int id;
	int nowDir;
	int dirInfo[5][5] = { 0, };   //�����ȣ ����
	int dr[5][5] = { 0, };     
	int dc[5][5] = { 0, };
	bool dead = false; //�� �Ѱܳ����� ���� �Ǻ�
};

struct smell {
	int id;
	int value;
};

int N, M, K;
int SharkPos[21][21] = { 0, };   //����� ��ġ ����
int SharkDead[401] = { 0, };    //�� �Ѱܳ����� ���� �Ǻ�
smell Scent[21][21] = { 0, }; //��� ���� ����
shark SharkInfo[401];

void input();
void Scent_Simulation();
void Shark_Simulation();


void solution() {

	int time = 0;

	while (1) {

		time++;
		Scent_Simulation();
		Shark_Simulation();

		//1���� ���Ҵ��� üũ�ϴ� �κ�
		bool flag = true;
		for (int i = 2; i <= M; i++) {
			if (!SharkInfo[i].dead) {
				flag = false;
				break;
			}
		}

		if (flag) {
			cout << time;
			break;
		}
		if (time >= 1000) {
			cout << "-1";
			break;
		}
	}
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

void input() {
	cin >> N >> M >> K;
	//��
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> SharkPos[i][j];
			if (SharkPos[i][j] != 0) {
				SharkInfo[SharkPos[i][j]].row = i;
				SharkInfo[SharkPos[i][j]].col = j;
				SharkInfo[SharkPos[i][j]].id = SharkPos[i][j];
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		int d;
		cin >> d;
		SharkInfo[i].nowDir = d;
	}

	for (int i = 1; i <= M; i++) {
		for (int dir = 1; dir <= 4; dir++) {
			for (int j = 1; j <= 4; j++) {
				int d;
				cin >> d;
				SharkInfo[i].dirInfo[dir][j] = d;
				SharkInfo[i].dr[dir][j] = DR[d];
				SharkInfo[i].dc[dir][j] = DC[d];
			}

		}
	}
}

void Scent_Simulation() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Scent[i][j].value == 0) continue;
			Scent[i][j].value --;
		}
	}

	for (int i = 1; i <= M; i++) {
		if (SharkInfo[i].dead) continue;
		//K ���� ��ų�� ��� �ִ� ��ġ ���� ����
		Scent[SharkInfo[i].row][SharkInfo[i].col].id = i;
		Scent[SharkInfo[i].row][SharkInfo[i].col].value = K;
	}
}

void Shark_Simulation() {

	//������ �ִ� ��� ó�� ������
	int SharkTemp[21][21] = { 0, };

	for (int i = 1; i <= M; i++) {
		if (SharkInfo[i].dead) continue;
		// i : ��� ��ȣ
		//i�� ��� �̵�

		int nowRow = SharkInfo[i].row;
		int nowCol = SharkInfo[i].col;
		int nowDir = SharkInfo[i].nowDir;

		//������ ĭ�� �ƹ� ���� ������ Ȯ��
		bool allDone = false;
		for (int dir = 1; dir <= 4; dir++) {
			int nextRow = nowRow + SharkInfo[i].dr[nowDir][dir];
			int nextCol = nowCol + SharkInfo[i].dc[nowDir][dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Scent[nextRow][nextCol].value != 0) continue;
			allDone = true;
			SharkPos[nowRow][nowCol] = 0;
			if (SharkTemp[nextRow][nextCol] != 0) {
				if (SharkTemp[nextRow][nextCol] > i) SharkTemp[nextRow][nextCol] = i;
				else {
					SharkInfo[i].dead = true;
					break;
				}
			}
			SharkTemp[nextRow][nextCol] = i;
			SharkInfo[i].row = nextRow;
			SharkInfo[i].col = nextCol;
			SharkInfo[i].nowDir = SharkInfo[i].dirInfo[nowDir][dir];
			break;
		}

		if (allDone) continue;

		//���ٸ� �ڽ��� ������ �ִ� ĭ�� ��������(���� �켱���� �ٸ�)

		for (int dir = 1; dir <= 4; dir++) {
			int nextRow = nowRow + SharkInfo[i].dr[nowDir][dir];
			int nextCol = nowCol + SharkInfo[i].dc[nowDir][dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Scent[nextRow][nextCol].id != i && Scent[nextRow][nextCol].value != 0) continue;
			allDone = true;

			SharkTemp[nowRow][nowCol] = 0;
			SharkTemp[nextRow][nextCol] = i;
			SharkInfo[i].row = nextRow;
			SharkInfo[i].col = nextCol;
			SharkInfo[i].nowDir = SharkInfo[i].dirInfo[nowDir][dir];
			break;
		}
	}

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			SharkPos[r][c] = SharkTemp[r][c];
		}
	}
}