#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//�迭 3x3 (�ε��� 1���� ����)
//1�� ���������� ���� ����

//R���� (���� ���� >= ���� ����) : ��� �࿡ ���ؼ� ���� ���� 
//C���� (���� ���� < ���� ����) : ��� ���� ���ؼ� ����

//�����ϱ� ���ؼ� ������ ���� ��� ���Դ��� �˾ƾ���
//���� ���� (0�� ����)
	// ����Ƚ�� Ŀ���� ��
	// ���� Ŀ���� ��
//�ٽ� ���� �� : �� / ����Ƚ�� ��� ����

//100�� �Ѿ�� ������ ����

//��ǥ : A[r][c] =k �϶����� ����

struct rule {
	int value;
	int cnt;

	bool operator<(rule next) const {
		if (cnt < next.cnt) return true;
		else if (cnt > next.cnt) return false;
		else {
			if (value < next.value) return true;
			else if (value > next.value) return false;
			else return false;
		}
	}
};

int Board[100][100] = { 0,0 }; //99������ ����

int R, C, K;
int nowRowSize = 3;  //�ϳ��� ���� ũ��
int nowColSize = 3;  //�ϳ��� ���� ũ��

void RSort() {


	for (int i = 0; i < nowRowSize; i++) {

		int DAT[101] = { 0, };
		vector<rule> temp;

		for (int j = 0; j < 100; j++) {

			int nowNum = Board[i][j];
			if (nowNum == 0) continue;
			Board[i][j] = 0;
			DAT[nowNum]++;
		}

		for (int j = 1; j <= 100; j++) {
			if (DAT[j] <= 0) continue;
			temp.push_back({ j,DAT[j] });
		}

		sort(temp.begin(), temp.end());
		Board[i].clear();
		for (int j = 0; j < 100; j++) {
			if (j >= temp.size()) break;
			Board[i].push_back(temp[j].value);
			if (Board[i].size() >= 100) break;
			Board[i].push_back(temp[j].cnt);
			if (Board[i].size() >= 100) break;
		}
		int tempsize = Board[i].size();
		nowRowSize = max(tempsize, nowRowSize);
	}
}

void CSort() {



}


void input() {
	cin >> R >> C >> K;
	R -= 1;
	C -= 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int temp;
			cin >> temp;
			Board[i].push_back(temp);
		}
	}
}
void solution() {

	for (int time = 1; time <= 100; time++) {

		int rowSize = Board[0].size(); //�ϳ��� ���� ũ��
		int colSize = Board.size(); //�ϳ��� ���� ũ��


		if (rowSize >= colSize) {
			RSort();
		}
		else if (rowSize < colSize) {
			CSort();
		}

		//���� �����ϸ� time ��� �� Ż��
	}

	//���� ���� �������� -1
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();


	return 0;
}