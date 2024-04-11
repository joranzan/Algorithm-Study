//���� �ð� : 09:00
//���� �ð� : 
#include<iostream>
#include<vector>
#include<set>

using namespace std;

/*
�Է�)
L : �� ũ��(3~40)
N : ��� ��(1~30)
Q : �� ��(1~100)

�� ���� :  0(��ĭ) 1(����) 2(��)

r c h w k
k: (1~100)


i d : i�� ��� d ���� (�� �� �� ��)
*/

const int dr[4] = { -1,0,1,0 };
const int dc[4] = { 0,1,0, -1 };


struct pos {
	int row;
	int col;
};

struct knight {
	int id;
	pos nowPos;
	int height;
	int width;
	int hp;
	bool alive = true;
};

int L, N, Q;
knight KnightInfo[31];  //��� ���� ����
int KnightMap[41][41] = { 0, }; //ID�� ����
int InputMap[41][41] = { 0, }; //����&������
int OriginHP[31] = { 0, };
bool Moved[31] = { false, };
vector<int> NeedtoMoveKnights;


void init() {
	cin >> L >> N >> Q;

	for (int r = 1; r <= L; r++) {
		for (int c = 1; c <= L; c++) {
			KnightMap[r][c] = 0;
			cin >> InputMap[r][c]; //0(��ĭ) 1(����) 2(��)
		}
	}

	for (int i = 1; i <= N; i++) {
		KnightInfo[i].id = i;
		cin >> KnightInfo[i].nowPos.row >> KnightInfo[i].nowPos.col >> KnightInfo[i].height >> KnightInfo[i].width >> KnightInfo[i].hp;
		OriginHP[i] = KnightInfo[i].hp;
		for (int r = KnightInfo[i].nowPos.row; r < KnightInfo[i].nowPos.row + KnightInfo[i].height; r++) {
			for (int c = KnightInfo[i].nowPos.col; c < KnightInfo[i].nowPos.col + KnightInfo[i].width; c++) {
				KnightMap[r][c] = i;
			}
		}
	}
}

bool isValid(int id, int dir) {

	int nowKnightRow = KnightInfo[id].nowPos.row;
	int nowKnightCol = KnightInfo[id].nowPos.col;

	set<int> nextKnightId;

	bool flag = true;

	//���� üũ
	switch (dir) {
	case 0: {     //��

		for (int c = nowKnightCol; c < nowKnightCol + KnightInfo[id].width; c++) {
			int nextRow = nowKnightRow + dr[dir];
			int nextCol = c;

			//�Ǻ��ϱ�
			if (nextRow <= 0 || nextCol <= 0 || nextRow > L || nextCol > L) {
				flag = false;
				break;
			}
			if (InputMap[nextRow][nextCol] == 2) {
				flag = false;
				//cout << "\n��!!!  False\n";
				break;
			}
			//��簡 �����Ѵٸ�
			if (KnightMap[nextRow][nextCol] != 0) {
				if (!KnightInfo[KnightMap[nextRow][nextCol]].alive) continue;
				nextKnightId.insert(KnightMap[nextRow][nextCol]);
			}
		}


		break;
	}
	case 1: {     //��

		for (int r = nowKnightRow; r < nowKnightRow + KnightInfo[id].height; r++) {
			int nextRow = r;
			int nextCol = nowKnightCol + KnightInfo[id].width - 1 + dc[dir];

			//�Ǻ��ϱ�
			if (nextRow <= 0 || nextCol <= 0 || nextRow > L || nextCol > L) {
				flag = false;
				break;
			}
			if (InputMap[nextRow][nextCol] == 2) {
				flag = false;
				//cout << "\n��!!!  False\n";
				break;
			}
			//��簡 �����Ѵٸ�
			if (KnightMap[nextRow][nextCol] != 0) {
				if (!KnightInfo[KnightMap[nextRow][nextCol]].alive) continue;
				nextKnightId.insert(KnightMap[nextRow][nextCol]);
			}
		}

		break;
	}
	case 2: {     //��

		for (int c = nowKnightCol; c < nowKnightCol + KnightInfo[id].width; c++) {

			int nextRow = nowKnightRow + KnightInfo[id].height - 1 + dr[dir];
			int nextCol = c;

			//�Ǻ��ϱ�
			if (nextRow <= 0 || nextCol <= 0 || nextRow > L || nextCol > L) {
				flag = false;
				break;
			}
			if (InputMap[nextRow][nextCol] == 2) {
				flag = false;
				//cout << "\n��!!!  False\n";
				break;
			}

			//��簡 �����Ѵٸ�
			if (KnightMap[nextRow][nextCol] != 0) {
				if (!KnightInfo[KnightMap[nextRow][nextCol]].alive) continue;
				nextKnightId.insert(KnightMap[nextRow][nextCol]);
			}
		}
		break;
	}
	case 3: {     //��

		for (int r = nowKnightRow; r < nowKnightRow + KnightInfo[id].height; r++) {

			int nextRow = r;
			int nextCol = nowKnightCol + dc[dir];

			//�Ǻ��ϱ�
			if (nextRow <= 0 || nextCol <= 0 || nextRow > L || nextCol > L) {
				flag = false;
				break;
			}
			if (InputMap[nextRow][nextCol] == 2) {
				flag = false;
				//cout << "\n��!!!  False\n";
				break;
			}

			//��簡 �����Ѵٸ�
			if (KnightMap[nextRow][nextCol] != 0) {
				if (!KnightInfo[KnightMap[nextRow][nextCol]].alive) continue;
				nextKnightId.insert(KnightMap[nextRow][nextCol]);
			}
		}
		break;
	}
	}

	if (!flag) {
		//cout << "�̵� �Ұ���\n";

		return flag;
	}
	int debugging = -1;
	for (auto it = nextKnightId.begin(); it != nextKnightId.end(); it++) {
		//cout << *it << " ";
		NeedtoMoveKnights.push_back(*it);
		flag = isValid(*it, dir);

		if (!flag) break;
	}
	//cout << "\n";


	//���� �Ұ����ϴٸ� false ��ȯ
	if (!flag) {
		return flag;
	}

	//true ��ȯ
	return flag;
}


void moveKnight(int dir) {

	for (int i = NeedtoMoveKnights.size() - 1; i >= 0; i--) {
		int id = NeedtoMoveKnights[i];
		Moved[id] = true;
		//cout<<id<<" ";
		int nowKnightRow = KnightInfo[id].nowPos.row;
		int nowKnightCol = KnightInfo[id].nowPos.col;
		//�̵�
		switch (dir) {
		case 0: {     //��

			for (int r = nowKnightRow; r < nowKnightRow + KnightInfo[id].height; r++) {
				for (int c = nowKnightCol; c < nowKnightCol + KnightInfo[id].width; c++) {
					int nextRow = r + dr[dir];
					int nextCol = c + dc[dir];
					if (InputMap[nextRow][nextCol] == 2) {
						int debugging = -1;
					}
					KnightMap[nextRow][nextCol] = KnightMap[r][c];
					KnightMap[r][c] = 0;
				}
			}

			KnightInfo[id].nowPos = { nowKnightRow + dr[dir], nowKnightCol + dc[dir] };

			break;
		}
		case 1: {     //��

			for (int c = nowKnightCol + KnightInfo[id].width - 1; c >= nowKnightCol; c--) {
				for (int r = nowKnightRow + KnightInfo[id].height - 1; r >= nowKnightRow; r--) {
					int nextRow = r + dr[dir];
					int nextCol = c + dc[dir];
					if (InputMap[nextRow][nextCol] == 2) {
						int debugging = -1;
					}
					KnightMap[nextRow][nextCol] = KnightMap[r][c];
					KnightMap[r][c] = 0;
				}
			}

			KnightInfo[id].nowPos = { nowKnightRow + dr[dir], nowKnightCol + dc[dir] };

			break;
		}
		case 2: {     //��



			for (int r = nowKnightRow + KnightInfo[id].height - 1; r >= nowKnightRow; r--) {
				for (int c = nowKnightCol + KnightInfo[id].width - 1; c >= nowKnightCol; c--) {
					int nextRow = r + dr[dir];
					int nextCol = c + dc[dir];
					if (InputMap[nextRow][nextCol] == 2) {
						int debugging = -1;
					}
					KnightMap[nextRow][nextCol] = KnightMap[r][c];
					KnightMap[r][c] = 0;
				}
			}

			KnightInfo[id].nowPos = { nowKnightRow + dr[dir], nowKnightCol + dc[dir] };

			break;
		}
		case 3: {     //��

			for (int c = nowKnightCol; c < nowKnightCol + KnightInfo[id].width; c++) {
				for (int r = nowKnightRow; r < nowKnightRow + KnightInfo[id].height; r++) {
					int nextRow = r + dr[dir];
					int nextCol = c + dc[dir];
					if (InputMap[nextRow][nextCol] == 2) {
						int debugging = -1;
					}
					KnightMap[nextRow][nextCol] = KnightMap[r][c];
					KnightMap[r][c] = 0;
				}
			}

			KnightInfo[id].nowPos = { nowKnightRow + dr[dir], nowKnightCol + dc[dir] };

			break;
		}
		}
	}

}

void solution() {

	for (int q = 1; q <= Q; q++) {  //100
		int id, dir;
		cin >> id >> dir;

		NeedtoMoveKnights.clear();

		for (int i = 1; i <= N; i++) {
			Moved[i] = false;
		}

		//cout << q << "��° ��ɾ�: id(" << id << ") ����(" << dir << ")\n";

		//���� �̹� ������ٸ� ����
		if (!KnightInfo[id].alive) continue;

		// cout << "\n***********������***********\n";
		// for (int r = 1; r <= L; r++) {
		// 	for (int c = 1; c <= L; c++) {
		// 		cout << KnightMap[r][c] << " ";
		// 	}
		// 	cout << "\n";
		// }

		NeedtoMoveKnights.push_back(id);

		bool flag = isValid(id, dir);

		if (!flag) {
			//cout << "������� ���� XXXXXXXXXXXXXX\n\n\n";
			continue;
		};

		moveKnight(dir);

		// for (int i = 0; i < NeedtoMoveKnights.size(); i++) {
		// 	cout << NeedtoMoveKnights[i] << " ";
		// }

		// cout << "\n***********������***********\n";
		// for (int r = 1; r <= L; r++) {
		// 	for (int c = 1; c <= L; c++) {
		// 		cout << KnightMap[r][c] << " ";
		// 	}
		// 	cout << "\n";
		// }

		// cout << "\n\n\n";


		vector<int> nowDeadKnight;

		//ü�� ��� 
		for (int i = 1; i <= N; i++) {  //30
			if (!KnightInfo[i].alive) continue;
			if (id == i) continue;
			if (!Moved[i]) continue;
			int trapCnt = 0;

			int Row = KnightInfo[i].nowPos.row;
			int Col = KnightInfo[i].nowPos.col;

			for (int r = Row; r < Row + KnightInfo[i].height; r++) {
				for (int c = Col; c < Col + KnightInfo[i].width; c++) {
					if (InputMap[r][c] == 1) trapCnt++;
				}
			}


			KnightInfo[i].hp -= trapCnt;

			//cout << "$$$$$$$$������$$$$$$$$ " << trapCnt << "\n\n\n";


			if (KnightInfo[i].hp <= 0) {
				//cout << i << "�� ��� �׾���----------\n";
				KnightInfo[i].hp = 0;
				KnightInfo[i].alive = false;
				nowDeadKnight.push_back(i);
			}
		}
		//KnightMap ����
		for (int i = 0; i < nowDeadKnight.size(); i++) {
			int nowID = nowDeadKnight[i];
			int Row = KnightInfo[i].nowPos.row;
			int Col = KnightInfo[i].nowPos.col;
			for (int r = Row; r < Row + KnightInfo[i].height; r++) {
				for (int c = Col; c < Col + KnightInfo[i].width; c++) {
					KnightMap[r][c] = 0;
				}
			}
		}
		int debugging = -1;
	}

	int Answer = 0;

	for (int i = 1; i <= N; i++) {
		if (!KnightInfo[i].alive) continue;
		Answer += (OriginHP[i] - KnightInfo[i].hp);
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

Map : LxL (1,1)

- ��ĭ
- ����
- ��

�ս��� ������ �������� ���� ���ĳ� �� ����
��� ����)

	(r,c) : ����� �ʱ� ��ġ
	(hxw) ����
	 k : ü��

���� ����

1) ��� �̵�
- ���� ��� ���� ��� : �����¿� �� �ϳ��� �� ĭ �̵�
	1) �̵� ĭ�� �ٸ� ��� �ִٸ� ���������� ��ĭ �з���
		- ������ �̵��� ���� wxh ���簢���� ���� ����ŭ ������ ����
		- ü�� ����
		- ü�� < 0 �̸� �����
		- ����� ���� ���� ���� ������
		- *****������ ��� �и� �Ŀ� ���� ����*****

	2) ������ ���⿡�� ���� �ִٸ� ��� ��� �̵��� �� ����
	3) ü���ǿ��� ����� ���� ��� ����

2) ��� Demage


*/


/*
Test Case

4 3 3
0 0 1 0
0 0 1 0
1 1 0 1
0 0 2 0
1 2 2 1 5
2 1 2 1 1
3 2 1 2 3
1 2
2 1
3 3

1�� ���)
id = 1
dir = 2 (��)

�̵��� �� �ִ��� �Ǻ�

1�� ��簡 dir�������� �̵� �� ĭ �Ǻ�
-----> 3�� ��簡 ��������
	3�� ��簡 dir �������� �̵��� ĭ �Ǻ�
	----> ���� �����Ƿ� false return

�� �� ����

2�� ���)
id = 2
dir = 1 (��)
1.  ***************************************

2�� ��簡 dir�������� �̵��� ĭ �Ǻ�
-----> 1�����, 3�� ��� �������� (set�� ����)
	--> 1�� ��� dir���� �̵� �� ĭ �Ǻ� : true
	--> 3�� ��� dir���� �̵� �� ĭ �Ǻ� : true

2.***********************************************

move() --> ���������� �̵� ��Ŵ (��� ������ �κп� �̵� ��Ŵ)

3. **********************************************

���� �Ǻ� �� ü�� ���

4. ********************************************

�׾����� �Ǻ� �� ����



*/