#include<iostream>
#include<vector>

using namespace std;

//���� ó���� �� �Ǽ� : �ʱ� �Է� ���鿡 ���Ͽ� Visited�迭�� ������Ʈ ������ ��


//���� �м�

//�̵�
//���� ���� ��ġ ����
//��: �����¿� (�� ���X)
//����: �����¿� 1�п� 1ĭ�� (�� ��� X)
// 
// Ż��
// �����ڸ� ���� �� 0,R-1 C-1 0
// 
// ��ǥ
//�ҿ� Ÿ�� �� Ż�� ����
//�󸶳� ����
struct pos {
	int row;
	int col;
};


int R, C;
char Map[1000][1000] = { 0, };
int Visited_Fire[1000][1000] = { 0, };
int Visited_JH[1000][1000] = { 0, };
vector<pos> JH;  // JH�� ���� �� �� �ִ� ��ġ��
vector<pos> Fire; //���� ���� ���� �� �ִ� ��ġ��


void input() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 'J') {
				JH.push_back({ i,j });
				Visited_JH[i][j] = 1;
			}
			else if (Map[i][j] == 'F') {
				Fire.push_back({ i,j });
				Visited_Fire[i][j] = 1;
			}
		}
	}

}

const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

void fire_BFS() { //�ѹ��� �ִ� �ð����⵵ 16

	vector<pos> temp = Fire;
	Fire.clear();
	for (int coord = 0; coord < temp.size(); coord++) {
		int now_r = temp[coord].row;
		int now_c = temp[coord].col;

		for (int dir = 0; dir < 4; dir++) {
			int next_r = now_r + dr[dir];
			int next_c = now_c + dc[dir];
			if (next_r < 0 || next_c < 0 || next_r >= R || next_c >= C) continue;
			if (Map[next_r][next_c] == '#') continue;
			if (Visited_Fire[next_r][next_c] == 1) continue;  //�̹� �˻������� ����
			Visited_Fire[next_r][next_c] = 1;
			Fire.push_back({ next_r,next_c });
		}
	}

}

void JH_BFS() {   //�ѹ��� �ִ� �ð����⵵ 16
	vector<pos> temp = JH;
	JH.clear();
	for (int coord = 0; coord < temp.size(); coord++) {
		int now_r = temp[coord].row;
		int now_c = temp[coord].col;

		for (int dir = 0; dir < 4; dir++) {
			int next_r = now_r + dr[dir];
			int next_c = now_c + dc[dir];
			if (next_r < 0 || next_c < 0 || next_r >= R || next_c >= C) continue;
			if (Map[next_r][next_c] == '#') continue;
			if (Visited_Fire[next_r][next_c] == 1) continue; //�̹� �� �Ű��� �� ����
			if (Visited_JH[next_r][next_c] == 1) continue;  //�̹� �˻������� ����
			Visited_JH[next_r][next_c] = 1;
			JH.push_back({ next_r,next_c });		
		}
	}
}


void solution() {


	int time = 0;
	while (1) {

		bool escapeValid = false;

		//Ż�� �Ұ����� ���
		//JH�� �����ڸ��� �ƴϾ��µ� ���̻� ������ ����(size=0)
		if (JH.size() == 0) {
			cout << "IMPOSSIBLE";
			break;
		}
		//���� �ִٸ�
		else {
			for (int i = 0; i < JH.size(); i++) {
				pos coord = JH[i];
				//Ż�� ������ ���
				//if(�����ڸ��� ��찡 �����Ѵٸ�!) �ð� ���
				if (coord.row == 0 || coord.row == R - 1 || coord.col == 0 || coord.col == C - 1) {
					cout << time + 1;
					escapeValid = true;
					break;
				}
			}
		}

		if (escapeValid) break;
		//Keep going
		//JH�� �����ڸ��� �ƴ����� �� ���� ���� ��Ȳ(size!=0)

		time++;
		fire_BFS();
		JH_BFS();

	}

}

int main() {

	input();
	solution();



	return 0;
}

//����

//BFS ���� (1000 1000)

//Fire ���� Flood Fill
//���� �̵��� �� �ִ� �� Visited ++


//���������� Queue_Fire  Queue_JH (vector�� �ص� �ɵ��ѵ�??)

//while(1)
//while�� �������� ����
//Ż�� ������ ���
//if(�����ڸ��� ��찡 �����Ѵٸ�!) �ð� ���

//Ż�� �Ұ����� ���
//JH�� �����ڸ��� �ƴϾ��µ� ���̻� ������ ����(size=0)

//Keep going
//JH�� �����ڸ��� �ƴ����� �� ���� ���� ��Ȳ(size!=0)
