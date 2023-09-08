#include<iostream>
#include<cmath>

using namespace std;

//���� �м�

//���̸� ���򺰷� �ڸ���

//��ĥ �ȵǾ������� 4���

// �Ͼ��: 0  �Ķ���: 1

struct pos {
	int row;
	int col;
};

int N;
int Map[130][130] = { 0, };
int DAT[2] = { 0 };

void Recursion(pos start, pos end, int n) {

	if (n == 0) {
		DAT[Map[start.row][start.col]]++;
		return;
	}
	
	//������ �ִ��� Ȯ���ϴ� �κ�
	bool same = true;
	int start_num = Map[start.row][start.col];
	for (int i = start.row; i <= end.row; i++) {
		for (int j = start.col; j <= end.col; j++) {
			if (start_num != Map[i][j]) {
				same = false;
				break;
			}
		}
		if (!same) break;
	}

	//�� ������ ���� �߰�
	if (same) {
		DAT[start_num]++;
		return;
	}

	//4��� ���
	int currentLength = pow(2, n - 1);
	Recursion({ start.row,start.col }, { start.row + currentLength - 1, start.col + currentLength - 1 }, n - 1);
	Recursion({ start.row, start.col + currentLength }, { start.row + currentLength - 1, start.col + currentLength * 2 - 1 }, n - 1);
	Recursion({ start.row + currentLength, start.col }, { start.row + currentLength * 2 - 1, start.col + currentLength - 1 }, n - 1);
	Recursion({ start.row + currentLength, start.col + currentLength }, { start.row + currentLength * 2 - 1,start.col + currentLength * 2 - 1 }, n - 1);

}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			cin >> Map[i][j];
		}
	}

	int num = N;
	int power = 0;

	while (num != 1) {
		num = num / 2;
		power++;
	}

	Recursion({ 0,0 }, { N - 1,N - 1 }, power);

	for (int i = 0; i < 2; i++) {
		cout << DAT[i] << "\n";
	}

	return 0;
}

//���� n=0�̸� �Ķ� �Ǵ� ��� ���� �ø��� return

//Ž���ؼ� �� ������ flag �α�

//