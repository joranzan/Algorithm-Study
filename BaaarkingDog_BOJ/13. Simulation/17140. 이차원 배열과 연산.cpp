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

	int max_index = 0;

	for (int r = 0; r < nowRowSize; r++) {
		int DAT[101] = { 0, };
		vector<rule> temp;

		for (int c = 0; c < 100; c++) {
			if (Board[r][c] == 0) continue;
			DAT[Board[r][c]]++;
			Board[r][c] = 0;
		}

		for (int j = 1; j <= 100; j++) {
			if (DAT[j] == 0) continue;
			temp.push_back({ j,DAT[j] });
		}

		sort(temp.begin(), temp.end());

		int index = 0;
		for (int j = 0; j < temp.size(); j++) {
			Board[r][index] = temp[j].value;
			index++;
			if (index >= 100) break;
			Board[r][index] = temp[j].cnt;
			index++;
			if (index >= 100) break;
		}
		max_index = max(max_index, index);
	}
	nowColSize = max_index;
}

void CSort() {

	int max_index = 0;

	for (int c = 0; c < nowColSize; c++) {
		int DAT[101] = { 0, };
		vector<rule> temp;

		for (int r = 0; r < 100; r++) {
			if (Board[r][c] == 0) continue;
			DAT[Board[r][c]]++;
			Board[r][c] = 0;
		}

		for (int j = 1; j <= 100; j++) {
			if (DAT[j] == 0) continue;
			temp.push_back({ j,DAT[j] });
		}

		sort(temp.begin(), temp.end());

		int index = 0;
		for (int j = 0; j < temp.size(); j++) {
			Board[index][c] = temp[j].value;
			index++;
			if (index >= 100) break;
			Board[index][c] = temp[j].cnt;
			index++;
			if (index >= 100) break;
		}
		max_index = max(max_index, index);
	}
	nowRowSize = max_index;
}


void input() {
	cin >> R >> C >> K;
	R -= 1;
	C -= 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> Board[i][j];
		}
	}
}
int solution() {


	if (Board[R][C] == K) {
		return 0;
	}

	for (int time = 1; time <= 100; time++) {

		//���� �����ϸ� time ��� �� Ż��


		if (nowRowSize >= nowColSize) {
			RSort();
		}
		else if (nowRowSize < nowColSize) {
			CSort();
		}

		//���� �����ϸ� time ��� �� Ż��
		if (Board[R][C] == K) {
			return time;
		}

	}

	//���� ���� �������� -1
	return -1;
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	cout << solution();


	return 0;
}