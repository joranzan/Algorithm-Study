#include<iostream>
#include<algorithm>


using namespace std;
/*
  0 1 2 3  0 1 2 3 4 5
0            ��
1
2
3

0 ��
1
2
3
4
5
*/

int N;
int blockID = 1;
int t, startRow, startCol;
// 1: 1x1 
// 2: 1x2
// 3: 2x1
const int t_size_r[4] = { 0,0,0,1 };  
const int t_size_c[4] = { 0,0,1,0 };
int typeVersion[10001] = { 0, };
int Green[6][4] = { 0, };
int Blue[4][6] = { 0, };
int score = 0;
//�ʷϻ� ����(6x4)
//�Ķ��� ����(4x6)


void updateBoard(int boardtype, int updatedPos) {
	//�ʷϻ� ������Ʈ
	if (boardtype == 0) {

		for (int r = updatedPos; r >= 0; r--) {
			for (int c = 0; c < 4; c++) {
				//��� ������ ����
				if (Green[r][c] == 0) continue;
				int nowID = Green[r][c];
				int nowType = typeVersion[nowID];
				//����� �ִµ� 2x1 ����� ���κ��̸� ���� (�̹� �Ű����Ƿ�)
				if (nowType == 3 && r != 5 && Green[r + 1][c] == nowID) continue;
				
				switch (nowType) {
				case 1: {    //1x1

					for (int temp_r = 5; temp_r > r; temp_r--) {
						if (Green[temp_r][c] == 0) {
							Green[temp_r][c] = nowID;
							Green[r][c] = 0;
							break;
						}
					}
					break;
				}
				case 2: {    //1x2
					if (c == 3) break;
					int result_r = r;
					for (int temp_r = r+1; temp_r <= 5; temp_r++) {
						if (Green[temp_r][c] == 0 && Green[temp_r][c + 1] == 0) {
							result_r = temp_r;
						}
						else break;
					}
					if (result_r == r) break;
					Green[result_r][c] = nowID;
					Green[r][c] = 0;
					if (Green[r][c + 1] != nowID) break;
					Green[result_r][c + 1] = nowID;
					Green[r][c + 1] = 0;
					

					break;
				}
				case 3: {    //2x1
					if (r == 0) break;
					int result_r = r;
					for (int temp_r = r+1; temp_r <= 5; temp_r++) {
						if (Green[temp_r][c] == 0) {
							result_r = temp_r;
						}
						else break;
					}
					if (result_r == r) break;
					Green[result_r][c] = nowID;
					Green[r][c] = 0;

					if (Green[r - 1][c] != nowID) break;
					Green[result_r - 1][c] = nowID;
					Green[r - 1][c] = 0;

					break;
				}
				}
			}
		}
	}
	//�Ķ��� ������Ʈ
	else if (boardtype == 1) {
		for (int c = updatedPos; c >= 0; c--) {
			for (int r = 0; r < 4; r++) {
				//��� ������ ����
				if (Blue[r][c] == 0) continue;
				int nowID = Blue[r][c];
				int nowType = typeVersion[nowID];
				//����� �ִµ� 1x2 ����� ���κ��̸� ���� (�̹� �Ű����Ƿ�)
				if (nowType == 2 && c != 5 && Blue[r][c+1] == nowID) continue;

				switch (nowType) {
				case 1: {  //1x1
					for (int temp_c = 5; temp_c > c; temp_c--) {
						if (Blue[r][temp_c] == 0) {
							Blue[r][temp_c] = nowID;
							Blue[r][c] = 0;
							break;
						}
					}
					break;
				}
				case 2: {  //1x2

					if (c == 0) break;
					int result_c = c;
					for (int temp_c = c+1; temp_c <= 5; temp_c++) {
						if (Blue[r][temp_c] == 0) {
							result_c = temp_c;
						}
						else break;
					}
					if (result_c == c) break;
					Blue[r][result_c] = nowID;
					Blue[r][c] = 0;
					if (Blue[r][c - 1] != nowID) break;
					Blue[r][result_c - 1] = nowID;
					Blue[r][c - 1] = 0;

					break;
				}
				case 3: {  //2x1
					if (r == 3) break;
					int result_c = c;
					for (int temp_c = c+1; temp_c <=5 ; temp_c++) {
						if (Blue[r][temp_c] == 0 && Blue[r + 1][temp_c] == 0) {
							result_c = temp_c;
						}
						else break;
					}
					if (result_c == c) break;
					Blue[r][result_c] = nowID;
					Blue[r][c] = 0;
					if (Blue[r + 1][c] != nowID) break;
					Blue[r + 1][result_c] = nowID;
					Blue[r + 1][c] = 0;

					break;
				}

				}
			}
		}

	}
}

void solution(){


	cin >> t >> startRow >> startCol; //(r,c)�� t type�� ��� 
	typeVersion[blockID] = t;
	//�ʷϻ� ���忡 �̵��� �� �ִ� ĭ���� �̵� (��� �Ǵ� ��� ���� ������)   --> �������� ����
	//O(12)
	//int blockGreenRow = 0;   //���������� ������ �ִ� ��
	//for (int r = 5; r >= 0; r--) {   
	//	bool valid = true;
	//	for (int c = startCol; c <= startCol + t_size_c[t]; c++) {
	//		if (Green[r][c] != 0) valid = false;
	//	}

	//	if(valid) {
	//		blockGreenRow = r;
	//		break;
	//	}
	//}
	int blockGreenRow_1 = 0;
	int blockGreenRow_2 = 0;
	for (int r = 0; r <= 5; r++) {
		if (Green[r][startCol] != 0) break;
		blockGreenRow_1 = r;
	}
	for (int r = 0; r <= 5; r++) {
		if (Green[r][startCol + 1] != 0) break;
		blockGreenRow_2 = r;
	}


	if(t == 1){
		Green[blockGreenRow_1][startCol] = blockID;
	}
	else if (t == 2) {
		int row = min(blockGreenRow_1, blockGreenRow_2);
		Green[row][startCol] = blockID;
		Green[row][startCol + 1] = blockID;
	}
	else if (t == 3) {
		Green[blockGreenRow_1][startCol] = blockID;
		Green[blockGreenRow_1 - 1][startCol] = blockID;
	}
	
	
	
	//�Ķ��� ���忡 �̵��� �� �ִ� ĭ���� �̵� (��� �Ǵ� ��� ���� ������)   --> �������� ����
	//O(12)
	//int blockBlueCol = 0;
	//for (int c = 5; c >= 0; c--) {
	//	bool valid = true;
	//	for (int r = startRow; r <= startRow + t_size_r[t]; r++) {
	//		if (Blue[r][c] != 0) valid = false;
	//	}
	//	if (valid) {
	//		blockBlueCol = c;
	//		break;
	//	}
	//}

	
	int blockBlueCol_1 = 0;
	int blockBlueCol_2 = 0;
	for (int c = 0; c <= 5; c++) {
		if (Blue[startRow][c] != 0) break;
		blockBlueCol_1 = c;
	}
	for (int c = 0; c <= 5; c++) {
		if (Blue[startRow + 1][c] != 0) break;
		blockBlueCol_2 = c;
	}
	


	if (t == 1) {
		Blue[startRow][blockBlueCol_1] = blockID;
	}
	
	else if (t == 2) {
		Blue[startRow][blockBlueCol_1] = blockID;
		Blue[startRow][blockBlueCol_1 - 1] = blockID;
	}
	else if (t == 3) {
		
		int col = min(blockBlueCol_1, blockBlueCol_2);
		Blue[startRow][col] = blockID;
		Blue[startRow + 1][col] = blockID;
	}

	/*
	(���� 1x1 �Ǵ� 1x2�� Ư��ĭ�� ���ƴٸ� continue)

	�ʷϻ� ������ ���� ���ִ� �� �ִ��� Ȯ��
	�ִٸ� -> ������ ������ ���� (����++)
	*/

	bool greenFilled = true;
	if (t == 1) {
		if (blockGreenRow_1 <= 1) greenFilled = false;
	}
	else if (t == 2) {
		if (min(blockGreenRow_1, blockBlueCol_2) <= 1) greenFilled = false;
	}

	while (greenFilled) {
		
		bool isUpdated = false;

		for (int r = 2; r <= 5; r++) {
			bool isFilled = true;
			for (int c = 0; c < 4; c++) {
				if (Green[r][c] == 0) {
					isFilled = false;
					break;
				}
			}

			//���� ���ִٸ�
			if (isFilled) {
				score++;
				for (int c = 0; c < 4; c++) {
					Green[r][c] = 0;
				}
				updateBoard(0, r);
				isUpdated = true;
				break;
			}
		}

		if (!isUpdated) break;
	}

	/*
	(���� 1x1 �Ǵ� 2x1�� Ư��ĭ�� ���ƴٸ� continue)

	�Ķ��� ������ ���� ���ִ� �� �ִ��� Ȯ��
	�ִٸ� -> ������ ������ ���� (����++)
	*/
	bool blueFilled = true;
	if (t == 1) {
		if (blockBlueCol_1 <= 1) blueFilled = false;
	}
	else if (t == 2) {
		if (min(blockBlueCol_1, blockBlueCol_2) <= 1) {
			blueFilled = false;
		}
	}

	while (blueFilled) {

		bool isUpdated = false;

		for (int c = 2; c <= 5; c++) {
			bool isFilled = true;
			for (int r = 0; r < 4; r++) {
				if (Blue[r][c] == 0) {
					isFilled = false;
					break;
				}
			}

			//���� ���ִٸ�
			if (isFilled) {
				score++;
				for (int r = 0; r < 4; r++) {
					Blue[r][c] = 0;
				}
				updateBoard(1, c);
				isUpdated = true;
				break;
			}
		}

		if (!isUpdated) break;
	}


	//�ʷϻ� ������ ���� ĭ (��) Ȯ�� -> ���� �ִٸ� ���� ����ŭ ���� �Ʒ� �� ����
	int GreenEraseCnt = 0;
	int BlueEraseCnt = 0;

	for (int r = 0; r <= 1; r++) {
		for (int c = 0; c < 4; c++) {
			if (Green[r][c] != 0) {
				GreenEraseCnt++;
				break;
			}
		}
	}

	for (int c = 0; c <= 1; c++) {
		for (int r = 0; r < 4; r++) {
			if (Blue[r][c] != 0) {
				BlueEraseCnt++;
				break;
			}
		}
	}

	for (int r = 5; r > 5 - GreenEraseCnt; r--) {
		for (int c = 0; c < 4; c++) {
			Green[r][c] = 0;
		}
	}

	for (int c = 5; c > 5 - BlueEraseCnt; c--) {
		for (int r = 0; r < 4; r++) {
			Blue[r][c] = 0;
		}
	}

	if (GreenEraseCnt != 0) {
		for (int r = 5-GreenEraseCnt; r >= 2-GreenEraseCnt; r--) {
			for (int c = 0; c < 4; c++) {
				Green[r + GreenEraseCnt][c] = Green[r][c];
				Green[r][c] = 0;
			}
		}
	}
	if (BlueEraseCnt != 0) {
		for (int c = 5 - BlueEraseCnt; c >= 2 - BlueEraseCnt; c--) {
			for (int r = 0; r < 4; r++) {
				Blue[r][c + BlueEraseCnt] = Blue[r][c];
				Blue[r][c] = 0;
			}
		}
	}
	



	//�Ķ��� ������ ���� ĭ (��) Ȯ�� -> ���� �ִٸ� ���� ����ŭ ���� ������ �� ����


	//��ǥ: ���������� Ÿ���� �ִ� ĭ�� ����

	blockID++;

}

int main() {

	ios::sync_with_stdio(false); 
	cin.tie(NULL); cout.tie(NULL);


	cin >> N;
	for (int i = 0; i < N; i++) {
		solution();
		int debugging = -1;
	}

	//�����ִ� Ÿ�� ���� ����
	int cnt = 0;
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 4; c++) {
			if (Green[r][c] != 0) cnt++;
			if (Blue[c][r] != 0) cnt++;
		}
	}

	cout << score << "\n" << cnt;
	

	//����, Ÿ�� ���� ���

	return 0;
}

/*
���� �м�

(x, y) : (��, ��)
ĭ ���� : �� �� ��

1. ��� ���� ��ġ ���� �� �̵�

1) �������� ���� ��� : ����ġ���� �ʷϻ�, �Ķ������� �̵�
(��� ���� ������)


2) �ϳ��� ���� ���� ���� Ÿ�� ��� ����� (�Ȼ����������)
3) �� ��(����)/��(�Ķ�) ä���� �̵�
4) +1�� ȹ��


2. Ư���� ĭ 

1) �ʷϻ� : 0~1�� ��
����� �ִ� ���� �� ��ŭ �Ʒ� ����� + �̵�

2) �Ķ��� 0~1�� ��
����� �ִ� ���� �� ��ŭ ������ ����� + �̵�


3. �켱���� : ��/�� ĭ �ϼ� �� �Ϸ� �Ŀ� ����ȹ�� �� ����ĭ ó��


4. ����� �������� �������� ���� ���� ������� ���� ����



��ǥ : ���������� Ÿ���� �ִ� ĭ�� ����
�Է�)
N : ��� ���� Ƚ��
t x y : type, (x,y)

*/

/*

while (greenFilled) {

		for (int r = nowRow; r > 1; r--) {
			bool isFilled = true;
			for (int c = 0; c < 4; c++) {
				if (Green[r][c] != 0) {
					isFilled = false;
					break;
				}
			}

			//���� ���ִٸ�
			if (isFilled) {
				for (int c = 0; c < 4; c++) {
					Green[r][c] = 0;
				}
				//updateBoard(0);
			}
		}
	}

*/


/*
���� ����

������ �� �ִ� ������ ã�Ƴ�������
*/