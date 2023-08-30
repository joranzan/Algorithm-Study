#include<iostream>
#include<vector>

using namespace std;

/*
7 2 9
1 1 7 1
2 1 7 1
5 1 5 4
3 2 8 4
4 3 14 1
3 4 3 3
1 5 8 2
3 5 100 1
5 5 1 1
*/

struct MAP {
	int colonyNum;  //���� �ش� ���� ������ ���� ��ȣ
	int cnt;  //�ش� ���� ���� �̻��� �� ��
};

struct Colony {
	int row, col, cnt, dir;
};

int N, M, K;
vector<Colony> colony;
vector<int> alive; //���� ����ִ� ���� ���

void init() {
	N = M = K = 0;
	colony.clear();
	alive.clear();
}
void input() {
	cin >> N >> M >> K;
	colony.push_back({ 0,0,0,0 });  //���� �����̶� �ǹ�
	for (int i = 1; i <= K; i++) {
		int row, col, cnt, dir;
		cin >> row >> col >> cnt >> dir;
		colony.push_back({ row,col,cnt,dir });  //���� �����ϴ� ���� 1������
		alive.push_back(i); //�ʱ⿣ ����ִٰ� ���
	}
}
void simulation() {
	for (int time = 0; time < M; time++) { 
		MAP Map[110][100] = { 0, };   //colonynum : �ʱⰪ 0 (������ ����)

		const int dr[] = { 0,-1,1,0,0 };
		const int dc[] = { 0,0,0,-1,1 };
		for (int i = 0; i < alive.size(); i++) {
			int nowColonyNum = alive[i];
			Colony nowColony = colony[nowColonyNum];
			nowColony.row += dr[nowColony.dir];
			nowColony.col += dc[nowColony.dir];

			if (nowColony.row <= 0 || nowColony.col <= 0 || nowColony.row >= N - 1 || nowColony.col >= N - 1)
			{
				nowColony.cnt /= 2;
				nowColony.dir += 1;

				if (nowColony.dir % 2 == 1) nowColony.dir -= 2;
			}
			//�����ڸ����� ���� ó��

			//��ġ�� (Map�� ���)
			int maxColonyNum = Map[nowColony.row][nowColony.col].colonyNum;  //���� ��ǥ�� ���� ���Ҵ� ����
			Colony maxColony = colony[maxColonyNum];
			if (maxColony.cnt < nowColony.cnt) {  //���� ��� ������ ����
				Map[nowColony.row][nowColony.col] = { nowColonyNum,
					Map[nowColony.row][nowColony.col].cnt +nowColony.cnt
				};
				colony[maxColonyNum].cnt = 0; //���� ����
			}
			else {   //���� �װ� ������ ���
				Map[nowColony.row][nowColony.col] = { maxColonyNum,
					Map[nowColony.row][nowColony.col].cnt + nowColony.cnt
				};
				nowColony.cnt = 0;  //���� ����
			}
			colony[nowColonyNum] = nowColony;  //�ӽ÷� �ٷ�� nowColony ������ ���� ����
		}
		//���� �� �غ�
		vector<int> next_alive;  //������ ����ִ� ���
		for (int i = 0; i < alive.size(); i++) {
			int nowColonyNum = alive[i];
			Colony nowColony = colony[nowColonyNum];
			if (nowColony.cnt == 0) continue;
			
			colony[nowColonyNum].cnt = Map[nowColony.row][nowColony.col].cnt;
			next_alive.push_back(nowColonyNum);
		}

		alive = next_alive;
	}
}
int solution() {

	simulation();
	int ret = 0;
	for (int i = 0; i < alive.size(); i++) {
		ret += colony[alive[i]].cnt;
	}
	return ret;
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		init();
		input();
		int answer = solution();
		cout << "#" << test << " " << answer << "\n";
	}

	return 0;
}