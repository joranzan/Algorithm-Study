#include<iostream>
#include<vector>

using namespace std;


//���� �м�
//NxN ����  ������ ��� ����(�߾� ���� K��ŭ �����)
//����: K^2 + (k-1)^2   
//���� ��� ��쿡�� ������ �״��

//���� ������ �� �ִ� ���: M

//��ǥ: "���غ���������" "���� ���� ��" �����ϴ� ���񽺿��� -> �̶� �����޴� ���� ��

struct pos {
	int row, col;
};

int N, M;
int Answer = 0;
vector<pos> House;  //�� ��ġ ����

void init() {
	N = M = 0;
	Answer = 0;
	House.clear();
}
void input() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int temp;
			cin >> temp;
			if (temp == 1) {
				House.push_back({ i,j });
			}
		}
	}
}

void check(int row, int col) {

	int ret = 0;

	for (int k = 1; k <= N+1; k++) {

		int cost = k * k + (k - 1) * (k - 1);
		int cnt = 0; //���� �� �� ����

		for (int i = 0; i < House.size(); i++) {
			int house_row = House[i].row;
			int house_col = House[i].col;

			int dist = abs(house_row - row) + abs(house_col - col);

			//���� �Ÿ� �ȴ�� ���
			if (dist > k-1 ) continue;
			//�̹� ���غ��� ��� ���̻� ��� ����
			cnt++;
		}
		//������ �� ���� * M - cost >=0   (���� �Ⱥ�)
		int margin = cnt * M - cost;
		if (margin < 0) continue;
		//Answer�� ��
		Answer = max(Answer, cnt);
	}
}

void solution() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			check(i, j);
		}
	}
}


int main() {


	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//freopen_s(new FILE*, "input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int test = 1; test <= T; test++) {
		init();
		input();
		solution();
		cout << "#" << test << " " << Answer << "\n";
	}


}

//����

//������ ���� ã�� -> �� ���� �� ���� �ľ�
//(M*���� ��) - (����) >= 0 �̿��� ���� ���� ����


