//https://www.codetree.ai/training-field/frequent-problems/problems/maze-runner/description?page=1&pageSize=20

#include<iostream>
#include<vector>

using namespace std;

struct pos {
	int row;
	int col;
};

//���� �м�
//������ : M��   N x N ���� (1,1)

//�̷� ����
//1. ��ĭ : ������ �̵� ����
//2. �� : ������ �̵� �Ұ� (1~9)
//   - ȸ�� �� ������ 1 ���� (0�Ǹ� ��ĭ���� ����)
//3. �ⱸ : ������ ���� �� Ż��!


// 1�ʿ� ������ ��ĭ �� ������
// �����̴� ����
// 1) �ִ� �Ÿ� : abs(x1-x2) + abs(y1-y2)
// 2) ������ ���ÿ� ������ -> �� �����̰� ó���Ұ� ó���ؾ���
// 3) �����¿� (��ĭ��)  �켱����: ����
// 4) �ⱸ���� �ִܰŸ� �� ��������Ը� ������ ����
// 5) ������ �� ������ Stay
// 6) ��ĭ�� ������ �־ �� (������ ���� ��ġ �迭 �����)


//�̷� ȸ��
//1�� �̻��� �����ڿ� �ⱸ ������ ���� ���� ���簢��
//�켱 ���� : �»�� Row��ǥ ���� �� -> �»�� Col ��ǥ ������
//�ð���� 90 ȸ�� (���, �ⱸ, ������ �� ���� ���ư�)
//������ 1 ����

//��� Ż�� �� ���� -> �������� �̵��Ÿ� �� + �ⱸ ��ǥ
int N, M;
pos Escape;  //�ⱸ ��ǥ


void rotation(int start_r, int start_c, int squareSize) {
	//�ð���� 90 ȸ�� (���, �ⱸ, ������ �� ���� ���ư�)
	//������ 1 ����
}

void findSquare() {

	int squareSize = 2;
	while (squareSize <= N) {
		int e_r = Escape.row;
		int e_c = Escape.col;

		vector<pos> squareCandi;

		int min_r = e_r - (squareSize - 1);    //Ž�� ���� ���� ��� ��ǥ r
		int min_c = e_c - (squareSize - 1);    //Ž�� ���� ���� ��� ��ǥ c
		if (min_r <= 0) min_r = 1;
		if (min_c <= 0) min_c = 1;

		for (int left_r = min_r; left_r <= e_r; left_r++) {
			if (left_r <= 0 || left_r > N) continue;
			for (int left_c = min_c; left_c <= e_c; left_c++) {
				if (left_c <= 0 || left_c > N) continue;
				squareCandi.push_back({ left_r, left_c });
			}
		}
		bool found = false;
		pos Result;
		for (int i = 0; i < squareCandi.size(); i++) {
			int start_r = squareCandi[i].row;
			int start_c = squareCandi[i].col;

			int personCnt = 0;
			//1�� �̻��� �����ڿ� �ⱸ ������ ���� ���� ���簢��
			//�켱 ���� : �»�� Row��ǥ ���� �� -> �»�� Col ��ǥ ������
			for (int r = 0; r < squareSize; r++) {
				for (int c = 0; c < squareSize; c++) {
					int now_r = start_r + r;
					int now_c = start_c + c;

					//������ ��ǥ Ž���ϴ� �ڵ�
					//������ �����ϸ� personCnt++
					if (personCnt >= 1) {
						found = true;
						Result = { start_r, start_c };
						break;
					}
					
					//break
				}
				if (found) break;
			}
			if (found) break;
		}
		if (found) {
			rotation(Result.row, Result.col, squareSize);
			break;
		}
	}
}



int main() {






	return 0;
}