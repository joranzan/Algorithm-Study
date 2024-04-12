//���� �ð� : 07:59
//���� �ð� : 09:38
#include<iostream>
#include<vector>

using namespace std;

struct pos {
	int row;
	int col;
};

int N, M, K, C;
int TreeMap[21][21] = { 0, };  //��: -1
int PoisonMap[21][21] = { 0, };  //�������� �Ѹ� ��
int Answer = 0;
const int tree_dr[4] = { -1,1,0,0 };
const int tree_dc[4] = { 0,0,-1,1 };
const int poison_dr[4] = { -1,-1,1,1 };
const int poison_dc[4] = { -1,1,-1,1 };

int totalTreeCnt = 0;

void init() {
	cin >> N >> M >> K >> C;

	Answer = 0;
	totalTreeCnt = 0;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			cin >> TreeMap[r][c];
			if (TreeMap[r][c] >= 1) totalTreeCnt++;

			PoisonMap[r][c] = 0;
		}
	}


}

void growTree() {
	//1) ������ ����
	//1) ������ 4���� ĭ �� ������ �ִ� ĭ�� ����ŭ ����
	//2)***** ��� ������ ���ÿ� �Ͼ

	//int tempMap[21][21] = { 0, };

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			//���� ���̰ų� ������ ���ٸ� ����
			if (TreeMap[r][c] < 1) continue;
			//���� ���� ����
			//int cnt = TreeMap[r][c];
			int cnt = 0;
			for (int dir = 0; dir < 4; dir++) {
				int nextRow = r + tree_dr[dir];
				int nextCol = c + tree_dc[dir];
				if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;   //���� �� ����
				if (TreeMap[nextRow][nextCol] < 1) continue;  //���̰ų� ���� ������ ����
				cnt++;
			}
			//tempMap[r][c] = cnt;
			TreeMap[r][c] += cnt;
		}
	}

	/*for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (tempMap[r][c] < 1) continue;
			TreeMap[r][c] = tempMap[r][c];
		}
	}*/

	//������
	// cout << "������ ����\n";
	// for (int r = 1; r <= N; r++) {
	// 	for (int c = 1; c <= N; c++) {
	// 		cout << TreeMap[r][c] << " ";
	// 	}
	// 	cout << "\n";
	// }
	// cout << "\n";

}

void reproduction() {
	//2) ����

	//1) ������ �ִ� �������� ������ 4���� ĭ ����
	//1) ���̸� ����
	//2) �ٸ� ������ ����
	//3) �������� ����
	//4) ������ ĭ���� ���� ������ ����

	int tempMap[21][21] = { 0, };

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (TreeMap[r][c] < 1) continue;
			int nowTreeCnt = TreeMap[r][c];

			int cnt = 0;
			vector<int> targetDir;

			for (int dir = 0; dir < 4; dir++) {
				int nextRow = r + tree_dr[dir];
				int nextCol = c + tree_dc[dir];
				if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;   //���� �� ����
				if (TreeMap[nextRow][nextCol] != 0) continue;  //���̰ų� ������ ����
				if (PoisonMap[nextRow][nextCol] != 0) continue;
				cnt++;
				targetDir.push_back(dir);
			}

			if (cnt == 0) continue;
			int nextCnt = nowTreeCnt / cnt;

			for (int i = 0; i < cnt; i++) {
				int nextRow = r + tree_dr[targetDir[i]];
				int nextCol = c + tree_dc[targetDir[i]];
				tempMap[nextRow][nextCol] += nextCnt;
			}
			tempMap[r][c] = nowTreeCnt;
		}


	}


	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (tempMap[r][c] < 1) continue;
			TreeMap[r][c] = tempMap[r][c];
		}
	}

	//������
	// cout << "������ ����\n";
	// for (int r = 1; r <= N; r++) {
	// 	for (int c = 1; c <= N; c++) {
	// 		cout << TreeMap[r][c] << " ";
	// 	}
	// 	cout << "\n";
	// }
	// cout << "\n";

}
void scatterPoison() {
	//3) ������ �Ѹ�
	//1) �� ĭ �� �������� �ѷ��� �� ���� ���� �ڸ�Ǵ� ĭ�� �Ѹ�
	//2) ������ ���� ����
	//2 - 1) ������ ���� �� : �ƹ� �ϵ� �� �Ͼ
	//2 - 2) ������ �ִ� ��
	//1) Kĭ ��ŭ �밢������ ����
	//2) ���ĵǴ� ���� ���̰ų� ���� ������ ����
	//3) C�⸸ŭ �������� ��������(C + 1)�⿡ ������
	//	4) �̹� �ִµ� �ѷ����� �ٽ� C�⵿�� ����

	pos ResultIndex;
	int maxCnt = -1;
	// 20x20x4x20 = O(32000000)
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			//���� ���ų� ���̸� ����
			if (TreeMap[r][c] < 1) continue;
			int cnt = TreeMap[r][c];
			for (int dir = 0; dir < 4; dir++) {
				for (int k = 1; k <= K; k++) {
					int nextRow = r + poison_dr[dir] * k;
					int nextCol = c + poison_dc[dir] * k;
					if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) break;
					if (TreeMap[nextRow][nextCol] < 1) {
						break;
					}
					cnt += TreeMap[nextRow][nextCol];
				}
			}
			if (maxCnt > cnt) continue;
			//���� ��ã�Ҵٸ�
			if (maxCnt == -1) {
				ResultIndex.row = r;
				ResultIndex.col = c;
				maxCnt = cnt;
			}
			else if (maxCnt < cnt) {
				ResultIndex.row = r;
				ResultIndex.col = c;
				maxCnt = cnt;
			}
			//���� ���� �������, ���� ���� ���� ��쿡�� ���� ���� ĭ�� �������� �Ѹ�
			else if (maxCnt == cnt) {
				if (ResultIndex.row > r) {
					ResultIndex.row = r;
					ResultIndex.col = c;
					maxCnt = cnt;
				}
				else if (ResultIndex.row == r) {
					if (ResultIndex.col > c) {
						ResultIndex.row = r;
						ResultIndex.col = c;
						maxCnt = cnt;
					}
				}
			}
		}
	}

	if (maxCnt == -1) return;

	//cout << "������ ��ġ : (" << ResultIndex.row << "," << ResultIndex.col << ")\n�ڸ�� : " << maxCnt << "\n\n";

	Answer += maxCnt;
	TreeMap[ResultIndex.row][ResultIndex.col] = 0;
	PoisonMap[ResultIndex.row][ResultIndex.col] = C;

	for (int dir = 0; dir < 4; dir++) {
		for (int k = 1; k <= K; k++) {
			int nextRow = ResultIndex.row + poison_dr[dir] * k;
			int nextCol = ResultIndex.col + poison_dc[dir] * k;
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) break;
			if (TreeMap[nextRow][nextCol] < 1) {
				PoisonMap[nextRow][nextCol] = C;
				break;
			}
			TreeMap[nextRow][nextCol] = 0;
			PoisonMap[nextRow][nextCol] = C;
		}
	}

}

void solution() {

	for (int turn = 1; turn <= M; turn++) {

		// cout << "\n----------------------------------------------------------------";
		// cout << "\n" << turn << "�� ° ��\n\n";
		//������ ����
		growTree();
		reproduction();

		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (PoisonMap[r][c] == 0) continue;
				PoisonMap[r][c]--;
			}
		}

		scatterPoison();

		int treeLeft = 0;
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (TreeMap[r][c] < 1) continue;
				treeLeft++;
			}
		}

		if (treeLeft == 0) {
			break;
		}
	}
	cout << Answer;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	solution();

	return 0;
}

/*
���� �м�

�� ���� : NxN
������
	1) K�� ������ŭ �밢������ ����
	2) ���� �ִ� ��� ����

���� ����

1) ������ ����
	1) ������ 4���� ĭ �� ������ �ִ� ĭ�� ����ŭ ����
	2) *****��� ������ ���ÿ� �Ͼ

2) ����

	1) ������ �ִ� �������� ������ 4���� ĭ ����
		1) ���̸� ����
		2) �ٸ� ������ ����
		3) �������� ����
		4) ������ ĭ���� ���� ������ ����

3) ������ �Ѹ�
	1) �� ĭ �� �������� �ѷ��� �� ���� ���� �ڸ�Ǵ� ĭ�� �Ѹ�
	2) ������ ���� ����
		2-1) ������ ���� �� : �ƹ� �ϵ� �� �Ͼ
		2-2) ������ �ִ� ��
			1) Kĭ ��ŭ �밢������ ����
			2) ���ĵǴ� ���� ���̰ų� ���� ������ ����
			3) C�⸸ŭ �������� �������� (C+1)�⿡ ������
			4) �̹� �ִµ� �ѷ����� �ٽ� C�⵿�� ����



*/

/*

������ �Ѹ� �� �밢�� Kĭ Ž���ؼ� ���� �� �ִ��� �� �Ѹ���

*/