#include<iostream>
#include<vector>
#include<queue>

using namespace std;



/*
�ʿ��� �ڷᱸ��

1. ������ü ������ : �迭


*/

struct pos {
	int row;
	int col;
};

struct TimeDisaster {
	int row;
	int col;
	int dir;    //���� (�����ϻ�)
	int valid;  //Ȯ�� ���
};

struct secondpos {
	pos nowPos;
	int nowTurn = 0;
};

int N, M, F;
int TimeWall[55][55] = { 0, }; //������ü ������
int UnknownSpace[21][21] = { 0, };

pos EscapePos = { -1,-1 };  //�����ǰ������� Ż�ⱸ
pos StartPosTimeWall;
pos EscapePosTimeWall; //�ð��Ǻ����� Ż�ⱸ�� �����ִ� ��
pos EndPos;
TimeDisaster TimeDisasterInfo[1000];
int TurnNum = 0;

bool input() {

	TurnNum = 0;
	
	cin >> N >> M >> F;


	pos TimeWallStartPos;  //�ð��Ǻ� ������ġ
	
	int started = 0; //�ð��Ǻ� ��ġ ã��

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> UnknownSpace[r][c];
			if (UnknownSpace[r][c] == 3 && !started) {
				TimeWallStartPos = { r,c };
				started = 1;
			}
			if (UnknownSpace[r][c] == 4) {
				EndPos = { r,c };
			}
		}
	}

	//Ż�ⱸ ã��
	for (int r = -1; r <= M; r++) {
		for (int c = -1; c <= M; c++) {
			int nowRow = TimeWallStartPos.row + r;
			int nowCol = TimeWallStartPos.col + c;
			if (nowRow < 0 || nowCol < 0 || nowRow >= N || nowCol >= N) continue;
			if (UnknownSpace[nowRow][nowCol] != 0) continue;
			EscapePos.row = nowRow;
			EscapePos.col = nowCol;
		}
		if (EscapePos.row != -1 || EscapePos.col != -1) break;
	}
	
	

	//Ż�ⱸ ������ false ��ȯ
	if (EscapePos.row == -1 || EscapePos.col == -1) {
		return false;
	}

	//�����ִ� �� ã��
	//��
	if (EscapePos.row < TimeWallStartPos.row) {
		EscapePosTimeWall.row = 0;
		EscapePosTimeWall.col = M + (EscapePos.col - TimeWallStartPos.col);
	}
	//��
	else if (EscapePos.row > TimeWallStartPos.row + M - 1) {
		EscapePosTimeWall.row = 3 * M - 1;
		EscapePosTimeWall.col = M + (EscapePos.col - TimeWallStartPos.col);
	}
	//��
	else if (EscapePos.col < TimeWallStartPos.col) {
		EscapePosTimeWall.col = 0;
		EscapePosTimeWall.row = M + (EscapePos.row - TimeWallStartPos.row);
	}
	//��
	else if (EscapePos.col > TimeWallStartPos.col + M - 1) {
		EscapePosTimeWall.col = 3 * M - 1;
		EscapePosTimeWall.row = M + (EscapePos.row - TimeWallStartPos.row);
	}
	
	


	int debugging = -1;

	//�ð��Ǻ� ������ �ʱ�ȭ
	for (int r = 0; r < 3 * M; r++) {
		for (int c = 0; c < 3 * M; c++) {
			TimeWall[r][c] = -1;
		}
	}
	//�� : �·� 90�� ȸ�� �� ����(2M���� 3M-1����), ���� (M, 2M-1)����

	for (int r = 0; r < M; r++) {
		for (int c = 0; c < M; c++) {
			cin >> TimeWall[2 * M - 1 - c][2 * M + r];
		}
	}

	//�� : ��� 90�� ȸ�� �� ���� (M-1���� 0����), ���� (M, 2M-1)����

	for (int r = 0; r < M; r++) {
		for (int c = 0; c < M; c++) {
			cin >> TimeWall[M + c][M - 1 - r];
		}
	}

	//��
	for (int r = 0; r < M; r++) {
		for (int c = 0; c < M; c++) {
			cin >> TimeWall[2 * M + r][M + c];
		}
	}

	//�� : 180�� ȸ�� �� ���� : 
	for (int r = 0; r < M; r++) {
		for (int c = 0; c < M; c++) {
			cin >> TimeWall[M - 1 - r][2 * M -1 - c];
		}
	}

	//����
	for (int r = 0; r < M; r++) {
		for (int c = 0; c < M; c++) {
			cin >> TimeWall[M + r][M + c];
			if (TimeWall[M + r][M + c] == 2) {
				StartPosTimeWall.row = M + r;
				StartPosTimeWall.col = M + c;
			}
		}
	}

	for (int i = 0; i < F; i++) {
		cin >> TimeDisasterInfo[i].row >> TimeDisasterInfo[i].col >> TimeDisasterInfo[i].dir >> TimeDisasterInfo[i].valid;
	}


	return true;
}


pos Mapping(int nowRow, int nowCol, int nextRow, int nextCol) {

	pos ret = { -1,-1 };
	//���� �ϸ��϶�
	if (nowRow >= 0 && nowRow < M && nowCol >= M && nowCol < 2 * M) {
		if (nextCol < M) {
			ret.row = M;
			ret.col = nextRow;
		}
		else if (nextCol >= 2 * M) {
			ret.row = M;
			ret.col = 3 * M - 1 - nextRow;
		}
		else {
			ret = { nextRow, nextCol };
		}
	}
	//���� �����϶�
	else if (nowRow >= 2 * M && nowRow < 3 * M && nowCol >= M && nowCol < 2 * M) {
		if (nextCol < M) {
			ret.row = 2 * M - 1;
			ret.col = 3 * M - 1 - nextRow;
		}
		else if (nextCol >= 2 * M) {
			ret.row = 2 * M - 1;
			ret.col = nextRow;
		}
		else {
			ret = { nextRow, nextCol };
		}
	}
	//���� �����϶�
	else if (nowRow >= M && nowRow<2 * M && nowCol >= 0 && nowCol < M) {
		if (nextRow < M) {  //���� ���
			ret.row = nextCol;
			ret.col = M;
		}
		else if (nextRow >= 2 * M) {  //�Ʒ��� ���
			ret.row = 3 * M - 1 - nextCol;
			ret.col = M;
		}
		else {
			ret = { nextRow, nextCol };
		}
	}
	//���� �����϶�
	else if (nowRow >= M && nowRow < 2 * M && nowCol >= 2*M && nowCol < 3 * M) {
		if (nextRow < M) {  //���� ���
			ret.row = 3 * M - 1 - nextCol;
			ret.col = 2 * M - 1;
		}
		else if (nextRow >= 2 * M) {  //�Ʒ��� ���
			ret.row = nextCol;
			ret.col = 2 * M - 1;
		}
		else {
			ret = { nextRow, nextCol };
		}
	}
	else {
		ret.row = nextRow;
		ret.col = nextCol;
	}

	return ret;
}


bool findShortestTimeWall() {
	//StartPosTimeWall ���� EscapePosTimeWall���� �ִ� �Ÿ�

	//*******************************
	//���������� �������� ����� �̾������� Mapping �Լ� ¥����

	queue<pos> q;
	int Visited[55][55] = {0,};
	int dr[4] = { -1,1,0,0 };
	int dc[4] = { 0,0,-1,1 };
	
	q.push(StartPosTimeWall);
	Visited[StartPosTimeWall.row][StartPosTimeWall.col] = 1;


	while (!q.empty()) {

		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		if (nowRow == EscapePosTimeWall.row && nowCol == EscapePosTimeWall.col) break;

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow < 0 || nextCol < 0 || nextRow >= 3 * M || nextCol >= 3 * M) continue;
			pos nextPos = Mapping(nowRow, nowCol, nextRow, nextCol);
			nextRow = nextPos.row;
			nextCol = nextPos.col;
			if (TimeWall[nextRow][nextCol] != 0) continue;
			if (Visited[nextRow][nextCol]!=0) continue;
			Visited[nextRow][nextCol] = Visited[nowRow][nowCol] + 1;
			q.push({ nextRow,nextCol });
		}
	}


	if (Visited[EscapePosTimeWall.row][EscapePosTimeWall.col] == 0) {
		return false;
	}
	else {
		TurnNum = Visited[EscapePosTimeWall.row][EscapePosTimeWall.col] - 1;
		return true;
	}

}


bool MoveUnknownSpace() {

	queue <secondpos> q;
	q.push({ { EscapePos.row, EscapePos.col }, 1 });
	int CurrentTurn = 1;
	int Visited[20][20] = { 0, };
	Visited[EscapePos.row][EscapePos.col] = 1;

	while (!q.empty()) {
		

		//�ð��̻� �̵�
		int dr[4] = { 0,0,1,-1 };
		int dc[4] = { 1,-1,0,0 };
		for (int i = 0; i < F; i++) {
			if (TimeDisasterInfo[i].valid == -1) continue;
			if ((TurnNum + CurrentTurn) % TimeDisasterInfo[i].valid == 0) {
				int nextRow = TimeDisasterInfo[i].row + dr[TimeDisasterInfo[i].dir];
				int nextCol = TimeDisasterInfo[i].col + dc[TimeDisasterInfo[i].dir];
				//���� �ð��̻��� �� ������ Ȯ��ȴٸ� ����
				if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) {
					TimeDisasterInfo[i].valid = -1;
					continue;
				}
				//���� ������� �ƴ϶�� Ȯ�� ����
				if (UnknownSpace[nextRow][nextCol] > 0 && UnknownSpace[nextRow][nextCol] < 100) {
					TimeDisasterInfo[i].valid = -1;
					continue;
				}

				//Ȯ�� �����ϴٸ�
				TimeDisasterInfo[i].row = nextRow;
				TimeDisasterInfo[i].col = nextCol;
				UnknownSpace[nextRow][nextCol] = 100;
			}
			
		}
		while (q.front().nowTurn == CurrentTurn) {
			int nowRow = q.front().nowPos.row;
			int nowCol = q.front().nowPos.col;
			int nowTurn = q.front().nowTurn;
			q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int nextRow = nowRow + dr[dir];
				int nextCol = nowCol + dc[dir];
				if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) continue;
				if (Visited[nextRow][nextCol] != 0) continue;
				if (UnknownSpace[nextRow][nextCol] == 4) {
					TurnNum += nowTurn;
					return true;
				}
				if (UnknownSpace[nextRow][nextCol] != 0) continue;

				Visited[nextRow][nextCol] = nowTurn + 1;
				q.push({ {nextRow,nextCol}, nowTurn + 1 });

				
			}
			if (q.empty()) break;
		}
		CurrentTurn++;
		
	}

	

	/*
	1. �̵��� �� �ִ� �ð��̻����� �̵�
	2. queue�� ��� �ֵ� �� ����ܰ� �̵�
	
	
	
	*/
	


	return false;

}

bool solution() {

	bool TimeWallisValid = findShortestTimeWall();
	int debugging = -1;
	if (TimeWallisValid) {
		//�ð��̻� TurnNum+1 ��ŭ �ű�� (���� Ÿ�Ӹӽ��� �ð��� ���� ����)

		for (int i = 0; i < F; i++) {
			UnknownSpace[TimeDisasterInfo[i].row][TimeDisasterInfo[i].col] = 100;
		}


		for (int nowtime = 1; nowtime <= TurnNum + 1; nowtime++) {
			//(�����ϻ�)
			int dr[4] = { 0,0,1,-1 };
			int dc[4] = { 1,-1,0,0 };
			for (int i = 0; i < F; i++) {
				if (TimeDisasterInfo[i].valid == -1) continue;
				if (nowtime % TimeDisasterInfo[i].valid == 0) {  //����϶���
					int nextRow = TimeDisasterInfo[i].row + dr[TimeDisasterInfo[i].dir];
					int nextCol = TimeDisasterInfo[i].col + dc[TimeDisasterInfo[i].dir];
					//���� �ð��̻��� �� ������ Ȯ��ȴٸ� ����
					if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) {
						TimeDisasterInfo[i].valid = -1;
						continue;
					}
					//���� ������� �ƴ϶�� Ȯ�� ����
					if (UnknownSpace[nextRow][nextCol] > 0 && UnknownSpace[nextRow][nextCol]<100) {
						TimeDisasterInfo[i].valid = -1;
						continue;
					}

					//Ȯ�� �����ϴٸ�
					TimeDisasterInfo[i].row = nextRow;
					TimeDisasterInfo[i].col = nextCol;
					UnknownSpace[nextRow][nextCol] = 100;
				}
			}
		}

		int debugging = -1;
		//Ż�ⱸ�� �����ٸ� False
		if (UnknownSpace[EscapePos.row][EscapePos.col] == 100) {
			//cout << "-1";
			return false;
		}
		
		//������� �Ѿ���� ����
		TurnNum++; 

		//��鿡�� �̵��ϴ� �Լ�
		return MoveUnknownSpace();
	}
	else {
		//cout << "-1";
		return false;
	}

}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	bool isValid = input();

	if (!isValid) {
		cout << "-1";
	}
	else {
		if (solution()) {
			cout << TurnNum;
		}
		else cout << "-1";
	}

	return 0;
}



/*
[������ ���� Ż�� �����м�]

�� : NxN
�̼� : Ÿ�Ӹӽ� Ÿ�� ���� Ż��

����)
1. �� : NxN
2. �ð��� ��(������ü) �Ѻ� : M

Ÿ�Ӹӽ� ��ĵ���

1) ������鵵 : ������ �� ����
2) �ð��� �� �ܸ鵵 : ����, ��������
3) 0(�� ����)�� 1(��ֹ�)
4) �ð��Ǻ��� �����ǰ��� �´��� �κ��� ��ֹ� (�ϳ��� Ż�ⱸ)


Ÿ�Ӹӽ� �̵�
1) Ÿ�Ӹӽ��� �����(0)�� �̵� ���� (��ֹ� X)
2) �ʱ� ��ġ : �ð��� �� ���� (2�� ǥ��)
3) ��鵵�� �ð��� �� ��ġ (3)
4) ��鵵�� Ż�ⱸ ��ġ (4) -> �ð��� �� �ܺο� �ִ� ������ ������ �ٴ�
5) �̵�
	- �� �ϸ��� �����¿� �̵�
	- �ð��̻����� ���ؾ���
	- �ð� �̻� ������ Ȯ��� ���� Ÿ�Ӹӽ��� �̵�
		-> Ÿ�Ӹӽ��� �ð� �̻� ������ Ȯ��Ǵ� ������ �̵��� �� ������ ����



�ð��̻����� : �����ǰ��� �ٴڿ� F����
1) �ٴ��� �� ���� r,c���� ����
2) �� v�� ��� �� ���� ���� d�� Ȯ��
	- ���� ��ġ ������� �ʰ� ����
	- ��������θ� Ȯ��
	- ���̻� Ȯ���� �� ���ٸ� ����
	- **���ÿ� Ȯ��
3) ���� : 0123 �������� �����ϻ�


���
	- Ż�� �ּ� �ð�(�� ��)
	- Ż���� �� ���ٸ� -1


�Է�
1) N M F
2) N���� �ٿ� �����ǰ��� ��鵵
3) ���������� ��鵵 ���� M��
3) F�ٿ� ���� (r,c) d v




**�ùķ��̼�

      1 1 1
      0 0 1
      0 0 0    
1 1 1 2 0 0 1 0 1
1 0 1 0 1 0 1 0 1
1 1 1 0 0 0 1 0 0
      0 0 1
	  1 0 0
	  1 0 1


Ż�ⱸ�� �´���ִ� �� ã��**
*/