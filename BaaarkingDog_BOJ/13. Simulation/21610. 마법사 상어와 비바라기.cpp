#include<iostream>
#include<vector>

using namespace std;

//���� �м�


//NxN �� (���� �� -> ���� ����) (1,1)
//1�� N ����

//��ٶ�� ����
//1) �񱸸� :  (N, 1), (N, 2), (N-1, 1), (N-1, 2)


//M�� ���
// d(����) s(�Ÿ�)
//1) ��� ������ d �������� sĭ  �̵�
//2) �� ������ �� ���� ���� �ִ� ĭ ���� �� += 1
//3) ������ ��� �����
//4) ������ ���� (��� : 2������ ������ �ֵ�)
	//1. �밢�� �������� �Ÿ� 1�� ĭ �� ���� �ִ� ĭ �� ��ŭ ++
//5) 2�̻��� ��� ĭ�� ���� �ٽ� ����
//6) ���� ���� ĭ�� �� -=2 (3������ ����ĭ ����)

struct query {
	int d;
	int s;
};

struct pos {
	int row;
	int col;
};


int N, M;
int Map[51][51] = { 0, };
query Query[101];
int Cloud[51][51] = { 0, };
vector<pos> CloudPos;

void moveCloud(int d, int s) {
	const int dr[9] = {0, 0,-1,-1,-1,0,1,1,1 };
	const int dc[9] = {0, -1,-1,0,1,1,1,0,-1 };

	vector<pos> temp;

	int moveCnt = s % N;

	for (int i = 0; i < CloudPos.size(); i++) {
		int nowRow = CloudPos[i].row;
		int nowCol = CloudPos[i].col;

		Cloud[nowRow][nowCol] = 0;

		int nextRow = nowRow + dr[d] * moveCnt;
		int nextCol = nowCol + dc[d] * moveCnt;
		if (nextRow > N) nextRow -= N;
		else if (nextRow <= 0) nextRow += N;
		if (nextCol > N) nextCol -= N;
		else if (nextCol <= 0) nextCol += N;

		temp.push_back({ nextRow,nextCol });
	}

	CloudPos.clear();

	for (int i = 0; i < temp.size(); i++) {
		CloudPos.push_back(temp[i]);
		//������ �ִ� �ڸ� ���
		Cloud[temp[i].row][temp[i].col] = 1;
		//2) �� ������ �� ���� ���� �ִ� ĭ ���� �� += 1
		Map[temp[i].row][temp[i].col] += 1;
	}

	int debugging =  -1;
}
void copyWater() {
	const int dr[4] = { -1,-1,1,1 };
	const int dc[4] = { -1,1,-1,1 };

	for (int i = 0; i < CloudPos.size(); i++) {
		int nowRow = CloudPos[i].row;
		int nowCol = CloudPos[i].col;
		int nowCnt = 0;
		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Map[nextRow][nextCol] > 0) nowCnt++;
		}
		Map[nowRow][nowCol] += nowCnt;
	}

}
void makeCloud() {

	vector<pos> Next;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (Map[r][c] <= 1) continue;
			if (Cloud[r][c] == 1) continue;
			Next.push_back({ r,c });
			Map[r][c] -= 2;
		}
	}

	for (int i = 0; i < CloudPos.size(); i++) {
		if (Cloud[CloudPos[i].row][CloudPos[i].col] != 1) {
			int debugging = -1;
		}
		Cloud[CloudPos[i].row][CloudPos[i].col] = 0;
	}

	CloudPos.clear();

	for (int i = 0; i < Next.size(); i++) {
		CloudPos.push_back(Next[i]);
	}

}

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}
	for (int i = 1; i <= M; i++) {
		int d, s;
		cin >> d >> s;
		Query[i] = { d,s };
	}

	CloudPos.push_back({ N,1 });
	CloudPos.push_back({ N,2 });
	CloudPos.push_back({ N - 1,1 });
	CloudPos.push_back({ N - 1,2 });
	Cloud[N][1] = 1;
	Cloud[N][2] = 1;
	Cloud[N - 1][1] = 1;
	Cloud[N - 1][2] = 1;
	
}

void solution() {

	for (int q = 1; q <= M; q++) {
		
		//������ ��� �Ǵ±���
		//�̵��� �� �ִ� ������ ���� ���
		moveCloud(Query[q].d, Query[q].s);
		copyWater();
		makeCloud();
	}

	int Answer = 0;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			Answer += Map[r][c];
			
		}
	}

	cout << Answer;

}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();


	return 0;
}