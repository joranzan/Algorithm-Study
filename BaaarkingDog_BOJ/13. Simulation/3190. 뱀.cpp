#include<iostream>
#include<queue>

using namespace std;

//���� �м�
//����� ������ �� ���̰� �þ
//�ڱ� �� �Ǵ� ���� �ε����� ���� ����


//���� ���� ����
//(1,1)���� ����, ����: 1
//�������� ����

//���� �÷���
//1. �Ӹ��� ����ĭ�� ��ġ��Ŵ
//2. ����ĭ�� �� �Ǵ� �ڱ� ���̸� Game Over
//3. ������ ĭ�� ����� �ִٸ� ����� �������� ������ �״��
//4. ������ ĭ�� ����� ���ٸ� ������ ��ġ�� ĭ�� ���


//�� �ʾȿ� ������ ��������?

struct ChangeDir {
	int time;
	char c;
};
struct pos {
	int row;
	int col;
};

int N, K, L;
int Board[101][101] = { 0, };  //��� 1, �� �� : -1
queue<ChangeDir> query;  //���� ��ȯ ���� ť
// ��(0) ��(1) ��(2) ��(3)
int nowDir = 3;
int nowTime = 0;
void input();

void direction(char c) {

	if (c == 'L') {  //�ݽð�
		if (nowDir == 0) {
			nowDir = 2;
		}
		else if (nowDir == 1) {
			nowDir = 3;
		}
		else if (nowDir == 2) {
			nowDir = 1;
		}
		else if (nowDir == 3) {
			nowDir = 0;
		}
	}
	else if (c == 'D') { //�ð�
		if (nowDir == 0) {
			nowDir = 3;
		}
		else if (nowDir == 1) {
			nowDir = 2;
		}
		else if (nowDir == 2) {
			nowDir = 0;
		}
		else if (nowDir == 3) {
			nowDir = 1;
		}
	}

}

void Simulation() {

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };
	
	queue<pos> Snake;
	Snake.push({ 1,1 });
	int headRow = Snake.front().row;
	int headCol = Snake.front().col;
	while (1) {
						
		if (!query.empty()&&nowTime == query.front().time) {
			direction(query.front().c);
			query.pop();
		}

		int next_headRow = headRow + dr[nowDir];
		int next_headCol = headCol + dc[nowDir];
		nowTime++;
		if (next_headRow <= 0 || next_headCol <= 0 || next_headRow > N || next_headCol > N) break;
		if (Board[next_headRow][next_headCol] == -1) break;
		//��� ���� ���
		else if (Board[next_headRow][next_headCol] == 0) {
			Snake.push({ next_headRow, next_headCol });
			Board[next_headRow][next_headCol] = -1;
			Board[Snake.front().row][Snake.front().col] = 0;
			Snake.pop();
			headRow = next_headRow;
			headCol = next_headCol;
		}
		//��� �ִ� ���
		else if (Board[next_headRow][next_headCol] == 1) {
			Snake.push({ next_headRow, next_headCol });
			Board[next_headRow][next_headCol] = -1;
			headRow = next_headRow;
			headCol = next_headCol;
		}

	}

}


void solution() {
	Simulation();
	cout << nowTime << "\n";
}

int main() {

	input();
	solution();


	return 0;
}

//�Է�
//N(NxN)
//K(����� ����)
//����� ��ġ (��,��)
//L(���� ��ȯ Ƚ��)
//X(���ӽ����ϰ� X�� ���� ����) C(L:�ð�ݴ�, D: �ð�)


void input() {
	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		int row, col;
		cin >> row >> col;
		Board[row][col] = 1;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int X;
		char C;
		cin >> X >> C;
		query.push({ X,C });
	}

}