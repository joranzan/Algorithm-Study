#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;


struct pos {
	int row;
	int col;
};


int Map[101][101] = { 0, };
int Visited[101][101] = { 0, };
int N;
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

vector<queue<pos>> Candi;

int Answer = 1000;

void findBoundary(int startRow, int startCol, int groupNum) {

	queue<pos> q;
	queue<pos> nextQ;

	q.push({ startRow, startCol });
	Visited[startRow][startCol] = 1;
	Map[startRow][startCol] = groupNum;

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Visited[nextRow][nextCol] == 1) continue;
			//만약 섬의 가장자리라면
			if (Map[nextRow][nextCol] == 0) {
				Visited[nextRow][nextCol] = 1;
				nextQ.push({ nextRow, nextCol });
			}
			else {
				Visited[nextRow][nextCol] = 1;
				Map[nextRow][nextCol] = groupNum;
				q.push({ nextRow,nextCol });
			}
		}
	}

	Candi.push_back(nextQ);
}




int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}

	//0번 인덱스 dummyData로 채워넣음
	queue<pos> dummyData;
	Candi.push_back(dummyData);

	int num = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Map[i][j] == 0) continue;
			if (Visited[i][j] == 1) continue;
			findBoundary(i, j, num);
			num++;
		}
	}

	for (int i = 1; i < Candi.size(); i++) {
		//i : 시작 섬
		int Distance[101][101] = { 0, };
		queue<pos> q;

		while (!Candi[i].empty()) {
			pos p = Candi[i].front();
			Candi[i].pop();
			Distance[p.row][p.col] = 1;

			q.push(p);
		}

		while (!q.empty()) {

			int nowRow = q.front().row;
			int nowCol = q.front().col;
			q.pop();

			
			if (Distance[nowRow][nowCol] > Answer) continue;

			if (Map[nowRow][nowCol] != 0 && Map[nowRow][nowCol] != i) {
				Answer = min(Answer, Distance[nowRow][nowCol] - 1);
				break;
			}

			for (int dir = 0; dir < 4; dir++) {
				int nextRow = nowRow + dr[dir];
				int nextCol = nowCol + dc[dir];
				if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
				if (Distance[nextRow][nextCol]) continue;
				if (Map[nextRow][nextCol] == i) continue;
				Distance[nextRow][nextCol] = Distance[nowRow][nowCol] + 1;
				q.push({ nextRow, nextCol });
			}
		}
	}


	int debugging = -1;

	cout << Answer;

	return 0;
}


/*

여러 섬 (섬 개수 모름 ;;)

//1. 각 섬의 경계선 점들 구하기


//2. 각 섬에서 0이 아닌 값 && 자기 섬 X 만나면 Answer 갱신





*/