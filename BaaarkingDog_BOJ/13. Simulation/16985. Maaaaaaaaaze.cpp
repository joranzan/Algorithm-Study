#include<iostream>
#include<queue>

using namespace std;

//3���� �̷�
//5x5x5
//�Ͼ�� : �� �� ����
//������ : �� �� ����

//rotation ���� (�ð� or �ݽð�)

//��� 0,0,0   ���� 4,4,4   �Ա�,�ⱸ ���������� Ż�� �Ұ�

//���� ���� �̵�Ƚ���� Ż���� ����� ���  //BFS

//�ð����⵵
//�� 5�� �״� ���� : 120
//4������ 5�� : 4^5 = 256 x 4 = 1024
//125�� Ž��

struct pos {
	int height;
	int row;
	int col;
};

int originMap[5][5][5] = { 0, };
int tempMap[5][5][5] = { 0, };
int Answer = 1000;

int BFS();
void Rotation(int nowFloor);
void DFS(int depth);
void Stacking(int depth);
void input();
void solution();


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

//�Լ� ���Ǻ�

//�̷� Ż�� �Լ�
int BFS() {
	int distance[5][5][5] = { 0, };
	queue<pos> q;
	q.push({ 0,0,0 });
	distance[0][0][0] = 1;

	int dh[6] = { -1,1,0,0,0,0 };
	int dr[6] = { 0,0,-1,1,0,0 };
	int dc[6] = { 0,0,0,0,-1,1 };

	while (!q.empty()) {

		pos Now = q.front();
		q.pop();

		if (Now.height == 4 && Now.row == 4 && Now.col == 4) break;

		for (int dir = 0; dir < 6; dir++) {
			int next_h = Now.height + dh[dir];
			int next_r = Now.row + dr[dir];
			int next_c = Now.col + dc[dir];
			if (next_h < 0 || next_r < 0 || next_c < 0 || next_h >= 5 || next_r >= 5 || next_c >= 5) continue;
			if (tempMap[next_h][next_r][next_c] == 0) continue;
			if (distance[next_h][next_r][next_c] != 0) continue;
			if (distance[Now.height][Now.row][Now.col] + 1 > Answer) continue;
			distance[next_h][next_r][next_c] = distance[Now.height][Now.row][Now.col] + 1;
			q.push({ next_h,next_r,next_c });
		}
	}

	int ret = distance[4][4][4];
	if (ret <= 0) return 1000;
	else return ret - 1;
}


//rotation �Լ� -> �ѹ������θ� �����鼭 DFS
void Rotation(int nowFloor) {
	int tempRotate[5][5] = { 0, };

	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 5; c++) {
			tempRotate[c][4 - r] = tempMap[nowFloor][r][c];
		}
	}

	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 5; c++) {
			tempMap[nowFloor][r][c] = tempRotate[r][c];
		}
	}
}


//DFS -> depth: ���� ��
void DFS(int depth) {
	if (depth >= 5) {

		//�Ա�, �ⱸ �������� Ȯ�� (�������� return)
		if (tempMap[0][0][0] == 0 || tempMap[4][4][4] == 0) return;
		//�̷�ã�� BFS ����
		Answer = min(Answer, BFS());
		return;
	}

	for (int i = 0; i < 4; i++) {
		Rotation(depth);
		DFS(depth + 1);
	}

}


//�� �״� �Լ� (DFS�� �ٷ� �ױ�)
int used_floor[5] = { 0, };   //���� �̹� �� ä������
void Stacking(int depth) {
	if (depth >= 5) {

		//DFS�� �Ѿ��
		DFS(0);

		return;
	}
	for (int i = 0; i < 5; i++) {
		if (used_floor[i] == 1) continue;
		used_floor[i] = 1;
		//�ش� �� tempMap�迭�� �ֱ�
		for (int r = 0; r < 5; r++) {
			for (int c = 0; c < 5; c++) {
				tempMap[i][r][c] = originMap[depth][r][c];
			}
		}
		//���� �� ����������
		Stacking(depth + 1);

		used_floor[i] = 0;
	}

}


//�Է¹޴� �Լ�
void input() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				cin >> originMap[i][j][k];
			}
		}
	}
}

//Solution �Լ�
void solution() {

	Stacking(0);
	if (Answer >= 1000) cout << "-1";
	else cout << Answer << "\n";
}




