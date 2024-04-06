#include<iostream>
#include<set>
#include<vector>

using namespace std;

//0:��, 1:��, 2:��, 3:��
const int dr[4] = { -1,1,0,0 };  
const int dc[4] = { 0,0,-1,1 };
int Map[100][100] = { 0, };
int TreeMap[100][100] = { 0, };
set<int> RunnerMap[100][100];
int taggerRow = -1;
int taggerCol = -1;
int taggerDir = -1;

struct pos {
	int row;
	int col;
};

struct tagger {
	pos nowPos;
	int dir;    //�ٶ󺸴� �þ�
};

struct runner {
	int runnerId;
	pos nowPos;
	int moveType;    // 1: �¿�  2: ���� 
	int trigger = 0; //�ٶ󺸴� ���� �ٲ������ ����
	int dir[3][2] = { {0,0},{3,2}, {1,0} };  // dir[moveType][trigger] : ���� ����
	bool alive = true;
};

int N, M, H, K;
runner RunnerInfo[10000];
tagger TaggerPath[10000];

void init() {

	cin >> N >> M >> H >> K;
	
	//�ʱ�ȭ
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			RunnerMap[r][c].clear();
			Map[r][c] = 0;
			TreeMap[r][c] = 0;
		}
	}

	for (int i = 0; i < M; i++) {
		int r, c, t;
		cin >> r >> c >> t;
		RunnerInfo[i].runnerId = i;
		RunnerInfo[i].nowPos.row = r;
		RunnerInfo[i].nowPos.col = c;
		RunnerInfo[i].moveType = t;
		RunnerMap[r][c].insert(i);
	}

	for (int i = 0; i < H; i++) {
		int r, c;
		cin >> r >> c;
		TreeMap[r][c] = 1;
	}

	taggerRow = N / 2 + 1;
	taggerCol = N / 2 + 1;
	taggerDir = 0;
	//������ ��� �̸� ���س��� 

	int TempMap[100][100] = { 0, };
	int pathIndex = 0;
	//0:��, 1:��, 2:��, 3:��
	int startRow = N / 2 + 1;
	int startCol = N / 2 + 1;
	int startDir = 0;  //�ٶ󺸴� �þ�

	// 0:��� 1:���� 2:���� 3:�»�
	const int diag_dr[4] = { -1,1,1,-1 };
	const int diag_dc[4] = { 1,1,-1,-1 };

	/*
	������ ���� ��
	1 3 3 3 1
	0 0 3 1 1
	0 0 0 1 1
	0 0 2 2 1
	0 2 2 2 2


	*/
	int temp_r[4] = { startRow,startRow, startRow, startRow};
	int temp_c[4] = { startCol, startCol, startCol, startCol+1 };
	int changedir[4] = { 2,3,1,4 };

	//���� ��ȯ�Ǵ� ĭ ã��
	for (int i = 0; i < 4; i++) {
		while (1) {
			temp_r[i] += diag_dr[i];
			temp_c[i] += diag_dc[i];
			if (temp_r[i] <= 0 || temp_c[i] <= 0 || temp_r[i] > N || temp_c[i] > N) break;
			TempMap[temp_r[i]][temp_c[i]] = changedir[i];
		}
	}
	TempMap[N / 2 + 1][N / 2 + 1] = 1;
	int nowRow = startRow;
	int nowCol = startCol;
	int nowDir = TempMap[nowRow][nowCol];

	//���� ��ο� �߰�
	while (nowRow != 1 || nowCol != 1) {
		
		if (TempMap[nowRow][nowCol] != 0){
			nowDir = TempMap[nowRow][nowCol];
		}

		TaggerPath[pathIndex].dir = nowDir-1;
		TaggerPath[pathIndex].nowPos.row = nowRow;
		TaggerPath[pathIndex].nowPos.col = nowCol;

		pathIndex++;

		nowRow += dr[nowDir - 1];
		nowCol += dc[nowDir - 1];

	}

	//(1,1) ĭ�� �߰����ֱ�
	TempMap[nowRow][nowCol] = 2;
	nowDir = 2;
	TaggerPath[pathIndex].nowPos.row = nowRow;
	TaggerPath[pathIndex].nowPos.col = nowCol;
	TaggerPath[pathIndex].dir = 1;
	pathIndex++;

	//�ݴ���� ��� �߰��ϱ�
	
	int temp_r_rv[4] = { startRow,startRow, startRow, startRow };
	int temp_c_rv[4] = { startCol, startCol, startCol, startCol + 1 };
	changedir[0] = 3;
	changedir[1] = 1;
	changedir[2] = 4;
	changedir[3] = 2;

	for (int i = 0; i < 4; i++) {
		while (1) {
			temp_r_rv[i] += diag_dr[i];
			temp_c_rv[i] += diag_dc[i];
			if (temp_r_rv[i] <= 0 || temp_c_rv[i] <= 0 || temp_r_rv[i] > N || temp_c_rv[i] > N) break;
			TempMap[temp_r_rv[i]][temp_c_rv[i]] = changedir[i];
		}
	}

	/*
	2 2 3 3 3
	2 2 2 3 1
	2 2 1 1 1
	2 4 4 1 1
	4 4 4 4 1
	
	*/


	//(2,1)���� ����
	nowRow += dr[nowDir - 1];
	nowCol += dc[nowDir - 1];
	
	nowDir = 2;
	while (nowRow != N / 2 + 1 || nowCol != N / 2 + 1) {
		if (TempMap[nowRow][nowCol] != 0) {
			nowDir = TempMap[nowRow][nowCol];
		}

		TaggerPath[pathIndex].dir = nowDir - 1;
		TaggerPath[pathIndex].nowPos.row = nowRow;
		TaggerPath[pathIndex].nowPos.col = nowCol;
		pathIndex++;

		nowRow += dr[nowDir - 1];
		nowCol += dc[nowDir - 1];
	}

	int debugging = -1;
}

void runnerMove() {

	/*
	1) m���� ������ "����"�� ������  (�ٶ� ���� 1ĭ)
	-  (|x1 - x2| + |y1 - y2| <=3) ���� �����ϴ� ������
	-  1) ���ڸ� ����� �ʴ� ���
		- ������ �ִٸ� �������� ����
		- �����־ �׳� ��
	-  2) ���� ����� ���
		- ���� �ݴ�� Ʋ��
		- �������ٸ� �� ���� 1ĭ �̵�
	*/

	for (int i = 0; i < M; i++) {
		if (!RunnerInfo[i].alive) continue;
		int nowRow = RunnerInfo[i].nowPos.row;
		int nowCol = RunnerInfo[i].nowPos.col;
		//(|x1 - x2| + |y1 - y2| <=3) ���� �����ϴ� ������
		int dist = abs(taggerRow - nowRow) + abs(taggerCol - nowCol);
		if (dist > 3) continue;

		int nextRow = nowRow + dr[RunnerInfo[i].dir[RunnerInfo[i].moveType][RunnerInfo[i].trigger]];
		int nextCol = nowCol + dc[RunnerInfo[i].dir[RunnerInfo[i].moveType][RunnerInfo[i].trigger]];
		
		//1) ���ڸ� ����� �ʴ� ���
		if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) {
			if (RunnerInfo[i].trigger == 1) RunnerInfo[i].trigger = 0;
			else if (RunnerInfo[i].trigger == 0) RunnerInfo[i].trigger = 1;
			nextRow = nowRow + dr[RunnerInfo[i].dir[RunnerInfo[i].moveType][RunnerInfo[i].trigger]];
			nextCol = nowCol + dc[RunnerInfo[i].dir[RunnerInfo[i].moveType][RunnerInfo[i].trigger]];
		}
		//���� �ִٸ� �ڸ� ����
		if (taggerRow == nextRow && taggerCol == nextCol) {
			continue;
		}
		//���� ���ٸ� �̵�
		else {
			//�����ڰ� ��ĥ���� ����....
			RunnerMap[nowRow][nowCol].erase(i);
			RunnerInfo[i].nowPos.row = nextRow;
			RunnerInfo[i].nowPos.col = nextCol;
			RunnerMap[nextRow][nextCol].insert(RunnerInfo[i].runnerId);
		}
	}
}

void taggerMove(int turn) {
	int maxPathIndex = N * N * 2 - 2;
	turn %= maxPathIndex;

	taggerRow = TaggerPath[turn].nowPos.row;
	taggerCol = TaggerPath[turn].nowPos.col;
	taggerDir = TaggerPath[turn].dir;

}

int catchRunner() {

	/*
	3) �þ� ���� ������ ���
	- ������ 3ĭ(���ڹ� ����ó��) *****
	- �ٶ󺸴� ���� 3ĭ�� �ִ� ������ ����
	- ������ �����ϴ� ��� �������� �Ⱥ��� (continue)
	- ���� ���� (t��° �� x ���� �Ͽ��� ���� ������ ��)
	*/
	int cnt = 0;

	for (int i = 0; i < 3; i++) {
		//������ 3ĭ(���ڹ� ����ó��) * ****
		int nowRow = taggerRow + i * dr[taggerDir];
		int nowCol = taggerCol + i * dc[taggerDir];
		if (nowRow <= 0 || nowCol <= 0 || nowRow > N || nowCol > N) break;
		//������ ���ٸ� ����
		if (RunnerMap[nowRow][nowCol].empty()) continue;

		//������ �����ϴ� ��� �������� �Ⱥ��� (continue)
		if (TreeMap[nowRow][nowCol] == 1) continue;

		//�ش� �ڸ��� �ִ� ������ ��� Ž��
		vector<int> DeadRunner;
		for (auto it = RunnerMap[nowRow][nowCol].begin(); it != RunnerMap[nowRow][nowCol].end(); it++) {
			if (!RunnerInfo[*it].alive) continue;
			//������ ���
			RunnerInfo[*it].alive = false;
			DeadRunner.push_back(*it);
			cnt++;
		}
		
		for (int j = 0; j < DeadRunner.size(); j++) {
			RunnerMap[nowRow][nowCol].erase(DeadRunner[j]);
		}
	}

	return cnt;
}

void solution() {

	int score = 0;

	for (int k = 1; k <= K; k++) {
		//������ �̵�
		runnerMove();
		int debugging = -1;
		//���� �̵�
		taggerMove(k);
		debugging = -1;
		//������ ���
		//���� ���� (t��° �� x ���� �Ͽ��� ���� ������ ��)
		score += catchRunner() * k;
		
		debugging = -1;

		
	}
	cout << score << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	solution();

	return 0;
}

/*
���� �м�

�� : NxN  (100�̸�) �ݵ�� Ȧ��   (1,1) (N,N)
------------------------------------------------
������ : M�� (1�̻� N^2 ����)

	- �߾ӿ��� ���� ����
	- (��/��): ������ �ٶ󺸰� ����
	- (��/��): �Ʒ��� �ٶ󺸰� ����
------------------------------------------------
������ġ : H�� (1�̻� N^2 ����)

	- �����ڿ� �ʱ⿡ �������� �־����� �� ����
-------------------------------------------------	
���� : ���߾� ���� (N/2+1)

=================================================

������� ���� ����
K�� �ݺ�(100����)
1) m���� ������ "����"�� ������  (�ٶ� ���� 1ĭ)
	-  (|x1 - x2| + |y1 - y2| <=3) ���� �����ϴ� ������
	-  1) ���ڸ� ����� �ʴ� ���
		- ������ �ִٸ� �������� ����
		- �����־ �׳� ��
	-  2) ���� ����� ���
		- ���� �ݴ�� Ʋ��
		- �������ٸ� �� ���� 1ĭ �̵�
========================================================

2) ���� ������ (������ ����) -> Mapping �ؾ���
	- ������ ���� 1ĭ �̵� (dir ����)
	- ���� ��ġ (N/2+1,N/2+1)
	*******************
	- 1ĭ �̵� �� �̵������� Ʋ������ ������ ��� -> �ٷ� ���� Ʋ��
	- (1,1), (N/2+1,N/2+1) ������ ���� �ٷ� Ʋ�����
	******************
==================================================================
3) �þ� ���� ������ ���
	- ������ 3ĭ(���ڹ� ����ó��) *****
	- �ٶ󺸴� ���� 3ĭ�� �ִ� ������ ����
	- ������ �����ϴ� ��� �������� �Ⱥ��� (continue)
	- ���� ���� (t��° �� x ���� �Ͽ��� ���� ������ ��)
=========================================================================
3) �� ����

==============================================================

�Է� : 
r, c , d (d: 1(�¿�) 2(����))


*/

/*
�ʿ��� ����



*/