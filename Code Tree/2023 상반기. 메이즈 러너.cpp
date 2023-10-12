//https://www.codetree.ai/training-field/frequent-problems/problems/maze-runner/description?page=1&pageSize=20

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct pos {
	int row;
	int col;
};

struct P_Info {
	int row;
	int col;
	int index;
};


struct nextpos {
	int row;
	int col;
	int dist; //�ⱸ���� �ִ� �Ÿ�
	int dir;

	bool operator<(nextpos next) const {
		if (dist < next.dist) return false;
		else if (dist > next.dist) return true;
		else {
			if (dir < next.dir) return false;
			else if (dir > next.dir) return true;
			else return false;
		}
	}
};

struct spaceInfo {
	int arr[10] = { 0 };
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
int N, M, K;
int Map[11][11] = { 0, };
spaceInfo Person[11][11] = { };  //��� ��ġ -> ȸ����ų�� �ٲ��ֱ� ����
pos Escape;  //�ⱸ ��ǥ
P_Info Info[10];  //������� ����
bool Escaped[10] = { false, };  //Ż�⿩��
int accDist[10] = { 0, };   //�Ÿ� ����

void move() {
	// �����̴� ����
	// 1) �ִ� �Ÿ� : abs(x1-x2) + abs(y1-y2)
	// 2) ������ ���ÿ� ������ -> �� �����̰� ó���Ұ� ó���ؾ���
	// 3) �����¿� (��ĭ��)  �켱����: ����
	// 4) �ⱸ���� �ִܰŸ� �� ��������Ը� ������ ����
	// 5) ������ �� ������ Stay
	// 6) ��ĭ�� ������ �־ �� (������ ���� ��ġ �迭 �����) -> INFO

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	for (int i = 0; i < M; i++) {
		//�̹� Ż�������� ����
		if (Escaped[i]) continue;
		int nowRow = Info[i].row;
		int nowCol = Info[i].col;
		int nowDist = abs(nowRow - Escape.row) + abs(nowCol - Escape.col);
		priority_queue<nextpos> pq;
		for (int dir = 0; dir < 4; dir++) {
			int next_r = nowRow + dr[dir];
			int next_c = nowCol + dc[dir];
			if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) continue;
			if (Map[next_r][next_c] > 0) continue;
			// 1) �ִ� �Ÿ� : abs(x1-x2) + abs(y1-y2)
			// 3) �����¿� (��ĭ��)  �켱����: ����
			// 4) �ⱸ���� �ִܰŸ� �� ��������Ը� ������ ����
			int next_dist = abs(next_r - Escape.row) + abs(next_c - Escape.col);
			if (next_dist >= nowDist) continue;
			pq.push({ next_r,next_c, next_dist, dir });
		}
		// 5) ������ �� ������ Stay
		if (pq.empty()) continue;
		int next_r = pq.top().row;
		int next_c = pq.top().col;
		Info[i].row = next_r;
		Info[i].col = next_c;
		accDist[i]++;
		Person[nowRow][nowCol].arr[i] = 0;
		Person[next_r][next_c].arr[i] = 1;
		if (Info[i].row == Escape.row && Info[i].col == Escape.col) {
			Escaped[i] = true;
		}
	}
}


void rotation(int start_r, int start_c, int squareSize) {
	//�ð���� 90 ȸ�� (���, �ⱸ, ������ �� ���� ���ư�)
	//������ 1 ����
	int temp[11][11] = { 0, };
	bool escapeSwap = false;
	bool personSwap[10] = { false };
	//start_r   start_r+squareSize-1    start_c   start_c+squareSize-1
	//�ϴ� ȸ��
	for (int i = 0; i < squareSize; i++) {
		for (int j = 0; j < squareSize; j++) {
			//start_c + squareSize - 1 - i
			temp[start_r+j][start_c + squareSize - 1 - i] = Map[start_r + i][start_c + j];
			
			if ((start_r + i) == Escape.row && (start_c + j) == Escape.col&&!escapeSwap) {
				Escape.row = start_r + j;
				Escape.col = start_c + squareSize - 1 - i;
				escapeSwap = true;
				continue;
			}
			//Info �迭
			for (int k = 0; k < M; k++) {
				if (Escaped[k]) continue;
				if ((start_r + i) == Info[k].row && (start_c + j) == Info[k].col&&!personSwap[k]) {
					Info[k].row = start_r + j;
					Info[k].col = start_c + squareSize - 1 - i;
					personSwap[k] = true;
				}
			}
		}
	}

	for (int i = 0; i < squareSize; i++) {
		for (int j = 0; j < squareSize; j++) {
			Map[start_r + i][start_c + j] = temp[start_r + i][start_c + j];
			if (Map[start_r + i][start_c + j] > 0) {
				Map[start_r + i][start_c + j]--;
			}
		}
	}
}

void findSquare() {

	int squareSize = 2;
	bool flag = false;
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
					for (int k = 0; k < M; k++) {
						if (Escaped[k]) continue;
						if (Info[k].row == now_r && Info[k].col == now_c) {
							personCnt++;
							break;
						}
						
					}
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
			flag = true;
			break;
		}
		if (flag) break;
		squareSize++;
	}
}


void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
			for (int k = 0; k < 10; k++) {
				Person[i][j].arr[k] = 0;
			}
		}
	}

	for (int i = 0; i < M; i++) {
		int r, c;
		cin >> r >> c;
		Info[i] = { r,c, i };
		Person[r][c].arr[i] = 1;
	}

	int target_r, target_c;
	cin >> target_r >> target_c;
	Escape = { target_r,target_c };

}




void solution() {
	for (int i = 0; i < K; i++) {
		move();
		findSquare();
	}
	int Ans = 0;
	for (int i = 0; i < M; i++) {
		Ans += accDist[i];
	}
	cout << Ans << "\n";
	cout << Escape.row << " " << Escape.col << "\n";
}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	input();
	solution();

	return 0;
}