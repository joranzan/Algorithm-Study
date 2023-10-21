#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

struct Info {
	int id;
	map<int, int> hit;  //��ĥ��
};

Info DAT[10];
int N;
int order[10];
int nowPlayer = 0;

int playStart() {
	int inning = 1;
	int score = 0;
	nowPlayer = 1;
	
	while (inning <= N) {
		int Base[4] = { 0, };
		int out = 0;
		while (out < 3) {

			int playerNum = order[nowPlayer];
			int batting = DAT[playerNum].hit[inning];
			
			if (batting > 0 && batting<=3) {
				//��Ÿ(1) : Ÿ�ڿ� ��� ���� 1�� ����
				//2��Ÿ(2) : 2�� ����
				//3��Ÿ(3) : 3�� ����
				for (int i = 3; i >= 1; i--) {
					if (Base[i] == 0) continue;
					int nextBase = i + batting;
					if (nextBase >= 4) {
						Base[i] = 0;
						score++;
					}
					else {
						Base[nextBase] = Base[i];
						Base[i] = 0;
					}
				}
				Base[batting] = playerNum;
			}
			else if (batting == 4) {
				//Ȩ��(4) : ��� ���� Ȩ
				int cnt = 0;
				for (int i = 1; i <= 3; i++) {
					if (Base[i] != 0) cnt++;
					Base[i] = 0;
				}
				score += (cnt + 1);
			}
			else if (batting == 0) {
				//�ƿ�(0) : ��� ���� �״�� , out �߰�
				out++;
			}

			nowPlayer++;
			if (nowPlayer > 9) nowPlayer = 1;
		}
		inning++;
	}
	if (score == 48) {
		int debugging = -1;
	}
	if (score == 43) {
		int debugging = -1;
	}
	return score;
}

void input() {
	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= 9; j++) {
			int s;
			cin >> s;
			DAT[j].id = j;
			DAT[j].hit[i] = s;
		}
	}

	for (int i = 1; i <= 9; i++) {
		order[i] = i;
	}

}
void solution() {
	int Answer = 0;

	do {

		Answer = max(Answer, playStart());

	} while (next_permutation(order + 1, order + 10));

	cout << Answer << "\n";
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

//36�� ����

//�����м�
//N�̴�
//1�̴� 3�ƿ�  -> �������� & �̴� ��

//��� ���� ��
//Ÿ�� ���ϱ�

//��� ����
//Ÿ�� ���� ���� 
//3out �ȳ��� �ٽ� ó������ ���� �����̼�
//���� ��� Ÿ�� �̾ ����

//1�� 2�� 3��  ���ļ� Ȩ ���� -> 1��

//��Ÿ(1) : Ÿ�ڿ� ��� ���� 1�� ����
//2��Ÿ(2) :                 2�� ����
//3��Ÿ(3) :                 3�� ����
//Ȩ��(4) : ��� ���� Ȩ
//�ƿ�(5) : ��� ���� �״�� , out �߰�

//���� ���� 1�� ~ 9��
//���� ���� ������ �ϴ� Ÿ�� ���ϱ�