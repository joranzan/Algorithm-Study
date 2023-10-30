#include<iostream>
#include<vector>
#include<queue>
#include<deque>
#include<algorithm>

using namespace std;

struct pos {
	int row;
	int col;
};

struct info {
	int row;
	int col;
	int size;
};

const int dr[4] = { -1,0,1,0 };
const int dc[4] = { 0,-1,0,1 };
int N;
int Map[21][21]; //(0,0)
int sharkRow, sharkCol;  //��� ��ġ
int sharkSize = 2;
int curTime = 0;
int cnt = 0;
int eaten = 0;
vector<info> fish[7];  //����� ��ġ 


int findDist(int targetRow, int targetCol) {

	int distance[21][21] = { 0 };
	queue<pos> q;
	q.push({ sharkRow, sharkCol });
	distance[sharkRow][sharkCol] = 1;

	while (!q.empty()) {

		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		if (nowRow == targetRow && nowCol == targetCol) {
			return distance[nowRow][nowCol] - 1;
		}


		for (int dir = 0; dir < 4; dir++) {
			int next_r = nowRow + dr[dir];
			int next_c = nowCol + dc[dir];
			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= N) continue;
			if (Map[next_r][next_c] > sharkSize) continue;
			if (distance[next_r][next_c] != 0) continue;
			distance[next_r][next_c] = distance[nowRow][nowCol] + 1;
			q.push({ next_r, next_c });
		}
	}
	return -1;
}

struct Select {
	int row;
	int col;
	int size;
	int dist;

	bool operator<(Select next) const {
		if (dist < next.dist) return false;
		else if (dist > next.dist) return true;
		else {
			if (row < next.row) return false;
			else if (row > next.row) return true;
			else {
				if (col < next.col) return false;
				else if (col > next.col) return true;
				else return false;
			}
		}
	}

};

void Simulation() {

	cnt = 0;
	priority_queue<Select> pq;
	
	for (int i = 1; i < min(7,sharkSize); i++) { //���� �� �ִ� �ֵ�
		for (int j = 0; j < fish[i].size(); j++) {
			int r = fish[i][j].row;
			int c = fish[i][j].col;
			if (Map[r][c] == 0) continue; //���� �ֵ� ����
			int distance = findDist(r, c);
			if (distance == -1) {
				pq.push({ r,c, i, 10 });
				continue;
			}
			cnt++;
			pq.push({ r,c, i, distance });
		}
		fish[i].clear();
	}
	if (cnt == 0) return;

	int target_r = pq.top().row;
	int target_c = pq.top().col;
	curTime += pq.top().dist;
	Map[sharkRow][sharkCol] = 0;
	sharkRow = target_r;
	sharkCol = target_c;
	Map[target_r][target_c] = 9;
	eaten++;
	pq.pop();

	while (!pq.empty()) {
		fish[pq.top().size].push_back({ pq.top().row,pq.top().col, pq.top().size });
		pq.pop();
	}

	//������ ��

}

void input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];

			if (Map[i][j] >= 1 && Map[i][j] <= 6) {
				fish[Map[i][j]].push_back({ i,j, Map[i][j] });
			}
			else if (Map[i][j] == 9) {
				sharkRow = i;
				sharkCol = j;
			}
		}
	}

}
void solution() {

	while (1) {
		
		Simulation();
		if (cnt == 0) {
			break;
		}
		if (eaten == sharkSize) {
			eaten = 0;
			sharkSize++;
		}
	}
	cout << curTime;
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

//NxN Map (1ĭ�� ����� �ִ� 1����)
//����� : M���� , ��� : 1����(ũ��: 2)

//�Ʊ��� �̵�
//�����¿� 1�ʿ� 1ĭ
//��� ũ�� < ����� ũ�� : ��������
//��� ũ�� == ����� ũ�� : ���������� ���� ����
//��� ũ�� > ����� ũ�� : �������� ����

//�̵� ����
//1) ���� �� �ִ� ����� = 0 :  �������� ���� ��û (���� ��) 
//2) ���� �� �ִ� ����� = 1 : ��������
//3) ���� �� �ִ� ����� > 1 : ���� ����� �����
	//�켱���� : �������ϴ� ĭ �ּ� -> ���� ����(��) -> ���� ����(��)

//���� ��
//�� �ڸ� ����� ��ĭ
//��� ũ�� == ���� ����� �� : ũ�� ++  (ũ�� Ŀ���� Reset)