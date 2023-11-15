#include<iostream>
#include<vector>

using namespace std;

//NxN Map
//M개의 칸에 존재

//상어 정보
//1. 1~M 번호
//2. 1번 상어 가장 강함


//상어 이동
//1. 자신의 냄새를 해당 위치에 뿌림
//2. 1초마다 상하좌우 이동
//	//1) 아무 냄새 없는 칸의 방향
	//2) 없다면 자신의 냄새가 있는 칸의 방향으로 (상어마다 우선순위 다름)
	//3) 상어 방향 : 초기값 주어짐 -> 이동 시 이동한 방향
//3. 이동 후 냄새 다시 뿌림
//4. K번 이동 후 냄새 사라짐
// 
//모든 상어 이동 후
	//4) 한칸에 여러마리 상어 : 번호 작은애 빼고 전멸 

//상하좌우
const int DR[5] = { 0,-1,1,0,0 };
const int DC[5] = { 0,0,0,-1,1 };

struct shark {
	int row;
	int col;
	int id;
	int nowDir;
	int dirInfo[5][5] = { 0, };   //방향번호 정보
	int dr[5][5] = { 0, };     
	int dc[5][5] = { 0, };
	bool dead = false; //상어가 쫓겨났는지 여부 판별
};

struct smell {
	int id;
	int value;
};

int N, M, K;
int SharkPos[21][21] = { 0, };   //상어의 위치 저장
int SharkDead[401] = { 0, };    //상어가 쫓겨났는지 여부 판별
smell Scent[21][21] = { 0, }; //상어 냄새 저장
shark SharkInfo[401];

void input();
void Scent_Simulation();
void Shark_Simulation();


void solution() {

	int time = 0;

	while (1) {

		time++;
		Scent_Simulation();
		Shark_Simulation();

		//1번만 남았는지 체크하는 부분
		bool flag = true;
		for (int i = 2; i <= M; i++) {
			if (!SharkInfo[i].dead) {
				flag = false;
				break;
			}
		}

		if (flag) {
			cout << time;
			break;
		}
		if (time >= 1000) {
			cout << "-1";
			break;
		}
	}
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

void input() {
	cin >> N >> M >> K;
	//맵
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> SharkPos[i][j];
			if (SharkPos[i][j] != 0) {
				SharkInfo[SharkPos[i][j]].row = i;
				SharkInfo[SharkPos[i][j]].col = j;
				SharkInfo[SharkPos[i][j]].id = SharkPos[i][j];
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		int d;
		cin >> d;
		SharkInfo[i].nowDir = d;
	}

	for (int i = 1; i <= M; i++) {
		for (int dir = 1; dir <= 4; dir++) {
			for (int j = 1; j <= 4; j++) {
				int d;
				cin >> d;
				SharkInfo[i].dirInfo[dir][j] = d;
				SharkInfo[i].dr[dir][j] = DR[d];
				SharkInfo[i].dc[dir][j] = DC[d];
			}

		}
	}
}

void Scent_Simulation() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Scent[i][j].value == 0) continue;
			Scent[i][j].value --;
		}
	}

	for (int i = 1; i <= M; i++) {
		if (SharkInfo[i].dead) continue;
		//K 감소 시킬때 상어 있는 위치 빼고 감소
		Scent[SharkInfo[i].row][SharkInfo[i].col].id = i;
		Scent[SharkInfo[i].row][SharkInfo[i].col].value = K;
	}
}

void Shark_Simulation() {

	//기존에 있던 상어 처리 때문에
	int SharkTemp[21][21] = { 0, };

	for (int i = 1; i <= M; i++) {
		if (SharkInfo[i].dead) continue;
		// i : 상어 번호
		//i번 상어 이동

		int nowRow = SharkInfo[i].row;
		int nowCol = SharkInfo[i].col;
		int nowDir = SharkInfo[i].nowDir;

		//인접한 칸에 아무 냄새 없는지 확인
		bool allDone = false;
		for (int dir = 1; dir <= 4; dir++) {
			int nextRow = nowRow + SharkInfo[i].dr[nowDir][dir];
			int nextCol = nowCol + SharkInfo[i].dc[nowDir][dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Scent[nextRow][nextCol].value != 0) continue;
			allDone = true;
			SharkPos[nowRow][nowCol] = 0;
			if (SharkTemp[nextRow][nextCol] != 0) {
				if (SharkTemp[nextRow][nextCol] > i) SharkTemp[nextRow][nextCol] = i;
				else {
					SharkInfo[i].dead = true;
					break;
				}
			}
			SharkTemp[nextRow][nextCol] = i;
			SharkInfo[i].row = nextRow;
			SharkInfo[i].col = nextCol;
			SharkInfo[i].nowDir = SharkInfo[i].dirInfo[nowDir][dir];
			break;
		}

		if (allDone) continue;

		//없다면 자신의 냄새가 있는 칸의 방향으로(상어마다 우선순위 다름)

		for (int dir = 1; dir <= 4; dir++) {
			int nextRow = nowRow + SharkInfo[i].dr[nowDir][dir];
			int nextCol = nowCol + SharkInfo[i].dc[nowDir][dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Scent[nextRow][nextCol].id != i && Scent[nextRow][nextCol].value != 0) continue;
			allDone = true;

			SharkTemp[nowRow][nowCol] = 0;
			SharkTemp[nextRow][nextCol] = i;
			SharkInfo[i].row = nextRow;
			SharkInfo[i].col = nextCol;
			SharkInfo[i].nowDir = SharkInfo[i].dirInfo[nowDir][dir];
			break;
		}
	}

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			SharkPos[r][c] = SharkTemp[r][c];
		}
	}
}