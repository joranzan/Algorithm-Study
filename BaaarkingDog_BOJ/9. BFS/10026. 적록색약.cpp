#include<iostream>
#include<queue>

using namespace std;

//���� �м�
//N x N �׸���
//R G B

//���ϻ��� �ƴ� ��� RGB ����
//���ϻ��� : RG / B ����

int N;
char Map[100][100];
int Visited[100][100];
int DAT[4] = { 0 };   //1: R   2: G  3: B
int DAT_Weak[3] = { 0 };  // 1: RG  2: B

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			Visited[i][j] = 0;
		}
	}
}

void BFS(int row, int col, char c) {
	queue<pair<int, int>> q;
	q.push({ row,col });

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	while (!q.empty()) {

		int now_r = q.front().first;
		int now_c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= N) continue;
			if (Map[next_r][next_c] != c) continue;
			if (Visited[next_r][next_c] != 0) continue;
			Visited[next_r][next_c] = 1;
			q.push({ next_r, next_c });
		}
	}

}

void solution() {


	//�������� ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			if (Visited[i][j] != 0) continue;
			if (Map[i][j] == 'R') {
				DAT[1]++;
			}
			else if (Map[i][j] == 'G') {
				DAT[2]++;
			}
			else if (Map[i][j] == 'B') {
				DAT[3]++;
			}
			Visited[i][j] = 1;
			BFS(i, j, Map[i][j]);
		}
	}

	//Visited �ʱ�ȭ, R�� G ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Visited[i][j] = 0;
			if (Map[i][j] == 'G') {
				Map[i][j] = 'R';
			}
		}
	}

	//���ϻ����� ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			if (Visited[i][j] != 0) continue;
			if (Map[i][j] == 'R') {
				DAT_Weak[1]++;
			}
			else if (Map[i][j] == 'B') {
				DAT_Weak[2]++;
			}
			Visited[i][j] = 1;
			BFS(i, j, Map[i][j]);
		}
	}

	cout << DAT[1] + DAT[2] + DAT[3] << " ";
	cout << DAT_Weak[1] + DAT_Weak[2];
}

int main() {
	input();
	solution();
}


//RGB DAT �����
//BFS
// R�϶� R �׷� ã��
// G�϶� G �׷� ã��
// B�϶� B �׷� ã��

//Visited �迭