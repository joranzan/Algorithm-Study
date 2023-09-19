#include<iostream>
#include<vector>

using namespace std;
//�ð����
// 0
//3 1
// 2

//CCTV 5���� ����
//1��: 1
//2��: 1 3     //2�� ȸ��    
//3��: 0 1
//4��: 0 1 3
//5��: 0 1 2 3  //�ȵ����� ��

struct pos {
	int row;
	int col;
	int info;
};

int N, M;
int Map[8][8] = { 0, }; 
int Result[8][8] = { 0, }; //CCTV�� �ٶ󺸴� �� 1�� �ٲٱ�
int Answer = 2112345678;
vector<pos> CCTV;   //CCTV ��ǥ
void FloodFill(int row, int col, int dir);


int Rotation[6][7] = {  // 0 1 2 3 0 1 2
	{0,0,0,0,0,0,0},
	{0,1,0,0,0,1,0},
	{0,1,0,1,0,1,0},  //��� 1��ŭ�� ������ ��
	{1,1,0,0,1,1,0},
	{1,1,0,1,1,1,0},
	{1,1,1,1,0,0,0}   //�ȵ����� ��
};
//�� �� �� ��
const int dr[4] = { -1,0,1,0 };
const int dc[4] = { 0,1,0,-1 };

//BackTracking
void BackTracking(int depth) {

	if (depth >= CCTV.size()) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (Result[i][j] == 0) cnt++;
			}
		}
		Answer = min(Answer, cnt);
		return;
	}

	int cctvNum = CCTV[depth].info;
	int nowRow = CCTV[depth].row;
	int nowCol = CCTV[depth].col;

	int Result_temp[8][8] = { 0, };  //���� Result�� ��Ƶδ� �迭

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Result_temp[i][j] = Result[i][j];
		}
	}

	if (cctvNum == 2) {  //1��ŭ�� ������
		for (int i = 0; i < 2; i++) {
			for (int dir = i; dir < i + 4; dir++) { //�׹��� ������
				if (Rotation[cctvNum][dir] == 0) continue;

				//�ش� ���� ä��� �Լ�
				FloodFill(nowRow, nowCol, dir - i);
			}
			BackTracking(depth + 1);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					Result[i][j] = Result_temp[i][j];
				}
			}
		}
	}
	else if (cctvNum == 5) { //�ȵ�������
		for (int dir = 0; dir < 4; dir++) { //�׹��� ������
			if (Rotation[cctvNum][dir] == 0) continue;

			//�ش� ���� ä��� �Լ�
			FloodFill(nowRow, nowCol, dir);
		}
		BackTracking(depth + 1);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				Result[i][j] = Result_temp[i][j];
			}
		}
	}
	else { //�׹��� �� ��������
		for (int i = 0; i < 4; i++) {
			for (int dir = i; dir < i + 4; dir++) { //�׹��� ������
				if (Rotation[cctvNum][dir] == 0) continue;
				
				//�ش� ���� ä��� �Լ�
				FloodFill(nowRow, nowCol, dir - i);
			}
			BackTracking(depth + 1);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					Result[i][j] = Result_temp[i][j];
				}
			}
		 }
	}
}

void FloodFill(int row, int col, int dir) {

	int nowRow = row;
	int nowCol = col;
	while (1) {

		int nextRow = nowRow + dr[dir];
		int nextCol = nowCol + dc[dir];
		if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M) break;
		if (Map[nextRow][nextCol] == 6) break;
		Result[nextRow][nextCol] = 1;
		nowRow = nextRow;
		nowCol = nextCol;
	}
}


int main() {


	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] >= 1 && Map[i][j] <= 5) {
				CCTV.push_back({ i,j, Map[i][j]});
				Result[i][j] = 1;
			}
			else if (Map[i][j] == 6) {
				Result[i][j] = -1;
			}
		}
	}

	BackTracking(0);
	cout << Answer;

	return 0;
}