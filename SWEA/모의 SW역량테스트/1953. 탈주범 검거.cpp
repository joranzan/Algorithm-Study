#include<iostream>
#include<queue>

using namespace std;

//���� �м�
//Ż�� 1�ð� �� �����ͳο� ��
//Ż�ֹ��� ���� �� �ִ� ��ġ ���

struct pos {
	int row;
	int col;
};

//�̵� ���
// 1: �����¿�  
// 2: �� ��
// 3: �� ��
// 4: �� ��
// 5: �� ��
// 6: �� ��
// 7: �� ��



// �����¿� 0 1 2 3
//�� �� ����Ǳ� ���ؼ��� 1,2,5,6
//�� �� ����Ǳ� ���ؼ��� 1,2,4,7
//�� �� ����Ǳ� ���ؼ��� 1,3,4,5
//�� �� ����Ǳ� ���ؼ��� 1,3,6,7

const int DAT_valid[4][8] = {
	//   0 1 2 3 4 5 6 7
		{0,1,1,0,1,0,0,1},
		{0,1,1,0,0,1,1,0},
		{0,1,0,1,0,0,1,1},
		{0,1,0,1,1,1,0,0} 
};

const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

const int DAT[4][8] = {
	//   0 1 2 3 4 5 6 7
		{0,1,1,0,0,1,1,0},//���� ��忡�� �� ���� Ž��
		{0,1,1,0,1,0,0,1},//���� ��忡�� �� ���� Ž��
		{0,1,0,1,1,1,0,0},//���� ��忡�� �� ���� Ž��
		{0,1,0,1,0,0,1,1} //���� ��忡�� �� ���� Ž��
};

int N, M;
int R, C;  //��Ȧ(������ ��ġ)
int L;     //Ż�� �� �ҿ�ð�
int Map[51][51] = { 0, };
int Visited[51][51] = { 0, };  //������ 1     

void init() {

	N = M = 0;
	R = C = 0;
	L = 0;
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			Visited[i][j] = 0;
			Map[i][j] = 0;
		}
	}
}
void input() {

	cin >> N >> M;
	cin >> R >> C >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
		}
	}

}

int BFS() {

	queue<pos> q;
	q.push({ R,C });
	Visited[R][C] = 1;
	int cnt = 1;

	while (!q.empty()) {

		int now_r = q.front().row;
		int now_c = q.front().col;
		q.pop();

		if (Visited[now_r][now_c] == L) continue;

		int now_value = Map[now_r][now_c];

		for (int i = 0; i < 4; i++) {
			if (DAT_valid[i][Map[now_r][now_c]] == 0) continue;
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= M) continue;
			int next_value = Map[next_r][next_c];
			//���� �������� ������ΰ� �����ִٸ� (�̵� �Ұ����)
			if (DAT[i][next_value] == 0) continue;
			//�̹� �湮�ؼ� ���� �ݿ��ߴ� ����̸� �ǳʶ�
			if (Visited[next_r][next_c] != 0) continue;
			//������� �Ǿ��ִٸ�
			Visited[next_r][next_c] = Visited[now_r][now_c] + 1;
			q.push({ next_r,next_c });
			cnt++;
		}
	}
	return cnt;
}

int solution() {
	return BFS();
}




int main() {

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {

		init();
		input();
		int answer = solution();

		cout << "#" << test << " " << answer << "\n";

	}

	return 0;
}



//******Ż�� �ѽð� �ڴ� ������ ������
//���ĺ���
//���� ����, �̵� ���� ���� ��� ����(������ �־ ��)

//�������� ĭ ���� ����? + �������� -> Visited �迭 �ʿ�