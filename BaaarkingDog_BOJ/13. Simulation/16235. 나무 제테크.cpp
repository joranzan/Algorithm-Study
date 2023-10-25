#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<deque>
using namespace std;

//���� �м�
//NxN �� (1,1)���� ����

//��� ���� �κ�
//1x1ĭ�� ����ִ� ��� ����
//��� ĭ�� ���ؼ� ����
//�ʱ� : 5��ŭ �������

//���� ����ũ(������ Ű���� �Ⱦ��糢�� ����ũ)
//M���� ���� ����
//��ĭ�� ������ ���� ���� �� ����

//����ũ ����



//2. ����
//���� ���� ������� �ٲ�
//���� ������ ���� / 2 ��ŭ ��� �߰�

//3. ����
//����
//���� : ���� ���� 5�� ���
//������ 8ĭ�� ���� ���� (�� ����� �ʴ� ����)

//4. �ܿ�
//�κ��� ��� �߰��� A[r][c] : �Է�


//��ǥ: K�� �� ����ִ� ������ ����

struct tree {
	int row;
	int col;
	int age;
	bool alive;

	bool operator<(tree next) const {
		if (age < next.age) return false;
		if (age > next.age) return true;

		return false;
	}
};

int N, M, K;
int A[11][11] = { 0, };
int Map[11][11] = { 0, };
deque<int> Tree[11][11];
vector<tree> dead;   //���� ������ ����
int Ans = 0;

void spring() {
	//1. ��
	//���� : �ڽ��� ���̸�ŭ ��� ���� �� ����++
	//(������ ������ �� ���̰� ��������� ��� ����)
	//���� ��� < ���� ���� -> ����
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int last = Tree[i][j].size();
			for (int t = 0; t < Tree[i][j].size(); t++) {
				if (Map[i][j] < Tree[i][j][t]) {
					last = t;
					break;
				}
				Map[i][j] -= Tree[i][j][t];
				Tree[i][j][t]++;
				
			}
			int deadNum = 0;
			int T = Tree[i][j].size();
			for (int t = 0; t < T - last; t++) {
				if (Tree[i][j].size() == 0) continue;
				deadNum += (Tree[i][j][Tree[i][j].size() - 1] / 2);
				Tree[i][j].pop_back();
			}

			Map[i][j] += deadNum;
		}
	}
}

void summer() {
	//2. ����
	//���� ���� ������� �ٲ�
	//���� ������ ���� / 2 ��ŭ ��� �߰�
	for (int i = 0; i < dead.size(); i++) {
		tree now = dead[i];
		Map[now.row][now.col] += (now.age / 2);
	}
}
void autumn() {
	//3. ����
	//����
	//���� : ���� ���� 5�� ���
	//������ 8ĭ�� ���� ���� (�� ����� �ʴ� ����)

	const int dr[8] = { -1,1,0,0,-1,-1,1,1 };
	const int dc[8] = { 0,0,-1,1,-1,1,-1,1 };

	vector<int> temp[11][11];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			
			for (int t = 0; t < Tree[i][j].size(); t++) {
				if (Tree[i][j][t] % 5 != 0) continue;
				for (int dir = 0; dir < 8; dir++) {
					int next_r = i + dr[dir];
					int next_c = j + dc[dir];
					if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) continue;
					tree next = { next_r, next_c , 1, true };
					temp[next_r][next_c].push_back(1);
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 0; k < temp[i][j].size(); k++) {
				Tree[i][j].push_front(temp[i][j][k]);
			}
		}
	}
}

void winter() {
	//4. �ܿ�
	//�κ��� ��� �߰��� A[r][c] : �Է�
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Map[i][j] += A[i][j];
		}
	}
}


void simulation() {

	spring();
	//summer();
	autumn();
	winter();
	
}

void init() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Map[i][j] = 5;
			sort(Tree[i][j].begin(), Tree[i][j].end());
		}
	}
}

void input() {
	//�Է�
	//N,M,K
	cin >> N >> M >> K;
	
	//A�迭 (�߰��� ���)
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	//x y,z : x(r) y(c) ����
	for (int i = 0; i < M; i++) {
		int r, c, old;
		cin >> r >> c >> old;
		Tree[r][c].push_back(old);
	}

	init();
}

void solution() {

	for (int i = 1; i <= K; i++) {
		dead.clear();
		simulation();
	}

	//����ִ� ���� ���� ����ϱ�
	Ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Ans += Tree[i][j].size();
		}
	}

	cout << Ans << "\n";

}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}