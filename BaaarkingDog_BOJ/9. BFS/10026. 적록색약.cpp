#include<iostream>
#include<queue>

using namespace std;

//문제 분석
//N x N 그리드
//R G B

//적록색약 아닌 사람 RGB 구분
//적록색약 : RG / B 구분

int N;
char Map[100][100];
int Visited[100][100];
int DAT[4] = { 0 };   //1: R   2: G  3: B
int DAT_Weak[3] = { 0 };  // 1: RG  2: B

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			Visited[i][j] = 0;
		}
	}
}

void BFS(int row, int col, char c) {
	queue<pair<int, int>> q;
	q.push({ row,col });

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	while (!q.empty()) {

		int now_r = q.front().first;
		int now_c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= N) continue;
			if (Map[next_r][next_c] != c) continue;
			if (Visited[next_r][next_c] != 0) continue;
			Visited[next_r][next_c] = 1;
			q.push({ next_r, next_c });
		}
	}

}

void solution() {


	//정상인인 경우
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			if (Visited[i][j] != 0) continue;
			if (Map[i][j] == 'R') {
				DAT[1]++;
			}
			else if (Map[i][j] == 'G') {
				DAT[2]++;
			}
			else if (Map[i][j] == 'B') {
				DAT[3]++;
			}
			Visited[i][j] = 1;
			BFS(i, j, Map[i][j]);
		}
	}

	//Visited 초기화, R과 G 통합
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Visited[i][j] = 0;
			if (Map[i][j] == 'G') {
				Map[i][j] = 'R';
			}
		}
	}

	//적록색약인 경우
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			if (Visited[i][j] != 0) continue;
			if (Map[i][j] == 'R') {
				DAT_Weak[1]++;
			}
			else if (Map[i][j] == 'B') {
				DAT_Weak[2]++;
			}
			Visited[i][j] = 1;
			BFS(i, j, Map[i][j]);
		}
	}

	cout << DAT[1] + DAT[2] + DAT[3] << " ";
	cout << DAT_Weak[1] + DAT_Weak[2];
}

int main() {
	input();
	solution();
}


//RGB DAT 만들기
//BFS
// R일때 R 그룹 찾기
// G일때 G 그룹 찾기
// B일때 B 그룹 찾기

//Visited 배열