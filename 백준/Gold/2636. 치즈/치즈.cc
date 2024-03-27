#include<iostream>
#include<queue>

using namespace std;


struct pos {
	int row;
	int col;
};

int Board[101][101] = { 0, };
int N, M;
int Time = 0;
int leftover = 0;
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
vector<pos> Candidate;


void init() {

	cin >> N >> M;
	Time = 0;

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> Board[r][c];
			if (Board[r][c] == 1) leftover++;
		}
	}
}

void findAir() {
	queue<pos> q;
	int Visited[101][101] = { 0, };
	q.push({ 0,0 });
	Visited[0][0] = 1;

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		bool cheeseExist = false;
		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M) continue;
			if (Visited[nextRow][nextCol] == 1) continue;
			Visited[nextRow][nextCol] = 1;
			if (Board[nextRow][nextCol] == 1) {
				Candidate.push_back({ nextRow, nextCol });
			}
			else if (Board[nextRow][nextCol] == 0) {
				
				q.push({ nextRow, nextCol });
			}
		}
	}
	int debugging = -1;
}

void melt() {

	int tempBoard[101][101] = { 0, };
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (Board[r][c] == 1) leftover++;
			tempBoard[r][c] = Board[r][c];
		}
	}



	
}

void solution() {


	while (1) {
		
		Candidate.clear();
		findAir();

		//녹는 과정
		for (int i = 0; i < Candidate.size(); i++) {
			Board[Candidate[i].row][Candidate[i].col] = 0;
		}
		
		Time++;

		bool allDone = true;

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (Board[r][c] == 1) {
					allDone = false;
					break;
				}
			}
			if (!allDone)  break;
		}


		if (allDone) {
			cout << Time << "\n" << leftover;
			break;
		}

		leftover -= Candidate.size();
	}
	

}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);


	init();
	solution();


	return 0;
}

/*
문제 분석

치즈 : (회색 표시)
판의 가장자리 : X

- 치즈에는 구멍이 있을 수 있음
- 공기와 접촉된 칸 : 1시간 뒤 없어짐

최대 100x100

*/