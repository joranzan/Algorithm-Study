#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
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
priority_queue<tree> Tree[11][11];
vector<tree> dead;   //���� ������ ����
int Ans = 0;

void spring() {
	//1. ��
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Tree[i][j].empty()) continue;
			int deadAge = 0;
			priority_queue<tree> temp;
			while (!Tree[i][j].empty()) {
				//(������ ������ �� ���̰� ��������� ��� ����)
				tree Now = Tree[i][j].top();
				Tree[i][j].pop();

				//���� ��� < ���� ���� -> ����
				if (Now.age > Map[i][j]) {
					Now.alive = false;
					dead.push_back(Now);
					deadAge += (Now.age / 2);
					continue;
				}
				//���� : �ڽ��� ���̸�ŭ ��� ���� �� ����++
				Map[i][j] -= Now.age;
				Now.age++;
				temp.push(Now);

			}

			while (!Tree[i][j].empty()) {
				tree Now = Tree[i][j].top();
				Tree[i][j].pop();
				Now.alive = false;
				deadAge += (Now.age / 2);
				dead.push_back(Now);
			}

			Tree[i][j] = temp;
			//Map[i][j] += deadAge;
			Map[i][j] += A[i][j];
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

	priority_queue<tree> temp[11][11];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Tree[i][j].empty()) continue;
			

			while (!Tree[i][j].empty()) {
				//���� : ���� ���� 5�� ���
				//������ 8ĭ�� ���� ���� (�� ����� �ʴ� ����)

				tree now = Tree[i][j].top();
				Tree[i][j].pop();

				temp[now.row][now.col].push(now);
				if (now.age % 5 != 0) continue;
				for (int i = 0; i < 8; i++) {
					int next_r = now.row + dr[i];
					int next_c = now.col + dc[i];
					if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) continue;
					tree next = { next_r, next_c , 1, true };
					temp[next_r][next_c].push(next);
				}

			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Tree[i][j] = temp[i][j];
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
	summer();
	autumn();
	//winter();
	
}

void init() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Map[i][j] = 5;
		}
	}
}

void input() {
	//�Է�
	//N,M,K
	cin >> N >> M >> K;
	init();
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
		Tree[r][c].push({ r,c,old,true });
	}
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