#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

//문제 분석

//NxN 맵 (1,1)
//학생 : N^2 (1번부터)

//상하좌우 인접

//정해진 순서대로 학생의 자리를 정함

//1. 비어있는 칸 중에서 좋아하는 학생이 가장많은 칸에 자리 정함
//2. 동률 : 인접칸 비어있는 칸이 가장 많은 칸으로 
//3. 동률 : 행의번호 가장 작은 칸
//4. 동률 : 열의 번호가 가장 작은 칸

void input();

struct seat {
	int friendCnt = 0;
	int emptyCnt = 0;
	int row;
	int col;

	bool operator<(seat next) const {
		if (friendCnt < next.friendCnt) return true;
		else if (friendCnt > next.friendCnt) return false;
		else {
			if (emptyCnt < next.emptyCnt) return true;
			else if (emptyCnt > next.emptyCnt) return false;
			else {
				if (row < next.row) return false;
				else if (row > next.row) return true;
				else {
					if (col < next.col) return false;
					else if (col > next.col) return true;
					else return false;

				}
			}
		}
	}
};

struct student {
	int id;
	int DAT[401] = { 0, };
};

int N;
int Map[21][21] = { 0, };
student Student[401];
int Order[401];
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
int Score[5] = { 0,1,10,100,1000 };

void chooseSeat(int id) {

	student now = Student[id];
	priority_queue<seat> pq;

	if (id == 9) {
		int debugging = -1;
	}

	seat Candi = { 0,0,N,N };

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Map[i][j] != 0) continue;
			
			int nowRow = i;
			int nowCol = j;
			int fcnt = 0;
			int ecnt = 0;
			for (int dir = 0; dir < 4; dir++) {
				int nextRow = nowRow + dr[dir];
				int nextCol = nowCol + dc[dir];
				if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
				if (Map[nextRow][nextCol] == 0) ecnt++;
				else if (Student[id].DAT[Map[nextRow][nextCol]] == 1) fcnt++;
			}
			//pq.push({ fcnt,ecnt,nowRow, nowCol });
			seat Now = { fcnt,ecnt,nowRow,nowCol };
			if (Candi < Now) Candi = Now;
		}
	}
	Map[Candi.row][Candi.col] = id;
	//Map[pq.top().row][pq.top().col] = id;

}



void solution() {

	int Answer = 0;

	for (int i = 1; i <= N * N; i++) {
		chooseSeat(Order[i]);
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			int cnt = 0;

			if (Map[i][j] == 0) {
				int debugging = -1;
			}
			int nowID = Map[i][j];
			for (int dir = 0; dir < 4; dir++) {
				int nextRow = i + dr[dir];
				int nextCol = j + dc[dir];
				if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
				if (Student[nowID].DAT[Map[nextRow][nextCol]] == 1) cnt++;
			}

			Answer += Score[cnt];
		}
	}
	cout << Answer;
}

int main() {
	
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

void input() {

	cin >> N;

	for (int i = 1; i <= N * N; i++) {

		int id, f1, f2, f3, f4;
		cin >> id >> f1 >> f2 >> f3 >> f4;

		Order[i] = id;

		Student[id].id = id;
		Student[id].DAT[f1] = 1;
		Student[id].DAT[f2] = 1;
		Student[id].DAT[f3] = 1;
		Student[id].DAT[f4] = 1;
	}

}