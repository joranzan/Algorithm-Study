#include<iostream>

using namespace std;

//문제분석
//로봇 청소기, 방의 상태 -> 청소하는 영역의 개수

//NxM 벽 or 빈칸
//동(우1)서(좌3)남(하2)북(상0) 




//청소 원리
//현재 칸 청소 x -> 청소

//상하좌우 청소 안된 빈칸 없는 경우
//바라보는 방향 유지 + 한칸 후진 후 1번 돌아감
//후진 못하면 작동 exit

//상하좌우 빈칸 있는 경우
//반시계방향 90도 회전
//바라보는 방향 기준으로 앞쪽 칸 청소 되지않은칸 -> 전진
//1번 돌아감

int N, M;
int nowRow, nowCol;
int nowDir;
int Map[50][50] = { 0, };
int Answer = 0;

int Rotation(int dir) {

	//상 우 하 좌   0 1 2 3
	if (dir == 0) {
		return 3;
	}
	else if (dir == 1) {
		return 0;
	}
	else if (dir == 2) {
		return 1;
	}
	else if (dir == 3) {
		return 2;
	}
}

void Simulation() {

	const int dr[4] = { -1,0,1,0 };
	const int dc[4] = { 0,1,0,-1 };

	while (1) {

		if (Map[nowRow][nowCol] == 0) {
			Answer++;
			Map[nowRow][nowCol] = -1;  //청소 완료
		}

		bool exist = false; //청소 안된 곳 있는지 여부
		for (int dir = 0; dir < 4; dir++) {
			int next_r = nowRow + dr[dir];
			int next_c = nowCol + dc[dir];
			if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= M) continue;
			if (Map[next_r][next_c] == 0) {
				exist = true;
			}
		}
		if (exist) {
			int tempDir = Rotation(nowDir);
			int next_r = nowRow + dr[tempDir];
			int next_c = nowCol + dc[tempDir];
			nowDir = tempDir;
			if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= M) continue;
			if (Map[next_r][next_c] == 0) {
				nowRow = next_r;
				nowCol = next_c;
			}
			
		}
		else if (!exist) {

			int tempDir = (nowDir + 2) % 4;
			int next_r = nowRow + dr[tempDir];
			int next_c = nowCol + dc[tempDir];

			if (Map[next_r][next_c] == 1) {
				break;
			}
			else {
				nowRow = next_r;
				nowCol = next_c;
			}

		}
	}
}

void solution() {

	Simulation();
	cout << Answer<<"\n";
}

void input() {

	cin >> N >> M;

	cin >> nowRow >> nowCol >> nowDir;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
		}
	}
}

int main() {


	input();
	solution();

	return 0;
}

//1 1 1 1 1 1 1 1 1 1
//1 0 0 0 0 0 0 0 0 1
//1 0 0 0 1 1 1 1 0 1
//1 0 0 1 1 0 0 0 0 1
//1 0 1 1 0 0 0 0 0 1
//1 0 0 0 0 0 0 0 0 1
//1 0 0 0 0 0 0 1 0 1
//1 0 0 0 -1 1 1 0 1
//1 0 0 0 0 0 1 1 0 1
//1 0 0 0 0 0 0 0 0 1
//1 1 1 1 1 1 1 1 1 1