#include<iostream>

using namespace std;

//문제 분석
// 
//상하좌우 방향 이동 가능

//같은 값을 갖는 블록 : 합쳐짐
//한번의 이동에서 이미 합쳐진 애들은 : 다시 못합침


int N;
int Map[20][20] = { 0, };
int Answer = 0;

//돌리기
void rotation() {

	int temp[20][20] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp[j][N - 1 - i] = Map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Map[i][j] = temp[i][j];
		}
	}

}

void action() {

	for (int col = 0; col < N; col++) {

		int top = 0;
		int bottom = 1;
		while (top <= bottom && bottom < N) {

			if (top == bottom) bottom++;
			else if (Map[bottom][col] == 0) bottom++;
			else if (Map[top][col] == 0) top++;
			else if (Map[top][col] == Map[bottom][col]) {
				Map[top][col] *= 2;
				Map[bottom][col] = 0;
				top++;
				bottom++;
			}
			else {
				top++;
				bottom++;
			}
		}
		//int bug = -1;
		int temp[20] = { 0 };
		int temp_idx = 0;
		for (int row = 0; row < N; row++) {
			if (Map[row][col] == 0) continue;
			temp[temp_idx] = Map[row][col];
			temp_idx++;
		}
		for (int row = 0; row < N; row++) {
			Map[row][col] = temp[row];
		}

	}
	int de = -1;

}

void DFS(int depth) {
	if (depth >= 5) {

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				Answer = max(Answer, Map[i][j]);
			}
		}
		return;
	}

	
	for (int i = 0; i < 4; i++) {

		int temp[20][20] = { 0, };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				temp[i][j] = Map[i][j];
			}
		}

		action();
		DFS(depth + 1);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				Map[i][j] = temp[i][j];
			}
		}
		if (i == 3) continue;
		rotation();
	}

	

}


void solution() {

	DFS(0);
	cout << Answer;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
		}
	}
	//action();
	solution();

	return 0;
}