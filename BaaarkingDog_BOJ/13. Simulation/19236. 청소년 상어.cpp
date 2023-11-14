#include<iostream>
#include<vector>

using namespace std;

//4x4

//����� (��ȣ(1~16) , ����)

//����� �̵� (��� ��ġ ����)
//1) �̵� ���� ĭ : ��ĭ, �ٸ� ����� ĭ
//2) �̵� �Ұ� ĭ : ���, ���� ��
//3) �̵���� : 
	//1. �̵��� �� �ִ� ĭ���� 45�� �ݽð�
	//2. ������ �̵� X
	//3. �ٸ� ����� ������ Swap (���� ����)


//��� �̵� (����� �̵� ���� ��)
// �ʱ� : (0,0) ����� �԰� (0,0)�� ��ġ 
// 
//1) ����� �ִ� ĭ���� ������ ���
	//1. ����� ����
	//2. ���� ����

//2) �̵� �� ����� ������ ����

//3) ����� ���� ĭ���� �̵� X

//4) �̵� ������ ĭ ������ ��ȯ

//���� 8��
void input();
void movefish();


struct pos {
	int row;
	int col;
	int dir;
};

const int dr[9] = {0, -1, -1, 0, 1, 1, 1, 0,-1 };
const int dc[9] = {0,  0, -1,-1,-1,0,1,1, 1 };
int Map[4][4] = { 0, };

int Dead[17] = { 0, };
pos Fish[17];
pos Shark;
int Answer = 0;


void DFS(int sum, int depth) {
	//���� ����� �� �׾��ų�
	//��� �̵��� �� ������ ��
	if (depth >= 15) {
		Answer = max(Answer, sum);
		return;
	}
	int sharkDir = Shark.dir;
	int sharkRow = Shark.row;
	int sharkCol = Shark.col;

	movefish();
	int Temp[4][4] = { 0, };

	pos Fish_Temp[17];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Temp[i][j] = Map[i][j];
		}
	}
	for (int i = 1; i <= 16; i++) {
		Fish_Temp[i] = Fish[i];
	}

	vector<pair<int, int>> Candi;  //���� �ĺ�

	while (1) {
		sharkRow += dr[sharkDir];
		sharkCol += dc[sharkDir];
		
		//3) ����� ���� ĭ���� �̵� X
		if (sharkRow < 0 || sharkCol < 0 || sharkRow >= 4 || sharkCol >= 4) break;
		if (Map[sharkRow][sharkCol] == 0) continue;
		Candi.push_back({ sharkRow, sharkCol });
	}
	//�̵� ������ ĭ ������ ��ȯ
	if (Candi.size() == 0) {
		Answer = max(Answer, sum);
		return;
	}
	sharkRow = Shark.row;
	sharkCol = Shark.col;

	if (Fish[9].row == 0 && Fish[9].col == 1) {
		int debugging = -1;
	}

	for (int i = 0; i < Candi.size(); i++) {

		int nextRow = Candi[i].first;
		int nextCol = Candi[i].second;
		int nextFish = Map[nextRow][nextCol];
		//��� �̵�
		Map[sharkRow][sharkCol] = 0;
		Map[nextRow][nextCol] = -1;
		//����� ����
		Dead[nextFish] = 1;
		Shark.row = nextRow; 
		Shark.col = nextCol; 
		Shark.dir = Fish[nextFish].dir;
		
		//��� ȣ�� �κ�
		DFS(sum + nextFish, depth+1);


		Dead[nextFish] = 0;
		
		Shark.row = sharkRow; 
		Shark.col = sharkCol;
		Shark.dir = sharkDir;

		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				Map[j][k] = Temp[j][k];
			}
		}

		for (int j = 1; j <= 16; j++) {
			Fish[j] = Fish_Temp[j];
		}
		int debugging = -1;
	}

}


void solution() {
	int init_Fish = Map[0][0];
	Shark = { Fish[init_Fish].row, Fish[init_Fish].col, Fish[init_Fish].dir };
	Map[0][0] = -1;  //��� �ִ� ĭ : -1
	Dead[init_Fish] = 1;

	DFS(init_Fish, 0);

	cout << Answer;

}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}



void input() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int a, b;
			cin >> a >> b;
			Fish[a] = { i,j,b };
			Map[i][j] = a;
		}
	}

}

void movefish() {


	for (int i = 1; i <= 16; i++) {
		if (Dead[i] == 1) continue;  //���� ����� ����

		int nowRow = Fish[i].row;
		int nowCol = Fish[i].col;
		int nowDir = Fish[i].dir;

		for (int d = nowDir; d < 8 + nowDir; d++) {
			int nextDir = d;
			if (nextDir > 8) nextDir -= 8;
			int nextRow = nowRow + dr[nextDir];
			int nextCol = nowCol + dc[nextDir];
			//�̵� �Ұ� ĭ : ���, ���� ��
			//2. ������ �̵� X
			if (nextRow < 0 || nextCol < 0 || nextRow >= 4 || nextCol >= 4) continue;
			if (Map[nextRow][nextCol] == -1) continue;

			else if (Map[nextRow][nextCol] == 0) {  //�׳� ��ĭ�� ��� �̵�
					Map[nextRow][nextCol] = i;
					Map[nowRow][nowCol] = 0;
					Fish[i].row = nextRow;
					Fish[i].col = nextCol;
					Fish[i].dir = nextDir;
					break;
			}
			else {    //�ٸ� ����Ⱑ �����ϴ� ���
				//�ٸ� ����� ������ Swap(���� ����)
				int nextFish = Map[nextRow][nextCol];
				swap(Map[nextRow][nextCol], Map[nowRow][nowCol]);
				Fish[i].row = nextRow;
				Fish[i].col = nextCol;
				Fish[i].dir = nextDir;
				Fish[nextFish].row = nowRow;
				Fish[nextFish].col = nowCol;
				break;
			}
		}
	}

}