#include<iostream>

using namespace std;

int N;
bool ColVisited[15] = { false, }; //�ش� ���� �̹� ���� �ִ��� Check
bool LeftDiagVisited[35] = { false, }; //���� Check
bool RightDiagVisited[35] = { false, }; //���� Check
int cnt = 0;

void BackTracking(int nowRow) {  

	if (nowRow >= N) {
		cnt++;
		return;
	}

	for (int i = 0; i < N; i++) {  //�ش� nowRow�� ���� �� �ִ� �ڸ� �� Ž��

		int nextRow = nowRow; //���ʿ� 0��° Row���� ����
		int nextCol = i;
		int leftDiag = nextRow + nextCol;
		int rightDiag = N - 1 - (nextRow - nextCol);
		//������ Map ��� �� ����
		if (ColVisited[i]) continue; //Col check
		if (LeftDiagVisited[leftDiag]) continue; //���� Check
		if (RightDiagVisited[rightDiag]) continue; //���� Check
		//�� ����� ���Ŵ�
		ColVisited[i] = true;
		LeftDiagVisited[leftDiag] = true;
		RightDiagVisited[rightDiag] = true;
		//�� ����!
		BackTracking(nowRow + 1);
		//�ٽ� ���󺹱�
		ColVisited[i] = false;
		LeftDiagVisited[leftDiag] = false;
		RightDiagVisited[rightDiag] = false;

	}

}

int main() {

	cin >> N;

	BackTracking(0);

	cout << cnt;

	return 0;
}

//����

//row�� �� �ϳ��ۿ� ������ -> �� row�� �˻��� ������

//BackTracking(int nowRow, int nowCol, )
//if(nowRow>=N) -> ������ row���� �� ������ 
//cnt++ , return 

//�밢�� ���� ���� ���
// ����
// row + col
// ����
// row - col   4 3 2 1 0 -1 -2 -3 -4  -> N-1 -(row-col) 0 1 2 3 4 5 6 7 8
//�Ʒ� ���  
// col check