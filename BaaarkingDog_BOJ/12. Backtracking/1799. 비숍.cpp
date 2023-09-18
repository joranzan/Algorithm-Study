#include<iostream>

using namespace std;


//ù��° �밢���� ���� �� �ִ� ��� ��ġ 
//�ش� �ݴ���� �밢���� �̹� ������ ����

// �»���� �밢��
// 0 1 2 3 4 5 6 7 8 

//���Ͽ�� �밢��
// 0 1 2 3 4 5 6 7 8

int N;
int Map[10][10] = { 0, };
int Answer = 0;
int rightdownDiag[20] = { 0 };
int leftdownDiag[20] = { 0 };

void BackTracking(int diagNum, int cnt) {

	if (diagNum > 2 * (N - 1)) {
		Answer = max(Answer, cnt);
		return;
	}
	//diagnum=2�϶� diagnum
	bool nowhere = true;
	for (int i = 0; i <= diagNum; i++) {
		int nextRow = i;
		int nextCol = diagNum - i;
		if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) continue;
		if (Map[nextRow][nextCol] == 0) continue;
		if (leftdownDiag[N - 1 - (nextRow - nextCol)] != 0) continue;
		leftdownDiag[N - 1 - (nextRow - nextCol)] += 1;
		rightdownDiag[diagNum] += 1;
		nowhere = false;
		BackTracking(diagNum + 1, cnt + 1);
		leftdownDiag[N - 1 - (nextRow - nextCol)] -= 1;
		rightdownDiag[diagNum] -= 1;
	}
	if (nowhere) BackTracking(diagNum + 1, cnt);

	Answer = max(Answer, cnt);

}

int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
		}
	}

	for (int i = 0; i < 2 * (N - 1); i++) {
		BackTracking(i, 0);
	}

	cout << Answer;

	return 0;
}