#include<iostream>
#include<vector>

using namespace std;

//��ȭ��
//K���� �巡�� Ŀ�� : K-1 �巡�� Ŀ�� ���� ���� 90�� �ð���� ȸ��


//�巡�� Ŀ�� : 3���� �Ӽ�
//������, ���� ����, ����
struct Info {
	int row;
	int col;
	int dir;
	int level;
};
//0,0 ~ 100,100
int Map[101][101]={0,};
int N;  //�巡�� Ŀ�� ����
Info Curve[20];
int Answer = 0;
//0 1 2 3  �� �� �� ��
const int dr[4] = { 0,-1,0,1 };
const int dc[4] = { 1,0,-1,0 };

//�ð�ݴ� �� �� �� ��  //1 2 3 0
int clockwise(int dir) {
	if (dir == 0) {
		return 1;
	}
	else if (dir == 1) {
		return 2;
	}
	else if (dir == 2) {
		return 3;
	}
	else if (dir == 3) {
		return 0;
	}
}

void Move(Info now) {
	//�������� ���
	//�迭 �ڿ������� ���� �ð���� ���
	//���� �迭�� �߰�
	vector<int> acc;
	int start_r = now.row;
	int start_c = now.col;
	acc.push_back(now.dir);
	for (int i = 0; i < now.level; i++) {
		vector<int> temp;
		for (int j = acc.size()-1; j >= 0; j--) {
			int nowDir = acc[j];
			temp.push_back(clockwise(nowDir));
		}
		for (int j = 0; j < temp.size(); j++) {
			acc.push_back(temp[j]);
		}
	}

	Map[start_r][start_c] = 1;
	for (int i = 0; i < acc.size(); i++) {
		start_r += dr[acc[i]];
		start_c += dc[acc[i]];
		Map[start_r][start_c] = 1;
	}
}

//��ǥ: 4�������� ��� �巡�� Ŀ�꿡 ������ 1x1 ���簢�� ����
void checkSquare() {

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int p1 = Map[i][j];
			int p2 = Map[i + 1][j];
			int p3 = Map[i][j + 1];
			int p4 = Map[i + 1][j + 1];
			if (p1 == 1 && p2 == 1 && p3 == 1 && p4 == 1) {
				Answer++;
			}
				
		}
	}

}

void input() {
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		Curve[i] = { y, x, d, g };
	}

}
void solution() {
	for (int i = 0; i < N; i++) {
		Move(Curve[i]);
	}

	checkSquare();
	cout << Answer << "\n";

}
//101 * 102 * 203 /3

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	input();
	solution();

	return 0;
}

//(3,3) �� 1����
//(2,4) �� 3����
//(2,4) �� 1����

//������ ���� ���� ȸ�� ��Ŵ

//�� �� �� �� �� �� �� �� | �� �� �� �� �� �� �� ��