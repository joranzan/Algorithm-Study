#include<iostream>
#include<map>
#include<vector>

using namespace std;

//���� �м�

//���� �� �ִ� �� : 6��

//�� ��� 90�� �����
// h r c
//�� : ��(W)  (h==0)
//�Ʒ� : ����� (Y)  (h==2)
//�� : �� (R)    (c===2)
//�޸� : ��Ȳ (O) (c==0)
//�� : �ʷ� (G)  (r==0)
//�� : �Ķ� (B)  (r==2)


vector<pair<int,char>> Cube[3][3][3];
int T;
map<char, int> planeMap;

//������ �� �ð���� ����
const int Mapping[6][2][6] = {
	{
	{ 0,1,4,5,3,2 }, //U C
	{0,1,5,4,2,3}  //U CW
	},
	{
	{0,1,5,4,2,3}, //D C
	{0,1,4,5,3,2}  //D CW
	},
	{
	{5,4,2,3,0,1}, //F C
	{4,5,2,3,1,0}  //F CW
	},
	{
	{4,5,2,3,1,0}, //B C
	{5,4,2,3,0,1}  //B CW
	},
	{
	{2,3,1,0,4,5}, //L C
	{3,2,0,1,4,5}, //L CW
	},
	{
	{3,2,0,1,4,5}, //R C
	{2,3,1,0,4,5}, //R CW
	}
};


// h r c
//�� : ��(W)  (h==0)
//�Ʒ� : ����� (Y)  (h==2)
//�� : �� (R)    (c===2)
//�޸� : ��Ȳ (O) (c==0)
//�� : �ʷ� (G)  (r==0)
//�� : �Ķ� (B)  (r==2)

void rotationU(int dir) {   //0
	vector<pair<int, char>> temp[3][3];

		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				for (int i = 0; i < Cube[0][r][c].size(); i++) {
					int face = Mapping[0][dir][Cube[0][r][c][i].first];
					char color = Cube[0][r][c][i].second;
					temp[c][2 - r].push_back({ face,color });
				}
			}
		}
		//�ٽ� �Űܴ��
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {

			}
		}
}
void rotationD(int dir) {   //1
	vector<pair<int, char>> temp[3][3];

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			for (int i = 0; i < Cube[2][r][c].size(); i++) {
				int face = Mapping[1][dir][Cube[2][r][c][i].first];
				char color = Cube[2][r][c][i].second;
				temp[2-c][r].push_back({ face,color });
			}
		}
	}
}
void rotationF(int dir) {
	vector<pair<int, char>> temp[3][3];

	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			for (int i = 0; i < Cube[h][r][2].size(); i++) {
				int face = Mapping[2][dir][Cube[h][r][2][i].first];
				char color = Cube[h][r][2][i].second;
				temp[r][2 - h].push_back({ face,color });
			}
		}
	}
}
void rotationB(int dir) {
	vector<pair<int, char>> temp[3][3];

	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			for (int i = 0; i < Cube[h][r][0].size(); i++) {
				int face = Mapping[3][dir][Cube[h][r][0][i].first];
				char color = Cube[h][r][0][i].second;
				temp[2 - r][h].push_back({ face,color });
			}
		}
	}
}
void rotationL(int dir) {

	vector<pair<int, char>> temp[3][3];

	for (int h = 0; h < 2; h++) {
		for (int c = 0; c < 2; c++) {
			for (int i = 0; i < Cube[h][0][c].size(); i++) {
				int face = Mapping[4][dir][Cube[h][0][c][i].first];
				char color = Cube[h][0][c][i].second;
				temp[2 - c][h].push_back({ face,color });
			}
		}
	}
}
void rotationR(int dir) {
	vector<pair<int, char>> temp[3][3];

	for (int h = 0; h < 2; h++) {
		for (int c = 0; c < 2; c++) {
			for (int i = 0; i < Cube[h][2][c].size(); i++) {
				int face = Mapping[5][dir][Cube[h][2][c][i].first];
				char color = Cube[h][2][c][i].second;
				temp[c][2 - h].push_back({ face,color });
			}
		}
	}
}

void simulation(char plane, char dir) {

	int temp_dir;
	if (dir == '+') {   //�ð���� 90�� : 0
		temp_dir = 0;
	}
	else if (dir == '-') { //�ݽð���� 90�� : 1
		temp_dir = 1;
	}


	if (plane == 'U') { // ���� 
		rotationU(temp_dir);
	}
	else if (plane == 'D') {  //�Ʒ��� ������
		rotationD(temp_dir);
	}
	else if (plane == 'F') {  //�ո� ������
		rotationF(temp_dir);
	}
	else if (plane == 'B') {  //�޸� ������
		rotationB(temp_dir);
	}
	else if (plane == 'L') {  //���ʸ� ������
		rotationL(temp_dir);
	}
	else if (plane == 'R') {  //�����ʸ� ������
		rotationR(temp_dir);
	}

}

void init() {

	//�ʱ�ȭ
	for (int h = 0; h < 2; h++) {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				Cube[r][c][h].clear();
			}
		}
	}
	


	// ���� �Ʒ��� ä���
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			//���� ä���
			Cube[0][r][c].push_back({ 0,'W' });
			//�Ʒ��� ä���
			Cube[2][r][c].push_back({ 1,'Y' });
		}
	}
	//�� �� �� ä���
	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			//�ո� ä���
			Cube[h][r][2].push_back({ 2,'R' });
			//�޸� ä���
			Cube[h][r][0].push_back({ 3,'O' });
		}
	}

	//���ʸ� �����ʸ� ä���
	for (int h = 0; h < 3; h++) {
		for (int c = 0; c < 3; c++) {
			//���ʸ�
			Cube[h][0][c].push_back({ 4,'G' });
			//�����ʸ�
			Cube[h][2][c].push_back({ 5,'B' });
		}
	}

	planeMap['U'] = 0;
	planeMap['D'] = 1;
	planeMap['F'] = 2;
	planeMap['B'] = 3;
	planeMap['L'] = 4;
	planeMap['R'] = 5;
	
	int debugging = -1;
}

void input() {
	cin >> T;
	for (int test = 0; test < T; test++) {
		int N;
		cin >> N;

		for (int i = 0; i < N; i++) {
			char plane;
			char dir;
			cin >> plane >> dir;

			simulation(plane, dir);
		}

	}
	
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	input();
	

	return 0;
}