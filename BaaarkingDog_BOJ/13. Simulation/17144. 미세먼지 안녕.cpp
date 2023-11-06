#include<iostream>
#include<vector>

using namespace std;

//맵 : R x C (1,1)  내용 : 미세먼지 양 
//공기청정기 시작 : 1열
//크기 : 2행

//1. 미세먼지 확산
	//1) 상하좌우
	//2) 공기청청기 or 범위 밖 -> 확산 X
	//3) 확산 양 : A[r][c]/5
	//4) Ar,c - (Ar,c/5)×(확산된 방향의 개수) 

//2. 공기청정기 작동
	//1) 윗쪽 공기 청정기 : 반시계 방향
	//2) 아랫쪽 공기 청정기 : 시계 방향
	//3) 미세먼지가 바람의 방향으로 한칸 이동
	//4) 공기청정기로 들어간 미세먼지는 정화됨 (없어짐)

struct pos {
	int row;
	int col;
};

int R, C, T;
int Map[51][51] = { 0, };
pos Device[2];

void Diffusion() {

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	int tempMap[51][51] = { 0, };
	vector<pos> v;  //미세먼지들 위치
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			if (Map[r][c] > 0) {
				v.push_back({ r,c });
				tempMap[r][c] = Map[r][c];
			}
		}
	}

	for (int i = 0; i < v.size(); i++) {

		int nowRow = v[i].row;
		int nowCol = v[i].col;
		int nowNum = Map[nowRow][nowCol];
		int cnt = 0;

		for (int dir = 0; dir < 4; dir++) {
			int next_r = nowRow + dr[dir];
			int next_c = nowCol + dc[dir];
			if (next_r <= 0 || next_c <= 0 || next_r > R || next_c > C) continue;
			if (Map[next_r][next_c] == -1) continue;
			cnt++;
			tempMap[next_r][next_c] += (nowNum / 5);
		}
		tempMap[nowRow][nowCol] -= cnt * (nowNum / 5);
	}

	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			if (Map[r][c] == -1) continue;
			Map[r][c] = tempMap[r][c];
		}
	}

}

void WindTop() {

	int FresherRow = Device[0].row;
	int FresherCol = Device[0].col;

	int startRow = FresherRow;
	int startCol = FresherCol + 1;

	int temp = Map[startRow][startCol];
	Map[startRow][startCol] = 0;
	const int dr[4] = { 0,-1,0,1 };
	const int dc[4] = { 1,0,-1,0 };

	//방향 : 3 0 2 1
	int dir = 0;

	while (1) {
		if (Map[startRow][startCol] == -1) break;
		int next_r = startRow + dr[dir];
		int next_c = startCol + dc[dir];
		if (next_r <= 0 || next_c <= 0 || next_r > R || next_c > C) {
			dir++;
			next_r = startRow + dr[dir];
			next_c = startCol + dc[dir];
		}
		int temp_2 = 0;
		temp_2 = Map[next_r][next_c];
		if (temp_2 == -1) break;
		Map[next_r][next_c] = temp;
		temp = temp_2;
		startRow = next_r;
		startCol = next_c;

	}
}

void WindBottom() {
	int FresherRow = Device[1].row;
	int FresherCol = Device[1].col;

	int startRow = FresherRow;
	int startCol = FresherCol + 1;
	//방향 : 3 1 2 0
	int temp = Map[startRow][startCol];
	Map[startRow][startCol] = 0;

	const int dr[4] = { 0,1,0,-1 };
	const int dc[4] = { 1,0,-1,0 };

	//방향 : 3 0 2 1
	int dir = 0;

	while (1) {
		if (Map[startRow][startCol] == -1) break;
		int next_r = startRow + dr[dir];
		int next_c = startCol + dc[dir];
		if (next_r <= 0 || next_c <= 0 || next_r > R || next_c > C) {
			dir++;
			next_r = startRow + dr[dir];
			next_c = startCol + dc[dir];
		}
		int temp_2 = 0;
		temp_2 = Map[next_r][next_c];
		if (temp_2 == -1) break;
		Map[next_r][next_c] = temp;
		temp = temp_2;
		startRow = next_r;
		startCol = next_c;

	}


}

void input() {
	cin >> R >> C >> T;

	int num = 0;
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			cin >> Map[r][c];
			if (Map[r][c] == -1) {
				Device[num].row = r;
				Device[num].col = c;
				num++;
			}
		}
	}
}

void solution() {




	for (int time = 0; time < T; time++) {
		Diffusion();
		WindTop();
		WindBottom();
		int debugging = -1;
	}
	int Answer = 0;

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (Map[i][j] <= 0) continue;
			Answer += Map[i][j];
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

//미세먼지 이동 시 한번에 이동
//-> Map의 값 바로 바꾸면 안됨
