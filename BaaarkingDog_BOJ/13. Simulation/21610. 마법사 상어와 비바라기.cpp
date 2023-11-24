#include<iostream>
#include<vector>

using namespace std;

//문제 분석


//NxN 맵 (물의 양 -> 제한 없음) (1,1)
//1과 N 연결

//비바라기 시전
//1) 비구름 :  (N, 1), (N, 2), (N-1, 1), (N-1, 2)


//M번 명령
// d(방향) s(거리)
//1) 모든 구름이 d 방향으로 s칸  이동
//2) 각 구름에 비가 내려 구림 있는 칸 물의 양 += 1
//3) 구름이 모두 사라짐
//4) 물복사 버그 (대상 : 2번에서 증가한 애들)
	//1. 대각선 방향으로 거리 1인 칸 중 물이 있는 칸 수 만큼 ++
//5) 2이상인 모든 칸에 구름 다시 생김
//6) 구름 생긴 칸에 물 -=2 (3번에서 구름칸 무시)

struct query {
	int d;
	int s;
};

struct pos {
	int row;
	int col;
};


int N, M;
int Map[51][51] = { 0, };
query Query[101];
int Cloud[51][51] = { 0, };
vector<pos> CloudPos;

void moveCloud(int d, int s) {
	const int dr[9] = {0, 0,-1,-1,-1,0,1,1,1 };
	const int dc[9] = {0, -1,-1,0,1,1,1,0,-1 };

	vector<pos> temp;

	int moveCnt = s % N;

	for (int i = 0; i < CloudPos.size(); i++) {
		int nowRow = CloudPos[i].row;
		int nowCol = CloudPos[i].col;

		Cloud[nowRow][nowCol] = 0;

		int nextRow = nowRow + dr[d] * moveCnt;
		int nextCol = nowCol + dc[d] * moveCnt;
		if (nextRow > N) nextRow -= N;
		else if (nextRow <= 0) nextRow += N;
		if (nextCol > N) nextCol -= N;
		else if (nextCol <= 0) nextCol += N;

		temp.push_back({ nextRow,nextCol });
	}

	CloudPos.clear();

	for (int i = 0; i < temp.size(); i++) {
		CloudPos.push_back(temp[i]);
		//구름이 있던 자리 기록
		Cloud[temp[i].row][temp[i].col] = 1;
		//2) 각 구름에 비가 내려 구림 있는 칸 물의 양 += 1
		Map[temp[i].row][temp[i].col] += 1;
	}

	int debugging =  -1;
}
void copyWater() {
	const int dr[4] = { -1,-1,1,1 };
	const int dc[4] = { -1,1,-1,1 };

	for (int i = 0; i < CloudPos.size(); i++) {
		int nowRow = CloudPos[i].row;
		int nowCol = CloudPos[i].col;
		int nowCnt = 0;
		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Map[nextRow][nextCol] > 0) nowCnt++;
		}
		Map[nowRow][nowCol] += nowCnt;
	}

}
void makeCloud() {

	vector<pos> Next;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (Map[r][c] <= 1) continue;
			if (Cloud[r][c] == 1) continue;
			Next.push_back({ r,c });
			Map[r][c] -= 2;
		}
	}

	for (int i = 0; i < CloudPos.size(); i++) {
		if (Cloud[CloudPos[i].row][CloudPos[i].col] != 1) {
			int debugging = -1;
		}
		Cloud[CloudPos[i].row][CloudPos[i].col] = 0;
	}

	CloudPos.clear();

	for (int i = 0; i < Next.size(); i++) {
		CloudPos.push_back(Next[i]);
	}

}

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}
	for (int i = 1; i <= M; i++) {
		int d, s;
		cin >> d >> s;
		Query[i] = { d,s };
	}

	CloudPos.push_back({ N,1 });
	CloudPos.push_back({ N,2 });
	CloudPos.push_back({ N - 1,1 });
	CloudPos.push_back({ N - 1,2 });
	Cloud[N][1] = 1;
	Cloud[N][2] = 1;
	Cloud[N - 1][1] = 1;
	Cloud[N - 1][2] = 1;
	
}

void solution() {

	for (int q = 1; q <= M; q++) {
		
		//구름이 없어도 되는구나
		//이동할 수 있는 구름이 없는 경우
		moveCloud(Query[q].d, Query[q].s);
		copyWater();
		makeCloud();
	}

	int Answer = 0;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			Answer += Map[r][c];
			
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