#include<iostream>
#include<queue>

using namespace std;

//�� �ٱ⼼��: ����� ��ġ X
// X�ð� �� Ȱ��ȭ -> X�ð� �ڿ� ����(������ �״�� �ֱ���)

//Ȱ��ȭ�� �ٱ⼼��
//�����¿� ���� (1�ð�)
//��ĥ ��� ����� ��ġ�� ���� �ٱ⼼���� ����(���� �ΰ��)


//K�ð� �� ����ִ� �ٱ� ���� (��Ȱ�� + Ȱ��)    1�̻� 300����

int Map[651][651] = { 0, };
int Visited[651][651] = { 0, };


struct Cell {

	int origin_life;   //���� ���� X
	int current_life;  //���� ����
	int state;  // 2: Ȱ��ȭ  1: ��Ȱ��ȭ  0: ����
	
	int row;
	int col;

	bool operator<(Cell next) const {
		if (origin_life < next.origin_life) return true;
		if (origin_life > next.origin_life) return false;

		if (row < next.row) return false;
		if (row > next.row) return true;

		if (col < next.col) return false;
		if (col > next.col) return true;

		return false;		
	}

};


priority_queue<Cell> pq;

void FloodFill() {

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	priority_queue<Cell> pq_temp;

	//������ ���� pq�� �ִ� ������ �ű��
	while (!pq.empty()) {
		pq_temp.push(pq.top());
		pq.pop();
	}

	while (!pq_temp.empty()) {

		Cell Now = pq_temp.top();
		pq_temp.pop();

		int next_life = Now.current_life - 1;  //1�ð� �����ٰ� �����ϰ�

		if (Now.state == 1) {  //��Ȱ��ȭ �Ǿ��ִٸ�

			//���� ���ð��� �����ִٸ� ��Ȱ��ȭ ����
			if (next_life > 0) {
				pq.push({ Now.origin_life, next_life, Now.state, Now.row, Now.col });
			}
			//���ð��� ������ Ȱ��ȭ �Ǿ���ϴ� ���
			else {
				pq.push({ Now.origin_life, Now.origin_life, 2, Now.row,Now.col });
			}

		}
		else{   //�̹� Ȱ��ȭ �� ����
			if (next_life > 0) //���� �����Ҵٸ�
			{
				pq.push({ Now.origin_life, next_life, Now.state, Now.row, Now.col });
			}

			for (int i = 0; i < 4; i++) {
				int next_row = Now.row + dr[i];
				int next_col = Now.col + dc[i];

				if (next_row < 0 || next_col < 0 || next_row>650 || next_col>650) continue;
				if (Visited[next_row][next_col] == 1) continue;

				Visited[next_row][next_col] = 1;
				pq.push({ Now.origin_life, Now.origin_life, 1, next_row, next_col });
			}

		}

	}

}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	freopen_s(new FILE*, "input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int test = 1; test <= T; test++) {


		int N, M, K;
		cin >> N >> M >> K;

		//�ʱ�ȭ
		for (int i = 0; i < 651; i++) {
			for (int j = 0; j < 651; j++) {
				Visited[i][j] = 0;
				Map[i][j] = 0;
			}
		}
		while (!pq.empty()) pq.pop();



		//�Է�
		for (int i = 300; i < 300 + N; i++) {
			for (int j = 300; j < 300 + M; j++) {
				cin >> Map[i][j];
				if (Map[i][j] == 0) continue;
				pq.push({ Map[i][j],Map[i][j],1,i,j });
				Visited[i][j] = 1;
			}
		}

		for (int i = 0; i < K; i++) {  //1�ð� ����
			FloodFill();
		}

		cout << "#" << test << " " << pq.size() << "\n";

	}

	return 0;
}