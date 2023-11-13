#include<iostream>
#include<vector>

using namespace std;

//NxN ü����
// ���, ������, �Ķ���
//
 
//�� (���� : K��) 1~k��
//1) ���� ���
//2) �ϳ��� �� ���� �ٸ� �� �ø��� ����
//3) �����¿�(�̵����� �־���)


//�̵� (����ĭ)
//1. ��� ĭ�� ���
	//1) �ϴ� �̵�
	//2) �̹� �� ���� -> ���� ���� �ø�
	//3) ���� �ִ� �� ��� �̵�

//2. ������ ���
	//1) ������ ĭ �̵� (��� �� ����)
	//2) ���� ���� �ݴ�� �ٲ� (�̵��� �ֵ鸸)
	
//3. �Ķ��� ��� (==�� ��� ���)
	//1) A�� ���� �̵� ���� �ݴ�
	//2) �� �Ķ��� ��� �̵� X
	//3) �̵�


//�� 1�� : 1������ K�� �� �̵� 
//���� 4�� �̻� ���̸� �׳� ����


struct Info {
	int row;
	int col;
	int dir;
};


void input();


const int dr[5] = { 0,0,0,-1,1 };
const int dc[5] = { 0,1,-1,0,0 };
const int Oppdir[5] = { 0,2,1,4,3 };

int N, K;
int Map[13][13] = { 0, };
Info Horse[10];   //���� N�� ���� ��ġ ����
vector<int> StackedMap[13][13];  //�� ���� ����

bool Exit = false;

void White(int num) {
	//1. ��� ĭ�� ���
	//1) �ϴ� �̵�
	//2) �̹� �� ���� -> ���� ���� �ø�
	//3) ���� �ִ� �� ��� �̵�
	int nowRow = Horse[num].row;
	int nowCol = Horse[num].col;
	int nowDir = Horse[num].dir;
	int nextRow = nowRow + dr[nowDir];
	int nextCol = nowCol + dc[nowDir];

	vector<int> temp;

	while (1) {
		temp.push_back(StackedMap[nowRow][nowCol].back());
		StackedMap[nowRow][nowCol].pop_back();
		if (temp.back() == num) break;
	}

	for (int i = temp.size()-1; i >=0; i--) {
		Horse[temp[i]].row = nextRow;
		Horse[temp[i]].col = nextCol;
		StackedMap[nextRow][nextCol].push_back(temp[i]);
	}

	if (StackedMap[nextRow][nextCol].size() >= 4) Exit = true;

}

void Red(int num) {
	//2. ������ ���
	//1) ������ ĭ �̵� (��� �� ����)
	//2) ���� ���� �ݴ�� �ٲ� (�̵��� �ֵ鸸)

	int nowRow = Horse[num].row;
	int nowCol = Horse[num].col;
	int nowDir = Horse[num].dir;
	int nextRow = nowRow + dr[nowDir];
	int nextCol = nowCol + dc[nowDir];

	vector<int> temp;
	while (1) {
		temp.push_back(StackedMap[nowRow][nowCol].back());
		StackedMap[nowRow][nowCol].pop_back();
		if (temp.back() == num) break;
	}

	for (int i = 0; i <temp.size(); i++) {
		Horse[temp[i]].row = nextRow;
		Horse[temp[i]].col = nextCol;
		StackedMap[nextRow][nextCol].push_back(temp[i]);
	}

	if (StackedMap[nextRow][nextCol].size() >= 4) Exit = true;

}

void Blue(int num) {
	//3. �Ķ��� ��� (==�� ��� ���)
	//1) A�� ���� �̵� ���� �ݴ�
	//2) �� �Ķ��� ��� �̵� X
	//3) �̵�

	int nowDir = Horse[num].dir;
	nowDir = Oppdir[nowDir];
	Horse[num].dir = nowDir;

	int nowRow = Horse[num].row;
	int nowCol = Horse[num].col;

	int nextRow = nowRow + dr[nowDir];
	int nextCol = nowCol + dc[nowDir];
	
	if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) return;
	if (Map[nextRow][nextCol] == 2) return;

	vector<int> temp;
	while (1) {
		temp.push_back(StackedMap[nowRow][nowCol].back());
		StackedMap[nowRow][nowCol].pop_back();
		if (temp.back() == num) break;
	}

	for (int i = temp.size() - 1; i >= 0; i--) {
		Horse[temp[i]].row = nextRow;
		Horse[temp[i]].col = nextCol;
		StackedMap[nextRow][nextCol].push_back(temp[i]);
	}

	if (StackedMap[nextRow][nextCol].size() >= 4) Exit = true;


}




void solution() {


	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= K; j++) {  //1 ~ K������
			if (i == 7) {
				int debugging = -1;
			}
			int nowRow = Horse[j].row;
			int nowCol = Horse[j].col;
			int nowDir = Horse[j].dir;

			int nextRow = nowRow + dr[nowDir];
			int nextCol = nowCol + dc[nowDir];


			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) {
				Blue(j);
			}
			else if (Map[nextRow][nextCol] == 0) {
				White(j);
			}
			else if (Map[nextRow][nextCol] == 1) {
				Red(j);
			}
			else if (Map[nextRow][nextCol] == 2) {
				Blue(j);
			}

			if (Exit) {
				cout << i;
				return;
			}

		}
	}
	cout << "-1";
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}


void input() {
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		int r, c, d;
		cin >> r >> c >> d;
		Horse[i] = { r,c,d };
		StackedMap[r][c].push_back(i);

	}

}


// �� �ݺ���
// ���
// ������
// -> 
// �Ķ���
