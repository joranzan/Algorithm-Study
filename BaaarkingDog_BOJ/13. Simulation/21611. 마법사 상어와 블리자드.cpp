#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int arr[101] = { 0, };
	int N, M;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		arr[i] = i;
	}

	for (int q = 0; q < M; q++) {
		int i, j;
		cin >> i >> j;

		while (i < j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	for (int i = 1; i <= N; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}
































/*
using namespace std;

//���� �м�

//NxN �� (1x1)
//������ ��� :  ((N+1)/2, (N+1)/2)

//���� (1�� 2�� 3��) => ��� �ִ� ĭ ����
//���� ��ȣ�� ���� ������ ���� -> �����ϴ� ����

//���� ����
//1. d(���� �����¿� 1234) s(�Ÿ�) d�������� �Ÿ��� s������ ��� ĭ�� ���� ����
//2. ���� �ı� �� ��ĭ �� (��ĭ ��Ÿ�� ���� ���ϱ�)
//3. ���� �ı� X

//���� �̵�
//1. �ش� ĭ�� ��ȣ���� 1 ���� ĭ�� ��ĭ�� ���
//2. �ش� ĭ�� ������ ����ĭ���� �̵�

//���� ���� (���� ���� 4�� �̻�)
//1. ���� ���� ���� -> ��ĭ��
//2. ���� �ٽ� �̵�
//3. �� ������ ���� ���� ���� �� ���� �ݺ�
//**************�Ͷ߸����ִ¾ֵ� ��� �Ͷ߸��Ŀ� �ű��********

//���� ��ȭ
//1. �׷� : �����ϴ� ���� 
//2. �ϳ��� �׷� 2���� ������ ��ȭ : { �׷쿡 ����ִ� ������ ����, ������ ��ȣ}
//***������ ĭ �Ѿ�� �����


//��ǥ : ���� 1���� ���� * 1 + ����2���� ���� *2 + ����3���� ���� *3


struct pos {
	int row;
	int col;
	int dir;
};

struct query {
	int d;
	int s;
};

int N, M;
int Map[50][50] = { 0, };
pos ID_Mapping[2500];
query Query[100];
const int dr[5] = { 0,-1,1,0,0 };
const int dc[5] = {0, 0, 0, -1, 1};


void Magic(int d, int s) {
	//���� ����
	//1. d(���� �����¿� 1234) s(�Ÿ�) d�������� �Ÿ��� s������ ��� ĭ�� ���� ����
	//2. ���� �ı� �� ��ĭ �� (��ĭ ��Ÿ�� ���� ���ϱ� : 0)
	//3. ���� �ı� X
}

void Explosion() {
	vector<int> temp1;  
	queue<int> ReadyQ;
	//��� ���߽�Ű��
	pair<int, int> InsideCnt = {0,0}; //������ ����, ����

	for (int i = 1; i < N * N; i++) {
		int nowRow = ID_Mapping[i].row;
		int nowCol = ID_Mapping[i].col;
		if (Map[nowRow][nowCol] == 0) continue; //��ĭ�̸� Continue
		if (InsideCnt.first == 0 && InsideCnt.second == 0) {
			//ù��°�� �׳� �ְ� Continue
			temp1.push_back(Map[nowRow][nowCol]);
			InsideCnt.first = Map[nowRow][nowCol];
			InsideCnt.second = 1;
			continue;
		}

		if (InsideCnt.first == Map[nowRow][nowCol]) {  //���� ĭ�� �����̸�
			//readyQ�� �ֱ�
			ReadyQ.push(Map[nowRow][nowCol]);
			InsideCnt.second++;
		}
		else {  //����ĭ �ٸ� �����̸�
			//1. cnt�� 4�̻��̸� �ȳֱ�
			if (InsideCnt.second >= 4) {
				temp1.pop_back();
				ReadyQ = queue<int>();
			}
			//2. �ƴϸ� �� vector�� �־���
			else {
				while (!ReadyQ.empty()) {
					temp1.push_back(ReadyQ.front());
					ReadyQ.pop();
				}
			}
			//InsideCnt ����
			InsideCnt.first = Map[nowRow][nowCol];
			InsideCnt.second = 1;
			temp1.push_back(Map[nowRow][nowCol]);
		}
	}

	//�� ������ �����ִ� �ֵ�
	if (!ReadyQ.empty()) {
		if (InsideCnt.second >= 4) temp1.pop_back();
		else {
			while (!ReadyQ.empty()) {
				temp1.push_back(ReadyQ.front());
				ReadyQ.pop();
			}
		}
	}

	//*************************************
	//���� ������ �������� Ǯ�� ���� �߻�!
	//Temp���Ϳ� ����ִ� ������ ���� ReadyQ�� �ִ� �� ��� ������ ��
	//���� ���� �̹� ������ ����ִ� ������  ���� ���� ��
	//�̹� ����ִ� ���� ���Ͷ߸�...
	//vector�� ���ӵǴ� ���� ���� �����ؾ��ҵ�..


}

void input() {
	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		Query[i] = { d,s };
	}

	int init_Temp[51][51] = { 0, };
	int init_Row[4] = { (N + 1) / 2, (N + 1) / 2 + 1 , (N + 1) / 2 + 1 , (N + 1) / 2 - 1 };
	int init_Col[4] = { (N + 1) / 2 - 1 , (N + 1) / 2 - 1 , (N + 1) / 2 + 1 ,(N + 1) / 2 + 1 };

	int init_dr[4] = { -1,1,1,-1 };
	int init_dc[4] = { -1,-1,1,1 };
	int dir[4] = { 2,4,1,3 };

	for (int i = 0; i < N/2; i++) {
		for (int j = 0; j < 4; j++) {
			init_Temp[init_dr[j] * i + init_Row[j]][init_dc[j] * i + init_Col[j]] = dir[j];
		}
	}

	
	
	int nowRow = (N + 1) / 2;
	int nowCol = (N + 1) / 2;
	int nowDir = 3;
	init_Temp[nowRow][nowCol] = 0;

	for (int i = 0; i < N * N; i++) {
		if (init_Temp[nowRow][nowCol] != 0) nowDir = init_Temp[nowRow][nowCol];
		ID_Mapping[i] = { nowRow, nowCol, nowDir };
		nowRow += dr[nowDir];
		nowCol += dc[nowDir];
	}

	int debugging = -1;
}
void solution() {

	for (int q = 0; q < M; q++) {
		Magic(Query[q].d, Query[q].s);
		Explosion();
	}

}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

*/