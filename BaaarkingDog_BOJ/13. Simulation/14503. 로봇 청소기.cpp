#include<iostream>

using namespace std;

//�����м�
//�κ� û�ұ�, ���� ���� -> û���ϴ� ������ ����

//NxM �� or ��ĭ
//��(��1)��(��3)��(��2)��(��0) 




//û�� ����
//���� ĭ û�� x -> û��

//�����¿� û�� �ȵ� ��ĭ ���� ���
//�ٶ󺸴� ���� ���� + ��ĭ ���� �� 1�� ���ư�
//���� ���ϸ� �۵� exit

//�����¿� ��ĭ �ִ� ���
//�ݽð���� 90�� ȸ��
//�ٶ󺸴� ���� �������� ���� ĭ û�� ��������ĭ -> ����
//1�� ���ư�

int N, M;
int nowRow, nowCol;
int nowDir;
int Map[12][11] = { 0, };
int Answer = 0;

int Rotation(int dir) {

	//�� �� �� ��   0 1 2 3
	if (dir == 0) {
		return 1;
	}
	else if (dir == 1) {
		return 2;
	}
	else if (dir == 2) {
		return 3;
	}
	else if (dir == 3) {
		return 0;
	}
}

void Simulation() {

	const int dr[4] = { -1,0,1,0 };
	const int dc[4] = { 0,1,0,-1 };

	while (1) {

		if (Map[nowRow][nowCol] == 0) {
			Answer++;
			Map[nowRow][nowCol] = -1;  //û�� �Ϸ�
		}

		bool exist = false; //û�� �ȵ� �� �ִ��� ����
		for (int dir = 0; dir < 4; dir++) {
			int next_r = nowRow + dr[dir];
			int next_c = nowCol + dc[dir];
			if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= M) continue;
			if (Map[next_r][next_c] == 0) {
				exist = true;
			}
		}
		if (exist) {
			int tempDir = Rotation(nowDir);
			int next_r = nowRow + dr[tempDir];
			int next_c = nowCol + dc[tempDir];
			nowDir = tempDir;
			if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= M) continue;
			if (Map[next_r][next_c] == 0) {
				nowRow = next_r;
				nowCol = next_c;
			}
			
		}
		else if (!exist) {

			int tempDir = (nowDir + 2) % 4;
			int next_r = nowRow + dr[tempDir];
			int next_c = nowCol + dc[tempDir];

			if (Map[next_r][next_c] == 1) {
				break;
			}
			else {
				nowRow = next_r;
				nowCol = next_c;
			}

		}
	}
}

void solution() {

	Simulation();
	cout << Answer;
}

void input() {

	cin >> N >> M;

	cin >> nowRow >> nowCol >> nowDir;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
		}
	}
}

int main() {


	input();
	solution();

	return 0;
}

//1 1 1 1 1 1 1 1 1 1
//1 0 0 0 0 0 0 0 0 1
//1 0 0 0 1 1 1 1 0 1
//1 0 0 1 1 0 0 0 0 1
//1 0 1 1 0 0 0 0 0 1
//1 0 0 0 0 0 0 0 0 1
//1 0 0 0 0 0 0 1 0 1
//1 0 0 0 -1 1 1 0 1
//1 0 0 0 0 0 1 1 0 1
//1 0 0 0 0 0 0 0 0 1
//1 1 1 1 1 1 1 1 1 1