#include<iostream>
#include<algorithm>

using namespace std;

//���� �м�
//NxN ���� (1,1)
//�� ���� : 5���� ���ű� �� �ϳ�
//�� ���ű� : �ּ� 1�� ���� ����, ����Ǿ��־����(����)
//�߰��� ���ϴ� ������ ���� : 0�� �̻�

//���ű� ������
//1. ������ : x,y (d1,d2)
//2. ��輱 (5�����ű�)
	//1) 

int N;
int A[21][21] = { 0, };
int minValue = 2112345678;



//�ִ� ���ϴ� �Լ�

//������ (r : 1) (c: 2 ~ N-1)

//���� ������ (r: 2 ~ N-1) (c: 1)
//������ ������ (r : N - 1 ~ 2) c: N
//�Ʒ� ������ (r: N) (c: N-1~ 2)

//(N-r+1)


void Division(int x, int y) {
	// d1, d2 �� 1
	// 1 �� x < x + d1 + d2 �� N
	// 1 �� y - d1 < y < y + d2 �� N
	
	int debugging = -1;

	for (int d1 = 1; d1 <= y-1; d1++) {
		for (int d2 = 1; d2 <= N - y; d2++) {

			if (x + d1 + d2 > N) continue;

			int Map[21][21] = { 0, };
			Map[x][y] = 5;

			int nowRow = x;
			int left_offset = -1;
			int right_offset = 1;
			int leftCol = y;
			int rightCol = y;

			for (int i = 1; i <= d1 + d2; i++) {
				leftCol += left_offset;
				rightCol += right_offset;
				if (leftCol == y - d1) left_offset = 1;
				if (rightCol == y + d2) right_offset = -1;

				for (int j = leftCol; j <= rightCol; j++) {
					Map[nowRow + i][j] = 5;
				}
				
			}


			for (int r = 1; r <= N; r++) {
				for (int c = 1; c <= N; c++) {

					if (Map[r][c] == 5) continue;
					else if (1 <= r && r < x + d1 && 1 <= c && c <= y) Map[r][c] = 1;
					else if (1 <= r && r <= x + d2 && y < c && c <= N) Map[r][c] = 2;
					else if (x + d1 <= r && r <= N && 1 <= c && c < y - d1 + d2) Map[r][c] = 3;
					else if (x + d2 < r && r <= N && y - d1 + d2 <= c && c <= N) Map[r][c] = 4;
				}
			}

			int sum[6] = { 0, };
			
			for (int r = 1; r <= N; r++) {
				for (int c = 1; c <= N; c++) {

					sum[Map[r][c]] += A[r][c];
				}
			}
			sort(sum + 1, sum + 6);
			int min__ = sum[1];
			int max__ = sum[5];
			if (max__ - min__ == 158) {
				int debugging = -1;
			}
			minValue = min(minValue, max__ - min__);

		}
	}
}

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
}

void solution() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Division(i, j);
		}
	}
	cout << minValue;
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}
