//���� �ð� : 19:21
//���� �ð� : 21:34
#include<iostream>
#include<vector>

using namespace std;

struct pos {
	int row;
	int col;
};

struct person {
	int id;
	bool escaped = false;
	pos nowPos;
	int path = 0;
};

/*
�Է�)
N : �̷� ũ�� (4�̻� 10����)
M : ������ �� (1�̻� 10����)
K : ���� �ݺ� �� (1�̻� 100����)
Map ���� : 0(��ĭ) , 1~9(������)
������ ��ǥ
�ⱸ ��ǥ
*/

int N, M, K;
int InputMap[11][11] = { 0, };
pos EscapePos;
person PersonInfo[11];
vector<int> PersonMap[11][11];

void init() {
	cin >> N >> M >> K;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			cin >> InputMap[r][c];
		}
	}

	for (int i = 1; i <= M; i++) {
		PersonInfo[i].id = i;
		cin >> PersonInfo[i].nowPos.row >> PersonInfo[i].nowPos.col;
	}

	cin >> EscapePos.row >> EscapePos.col;
}

void movePerson() {

//1. ��� ������ **���ÿ�** 1ĭ �̵�
//2. �����¿� 
//3. ���� ĭ���� �ⱸ �ִ� �Ÿ� > ������ ĭ �ⱸ �ִܰŸ�
//	(�ִܰŸ� : abs(x1-x2) + abs(y1-y2)
//4. �켱���� : ���� �¿�
//5. �������̸� �������� ���� (�� or �ִܰŸ� �Ȱ������)
//6. **��ĭ�� 2�� ������ ����**

	//��������� ���� ���
	//	1) nearPath = abs(�ⱸ��ǥ - �����ǥ) ���ϱ�
	//	2) nextnearPath = abs(�ⱸ ��ǥ - �׹��� ��ǥ)
	//	3) nextnearPath �ּ� �������� dir ���� ����
	//	4) �̵�

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	

	for (int i = 1; i <= M; i++) {
		//�̹� Ż���ߴٸ� ����
		if (PersonInfo[i].escaped) continue;

		//���� �������� ��ġ
		int nowRow = PersonInfo[i].nowPos.row;
		int nowCol = PersonInfo[i].nowPos.col;
		//���� �������� ��ġ���� �ⱸ���� �Ÿ�
		int nowNearPath = abs(nowRow - EscapePos.row) + abs(nowCol - EscapePos.col);



		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (InputMap[nextRow][nextCol] != 0) continue;
			//�������̸� �������� ����(�� or �ִܰŸ� �Ȱ������)
			int nextNearPath = abs(nextRow - EscapePos.row) + abs(nextCol - EscapePos.col);
			if (nextNearPath >= nowNearPath) continue;

			//���� ��������� ĭ ã�Ҵٸ� �̵�
			PersonInfo[i].nowPos = { nextRow, nextCol };
			PersonInfo[i].path += 1;
			//�̵��� ĭ�� Ż�ⱸ��� Ż��!
			if (nextRow == EscapePos.row && nextCol == EscapePos.col) {
				PersonInfo[i].escaped = true;
			}
			break;
		}
	}



}

pair<pos, int> findSquare() {

	

	//	�ⱸ(escapeRow, escapeCol) �� ��

	//	���簢���� �� ���� : h��� ���� �� ���� ��ǥ

	//	h = 2)

	//	escapeRow - (h - 1) <= ���� Row <= escapeRow
	//	escapeCol - (h - 1) <= ���� Col <= excapeCol

	//	���� ����� �ϳ��� �����Ѵٸ�
	//	��ȯ)
	//	- ������ǥ
	//	- ũ��
	bool foundPoint = false;

	for (int h = 2; h <= N; h++) {
		for (int r = EscapePos.row - (h - 1); r <= EscapePos.row; r++) {
			if (r <= 0 || r > N) continue;
			if (r + h - 1 <= 0 || r + h - 1 > N) continue;
			for (int c = EscapePos.col - (h - 1); c <= EscapePos.col; c++) {
				if (c <= 0 || c > N) continue;
				if (c + h - 1 <= 0 || c + h - 1 > N) continue;
				//���� ��� ��ǥ : (r,c) ~ (r+h-1, c+h-1)
				for (int Row = r; Row < r + h; Row++) {
					for (int Col = c; Col < c + h; Col++) {
						if (PersonMap[Row][Col].size() != 0) {
							//cout << "�簢�� ũ�� : " << h << "\n";
							//cout << "���� ��ǥ : (" << r << ", " << c << ")\n";
							foundPoint = true;
							return { {r,c},h };
							break;
						}
					}
					if (foundPoint) break;
				}
				if (foundPoint) break;
			}
			if (foundPoint) break;
		}
		if (foundPoint) break;
	}

}

void rotationSquare(pos squarePos, int squareSize) {

	/*
	3. ȸ��

		�ð���� 90�� ȸ�� �˰��� ����
		(ȸ���� �� ��ĭ�� ��� ������ ��� �Ұ���)

		- PersonInfo���� �簢�� ���� �ִ� ����� ID ��(r, c) ã�Ƴ���
		- ���� �� ���� r, c�� ��� ������ �ش� ID���� ��ġ �Ű��ֱ�
	*/

	int tempMap[11][11] = { 0, };
	int escapeRow = EscapePos.row;
	int escapeCol = EscapePos.col;

	for (int r = squarePos.row; r < squarePos.row + squareSize; r++) {
		for (int c = squarePos.col; c < squarePos.col + squareSize; c++) {
			tempMap[squarePos.row - squarePos.col + c][squarePos.col + squareSize - 1 - (r - squarePos.row)] = InputMap[r][c];
			//���� ��) squarePos.row + squareSize - r  vs   N - r + 1  vs squarePos.col+squareSize -1 -(r-squarePos.row)   
			//���� ��)c vs squarePos.row - squarePos.col + c
			bool debug1 = false;
			bool debug2 = false;

			//�ⱸ�� �ٲ������
			if (EscapePos.row == r && EscapePos.col == c) {
				escapeRow = squarePos.row - squarePos.col + c;
				escapeCol = squarePos.col + squareSize - 1 - (r - squarePos.row);
				//cout << "�ⱸ ����!\n";
				debug1 = true;
				//continue;
			}

			//��� ������ 
			for (int i = 0; i < PersonMap[r][c].size(); i++) {
				debug2 = true;
				PersonInfo[PersonMap[r][c][i]].nowPos.row = squarePos.row - squarePos.col + c;
				PersonInfo[PersonMap[r][c][i]].nowPos.col = squarePos.col + squareSize - 1 - (r - squarePos.row);
			}

			if (debug1 && debug2) {
				int debugging = -1;
			}

		}
	}

	EscapePos.row = escapeRow;
	EscapePos.col = escapeCol;

	for (int r = squarePos.row; r < squarePos.row + squareSize; r++) {
		for (int c = squarePos.col; c < squarePos.col + squareSize; c++) {
			InputMap[r][c] = tempMap[r][c];
			if (InputMap[r][c] != 0) InputMap[r][c]--;
		}
	}


}

void solution() {

	for (int k = 1; k <= K; k++) {

		//cout << k << "��° ��\n";

		//PersonMap �ʱ�ȭ
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				PersonMap[r][c].clear();
			}
		}

		bool allPlayerDone = true;

		//1. ������ �̵�
		movePerson();

		//PersonMap ����
		for (int i = 1; i <= M; i++) {
			if (PersonInfo[i].escaped) continue;
			allPlayerDone = false;
			PersonMap[PersonInfo[i].nowPos.row][PersonInfo[i].nowPos.col].push_back(PersonInfo[i].id);
		}

		////PersonMap �ʱ�ȭ
		//for (int r = 1; r <= N; r++) {
		//	for (int c = 1; c <= N; c++) {
		//		cout << PersonMap[r][c].size() << "�� ";
		//	}
		//	cout << "\n";
		//}

		
		if (allPlayerDone) break;

		//cout << "\n���� Map\n";

		//for (int r = 1; r <= N; r++) {
		//	for (int c = 1; c <= N; c++) {
		//		cout << InputMap[r][c] << " ";
		//	}
		//	cout << "\n";
		//}


		//2. ȸ���� �簢�� ã��
		pair<pos,int> ret = findSquare();
		
		pos squarePos = ret.first;
		int squareSize = ret.second;

		//�ð���� 90�� ȸ��
		rotationSquare(squarePos, squareSize);
		

		//cout << "\nȸ�� �� Map\n";
		//for (int r = 1; r <= N; r++) {
		//	for (int c = 1; c <= N; c++) {
		//		cout << InputMap[r][c] << " ";
		//	}
		//	cout << "\n";
		//}

		//cout << "\n�ⱸ ��ġ : ";
		//cout <<"(" << EscapePos.row << ", " << EscapePos.col << ")\n";
		//cout << "******************************************************************";
		//cout << "\n";
	}

	int sum = 0;

	for (int i = 1; i <= M; i++) {
		sum += PersonInfo[i].path;
	}

	cout << sum << "\n";
	cout << EscapePos.row << " " << EscapePos.col;

}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	solution();

	return 0;
}

/*
���� �м�

������ : M��
�� : NxN (1,1)

�̷� ĭ ����

1) ��ĭ : �̵� ����
2) �� :
	- �̵� �Ұ���
	- (1~9) ������ (ȸ���� �� -1�� ����)
	- ������ 0 �Ǹ� ��ĭ (�̵� ����)

3) �ⱸ : Ż��

----------------------------------------------------------------------
K�� ���� �ݺ� (��� �����ڰ� Ż�⿡ �����Ѵٸ�)

����)
---------------------------------------------------------
1. ������ ��ĭ �� �̵�

����)

1. ��� ������ **���ÿ�**
2. �����¿� 
3. ���� ĭ���� �ⱸ �ִ� �Ÿ� > ������ ĭ �ⱸ �ִܰŸ�
	(�ִܰŸ� : abs(x1-x2) + abs(y1-y2)
4. �켱���� : ���� �¿�
5. �������̸� �������� ���� (�� or �ִܰŸ� �Ȱ������)
6. **��ĭ�� 2�� ������ ����**

-----------------------------------------------------------

�̵� �� �̷� ȸ�� (ȸ�� �˰��� �ʿ�)

1) �� �� �̻��� �����ڿ� �ⱸ�� ������ ���� ���� ���簢��
2) �켱����
	- �»�� ��ǥ�� r�� ������
	- ������ ��� : c�� ������
3) �ð���� 90�� ȸ��
4) ������ --;


--------------------------------------------------------

*******��� �����ڵ��� �̵��Ÿ� ��!*************
*******�ⱸ ��ġ

-----------------------------------------------------------------
*/

/*
����

5 3 8
0 0 0 0 1
9 2 2 0 0
0 1 0 1 0
0 0 0 1 0
0 0 0 0 0
1 3
3 1
3 5
3 3


1. ������ �̵�

��������� ���� ��� 
1) nearPath = abs(�ⱸ��ǥ - �����ǥ) ���ϱ�
2) nextnearPath = abs(�ⱸ ��ǥ - �׹��� ��ǥ)
3) nextnearPath �ּ� �������� dir ���� ����
4) �̵�


2-0) �������� ��ġ �Ǻ��Ͽ� ��� �����ϴ��� ���� �����س���


2. ȸ���� �簢�� ã��

�ⱸ (escapeRow, escapeCol) �� �� 

���簢���� �� ���� : h��� ���� �� ���� ��ǥ

h = 2)

escapeRow-(h-1) <= ���� Row <= escapeRow
escapeCol-(h-1) <= ���� Col <= excapeCol

���� ����� �ϳ��� �����Ѵٸ�
��ȯ) 
- ������ǥ
- ũ�� 



3. ȸ��

�ð���� 90�� ȸ�� �˰��� ����
(ȸ���� �� ��ĭ�� ��� ������ ��� �Ұ���)

- PersonInfo���� �簢�� ���� �ִ� ����� ID �� (r,c) ã�Ƴ���
- ���� �� ���� r,c�� ��� ������ �ش� ID���� ��ġ �Ű��ֱ�

vector<int> v[r][c];  //id ����


int tempMap[11][11]={0,};

for(int r=1;r<=N;r++){
	for(int c=1;c<=N;c++){   
		tempMap[c][N-r+1] = Map[r][c];
		//�ⱸ�� �ٲ������
		for(int i=0;i<v[r][c].size();i++){
			PersonMap[v[i]].row = c;
			PersonMap[v[i]].col = N-r+1;
		}
	}
}

for(int r=1;r<=N;r++){
	for(int c=1;c<=N;c++){
		Map[r][c] = temp[r][c];
		if(Map[r][c]!=0) Map[r][c]--;
	}
}

*/

/*
��� ������ ���� �� �ִµ� ��� �ִ��� �Ǻ� ��� ���� ���ϱ�

PersonMap?
�ƴϸ� PersonInfo �� Ž���ϱ�?


�̵� �� ȸ���ϱ� ���� �̸� ��� �ִ� ��ǥ �� �ľ��س��� 
----> �갡 ���� ���� �� (��� �ʱ�ȭ �Ź� �ؾ���)
*/