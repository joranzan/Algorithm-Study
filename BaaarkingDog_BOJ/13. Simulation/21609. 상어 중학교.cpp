#include<iostream>
#include<queue>

using namespace std;



struct pos {
	int row;
	int col;
	bool operator<(pos next) const {
		if (row < next.row) return true;
		else if (row > next.row) return false;
		else {
			if (col < next.col) return true;
			else return false;
		}
	}
};

struct group {

	int row;
	int col;
	vector<pos> Member;
	int rainbowCnt;
	
	bool operator<(group next) const {
		if (Member.size() < next.Member.size()) return true;
		else if (Member.size() > next.Member.size()) return false;
		else {
			if (rainbowCnt < next.rainbowCnt) return true;
			else if (rainbowCnt > next.rainbowCnt) return false;
			else {
				if (row < next.row) return true;
				else if (row > next.row) return false;
				else {
					if (col < next.col) return true;
					else return false;
				}
			}
		}
	}
};

int Map[21][21] = { 0, };
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
int N, M;
int GlobalVisited[21][21] = { 0, };

group findBlock(int row, int col, int color) {

	group ret;
	int Visited[21][21]={0,};
	queue<pos> q;
	pos Leader = { row,col };
	int rainbowCnt = 0;
	q.push({ row,col });
	Visited[row][col] = 1;
	ret.Member.push_back({ row,col });

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			int nextColor = Map[nextRow][nextCol];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (nextColor <= -1) continue;  //검은색이면 무시
			if (Visited[nextRow][nextCol] == 1) continue;  //이미 찾았으면 무시
			//빈칸이여도 무시 (빈칸 숫자 뭘로할지 정하기)
			//////////////////////////////////////////////////////
			//같은 색깔 아니면 무시
			if (nextColor >= 1 && nextColor <= M) {
				if (nextColor != color) continue;
			}
			Visited[nextRow][nextCol] = 1;
			if (Map[nextRow][nextCol] == 0) rainbowCnt++;
			else {
				pos Now = { nextRow, nextCol };
				GlobalVisited[nextRow][nextCol] = 1;
				if (Now < Leader) Leader = Now;
			}
			q.push({ nextRow, nextCol });
			ret.Member.push_back({ nextRow,nextCol });
		}
	}

	ret.row = Leader.row;
	ret.col = Leader.col;
	ret.rainbowCnt = rainbowCnt;

	return ret;
}


void gravity_rotation() {

	int Temp[21][21];
	//초기화
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Temp[i][j] = -10;
		}
	}
	
	//중력 작용
	for (int c = 1; c <= N; c++) {
		int tempRow = N;
		for (int r = N; r >= 1; r--) {
			if (Map[r][c]<-1 || Map[r][c]>M) continue;
			if (Map[r][c] == -1) {
				Temp[r][c] = -1;
				tempRow = r - 1;
			}
			else {
				Temp[tempRow][c] = Map[r][c];
				tempRow--;
			}
		}
	}


	int Temp2[21][21];

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			Temp2[N + 1 - c][r] = Temp[r][c];
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Map[i][j] = -10;
		}
	}

	for (int c = 1; c <= N; c++) {
		int tempRow = N;
		for (int r = N; r >= 1; r--) {
			if (Temp2[r][c]<-1 || Temp2[r][c]>M) continue;
			if (Temp2[r][c] == -1) {
				Map[r][c] = -1;
				tempRow = r - 1;
			}
			else {
				Map[tempRow][c] = Temp2[r][c];
				tempRow--;
			}
		}
	}

	int debugging = -1;

}

void input() {

	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}
}

void solution() {

	int score = 0;

	while (1) {

		bool allDone = true;
		group Biggest;
		Biggest.row = -1;
		Biggest.col = -1;
		Biggest.rainbowCnt = -1;
		
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				
				int color = Map[i][j];
				if (GlobalVisited[i][j] == 1) continue;
				if (color >= 1 && color <= M) {
					GlobalVisited[i][j] = 1;
					group Next = findBlock(i, j, color);
					if (Next.Member.size() <= 1) continue;
					allDone = false;
					if (Biggest < Next) Biggest = Next;
				}
			}
		}

		if (allDone) {
			cout << score;
			break;
		}
		

		//찾은 블록은 모두 제거 + 점수 획득 (블록 수 제곱)
		int blockCnt = Biggest.Member.size();
		score += (blockCnt * blockCnt);
		for (int i = 0; i < blockCnt; i++) {
			int nowRow = Biggest.Member[i].row;
			int nowCol = Biggest.Member[i].col;
			Map[nowRow][nowCol] = -10;   //제거하면 빈칸 : -10
		}

		gravity_rotation();

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				GlobalVisited[i][j] = 0;
			}
		}

	}

}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();


	return 0;
}

//문제분석
//NxN 맵
//블록 : 검은색(-1), 무지개(0), 일반(M이하의 자연수)
//인접 : 상하좌우

//그룹 조건 (블록 2개이상) 
//1) 일반블록 적어도 1개(모두 색 같아야함)
//2) 검은 블록 포함 X
//3) 무지개 마음대로 있어도 됨
//4) 상하좌우로 모두 연결되어야함
//5) 기준 블록 : 무지개 블록 x (행 작음 -> 열 작음)


//목표 : 가장 큰 그룹 찾기
//1. 무지개 블록 수 가장 많은 그룹
//2. 기준 블록의 행 큼
//3. 기준 블록의 열 큼

//찾은 블록은 모두 제거 + 점수 획득 (블록 수 제곱)

//격자에 중력 작용 -> 90도 방향 반시계 회전 -> 다시 중력 작용

//중력 작용
//1. 검은색 블록 외에 모든 블록이 밑으로 이동(행큰곳으로) 