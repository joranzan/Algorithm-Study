#include<iostream>
#include<vector>

using namespace std;

//���� �м�
//������ : i -> i��° ����

//i��° ���� j��° �� : i,j

//����
//(i, 1)�� (i, 2), (i, M)�� ����
//(i, M)�� (i, M-1), (i, 1)�� ����
//(i, j)�� (i, j-1), (i, j+1)�� ���� (2 �� j �� M-1)
//(1, j)�� (2, j)�� ����
//(N, j)�� (N-1, j)�� ����
//(i, j)�� (i-1, j), (i+1, j)�� ���� (2 �� i �� N-1)

//ȸ�� 
//1) ������
//2) ���� ��ġ�� ����
//3) ȸ�� �� ���� ��ġ�� ȸ�� �� �� ����



//ȸ�� ��� (x,d,k)
//1. ��ȣ�� x�� ����� ������ d(0:�ð�, 1:�ݽð�)�������� kĭ ȸ��(%4) 
//2. ���ǿ� ���� ���������� �����ϸ鼭 ���� ���� �� ��� ã��
	//1) �����ϴ� ���� �� �ִ� ��� : �����ϸ鼭 ������ ��� ����
    //2) ���� ��� : ���ǿ� ���� ���� ��� (ū : -  ��: +)

struct pos {
	int row;
	int col;
};

int N, M, T;
int Circle[51][51] = { 0, }; //NxM
vector<pos> v;

void Rotation(int num, int dir, int k) { //num ���� dir�������� k��ŭ
	if (dir == 1) {//�ݽð�
		k = M - k;
	}

	//�ð���� Rotation
	int temp[51] = { 0, };

	for (int i = 1; i <= M; i++) {  //4
		int next_index = i + k;
		if (next_index > M) {
			next_index -= M;
		}
		temp[next_index] = Circle[num][i];
	}
	int sum = 0;
	int cnt = 0;
	for (int i = 1; i <= M; i++) {
		Circle[num][i] = temp[i];
		if (Circle[num][i] == -1) continue;
		sum += Circle[num][i];
		cnt++;
	}

}

double findAverage() {

	double cnt = 0;
	double sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] == -1) continue;
			sum += Circle[i][j];
			cnt++;
		}
	}

	return sum / cnt;
}

void simulation() {

	

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] == -1) continue;

			int nowNum = Circle[i][j];
			int next_top = i + 1;
			int next_bottom = i - 1;
			int next_cw = j - 1;
			int next_c = j + 1;
			if (next_cw <= 0) next_cw = M;
			if (next_c > M) next_c = 1;


			if (next_top <= N&&Circle[next_top][j]!=-1) {
				if (nowNum == Circle[next_top][j]) {
					v.push_back({ next_top, j });
				}
			}
			if (next_bottom >= 1&& Circle[next_bottom][j]!=-1) {
				if (nowNum == Circle[next_bottom][j]) {
					v.push_back({ next_bottom,j });
				}
			}

			if (nowNum == Circle[i][next_cw]&& Circle[i][next_cw]!=-1) {
				v.push_back({ i, next_cw });
			}
			if (nowNum == Circle[i][next_c]&& Circle[i][next_c]!=-1) {
				v.push_back({ i, next_c });
			}

		}
	}
}

int input() {

	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {

		for (int j = 1; j <= M; j++) {
			cin >> Circle[i][j];
		}
	}

	for (int t = 0; t < T; t++) {
		v.clear();
		int x, d, k;
		cin >> x >> d >> k; //x�� ����� ������ d �������� kĭ ȸ��
		k = k % M;
		//ȸ����Ű��
		if (k != 0) {   //������ Ƚ��
			for (int i = 1; i <= N; i++) {

				if (i % x == 0) {
					Rotation(i, d, k);
				}
			}
		}

		int debugging = -1;
		double avg = findAverage();

		//2. ���ǿ� ���� ���������� �����ϸ鼭 ���� ���� �� ��� ã��

		simulation();

		if (v.size() == 0) {
			//�����ϴ� ��� ������
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if (Circle[i][j] == -1) continue;
					if (Circle[i][j] > avg) Circle[i][j]--;
					else if (Circle[i][j] < avg) Circle[i][j]++;
				}
			}
		}
		else {
			for (int i = 0; i < v.size(); i++) {
				if (Circle[v[i].row][v[i].col] == -1) continue;
				Circle[v[i].row][v[i].col] = -1;
			}
		}

		int debugging2 = -1;
	}

	

	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] == -1) continue;
			sum += Circle[i][j];
		}
	}
	return sum;

}




int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cout << input();


	return 0;
}