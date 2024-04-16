#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int Map[10][10] = { 0, };
int Answer = 2112345678;
int PaperCnt[6] = { 0, };

void Recursion(int cnt) {

	//���� ����
	if (cnt >= Answer) return;

	bool allDone = true;

	int nowCnt = 0;

	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (Map[r][c] == 1) {
				allDone = false;
				break;
			}
		}
		if (!allDone) break;
	}

	if (allDone) {
		Answer = min(Answer, cnt);
	}
	


	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (Map[r][c] == 0) continue;

			for (int PaperSize = 5; PaperSize >= 1; PaperSize--) {

				//���� ���� �� ����ٸ� ����
				if (r + PaperSize > 10 || c + PaperSize > 10) continue;
				if (PaperCnt[PaperSize] >= 5) continue;
				//���� �� �ִ��� üũ
				bool isValid = true;
				for (int i = r; i < r + PaperSize; i++) {
					for (int j = c; j < c + PaperSize; j++) {
						if (Map[i][j]==0) {
							isValid = false;
							break;
						}
					}
					if (!isValid) break;
				}

				//���� �� �ִٸ�
				if (isValid) {
					
					//���̰�

					PaperCnt[PaperSize]++;

					for (int i = r; i < r + PaperSize; i++) {
						for (int j = c; j < c + PaperSize; j++) {
							Map[i][j] = 0;
						}
					}

					//���� ã���� ��
					Recursion(cnt + 1);

					PaperCnt[PaperSize]--;

					for (int i = r; i < r + PaperSize; i++) {
						for (int j = c; j < c + PaperSize; j++) {
							Map[i][j] = 1;
						}
					}
				}
			}
			return;
		}
	}
	
}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			cin >> Map[r][c];
		}
	}

	Recursion(0);

	if (Answer == 2112345678) cout << "-1";
	else cout << Answer;


	return 0;
}

/*
���� �м�

������(5����) : 1��1, 2��2, 3��3, 4��4, 5��5

1. 10x10 ������ ����
2. 0�� 1�� 1�� ��� �����̷� �������
3. ������ ���� ����
	1) ��ġ�� �ȵ�
	2) ���� �� �ȵ�
	3) ĭ�� ���� ��ġ 
	4) 0�� ���� ĭ�� ������ ������ �ȵ�


1. 5x5���� ������ �� ã��
	1) cnt <=5 : �Ѿ
	2) cnt > 5 : Combination(C,5)

	2. 4x4���� ������ �� ã�� 
		1) cnt <=5 : �Ѿ
		2) cnt > 5 : Combination(C,5)

		3. 3x3���� ������ �� ã��
			1) cnt <=5 : �Ѿ
			2) cnt > 5 : Combination(C,5)

			4. 2x2���� ������ �� ã��
				1) cnt <=5 : �Ѿ
				2) cnt > 5 : Combination(C,5)

				5. 1x1���� ������ �� ã��
					1) cnt <=5 : Answer�� ����
					2) cnt > 5 : �׳� Return



*/

/*
TC 5)

(1,1), (1,2), (2,1), (2,2), (2,3), 
(3,2), (3,3), (3,4), (3,5), (3,6),
(4,3), (4,4), (4,5), (4,6)
(5,4), (5,5), (5,6)
(6,2)


*/