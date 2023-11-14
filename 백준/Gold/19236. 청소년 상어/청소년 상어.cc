#include<iostream>
#include<vector>

using namespace std;

//4x4

//물고기 (번호(1~16) , 방향)

//물고기 이동 (상어 배치 다음)
//1) 이동 가능 칸 : 빈칸, 다른 물고기 칸
//2) 이동 불가 칸 : 상어, 범위 밖
//3) 이동방법 : 
	//1. 이동할 수 있는 칸까지 45도 반시계
	//2. 없으면 이동 X
	//3. 다른 물고기 있으면 Swap (방향 유지)


//상어 이동 (물고기 이동 끝난 후)
// 초기 : (0,0) 물고기 먹고 (0,0)에 위치 
// 
//1) 물고기 있는 칸으로 도착한 경우
	//1. 물고기 먹음
	//2. 방향 뺏음

//2) 이동 중 물고기 만나면 무시

//3) 물고기 없는 칸으로 이동 X

//4) 이동 가능한 칸 없으면 귀환

//방향 8개
void input();
void movefish();


struct pos {
	int row;
	int col;
	int dir;
};

const int dr[9] = {0, -1, -1, 0, 1, 1, 1, 0,-1 };
const int dc[9] = {0,  0, -1,-1,-1,0,1,1, 1 };
int Map[4][4] = { 0, };

int Dead[17] = { 0, };
pos Fish[17];
pos Shark;
int Answer = 0;


void DFS(int sum, int depth) {
	//먹을 물고기 다 죽었거나
	//상어 이동할 곳 없으면 끝
	if (depth >= 15) {
		Answer = max(Answer, sum);
		return;
	}
	int sharkDir = Shark.dir;
	int sharkRow = Shark.row;
	int sharkCol = Shark.col;

	movefish();
	int Temp[4][4] = { 0, };

	pos Fish_Temp[17];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Temp[i][j] = Map[i][j];
		}
	}
	for (int i = 1; i <= 16; i++) {
		Fish_Temp[i] = Fish[i];
	}

	vector<pair<int, int>> Candi;  //먹을 후보

	while (1) {
		sharkRow += dr[sharkDir];
		sharkCol += dc[sharkDir];
		
		//3) 물고기 없는 칸으로 이동 X
		if (sharkRow < 0 || sharkCol < 0 || sharkRow >= 4 || sharkCol >= 4) break;
		if (Map[sharkRow][sharkCol] == 0) continue;
		Candi.push_back({ sharkRow, sharkCol });
	}
	//이동 가능한 칸 없으면 귀환
	if (Candi.size() == 0) {
		Answer = max(Answer, sum);
		return;
	}
	sharkRow = Shark.row;
	sharkCol = Shark.col;

	if (Fish[9].row == 0 && Fish[9].col == 1) {
		int debugging = -1;
	}

	for (int i = 0; i < Candi.size(); i++) {

		int nextRow = Candi[i].first;
		int nextCol = Candi[i].second;
		int nextFish = Map[nextRow][nextCol];
		//상어 이동
		Map[sharkRow][sharkCol] = 0;
		Map[nextRow][nextCol] = -1;
		//물고기 먹음
		Dead[nextFish] = 1;
		Shark.row = nextRow; 
		Shark.col = nextCol; 
		Shark.dir = Fish[nextFish].dir;
		
		//재귀 호출 부분
		DFS(sum + nextFish, depth+1);


		Dead[nextFish] = 0;
		
		Shark.row = sharkRow; 
		Shark.col = sharkCol;
		Shark.dir = sharkDir;

		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				Map[j][k] = Temp[j][k];
			}
		}

		for (int j = 1; j <= 16; j++) {
			Fish[j] = Fish_Temp[j];
		}
		int debugging = -1;
	}

}


void solution() {
	int init_Fish = Map[0][0];
	Shark = { Fish[init_Fish].row, Fish[init_Fish].col, Fish[init_Fish].dir };
	Map[0][0] = -1;  //상어 있는 칸 : -1
	Dead[init_Fish] = 1;

	DFS(init_Fish, 0);

	cout << Answer;

}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}



void input() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int a, b;
			cin >> a >> b;
			Fish[a] = { i,j,b };
			Map[i][j] = a;
		}
	}

}

void movefish() {


	for (int i = 1; i <= 16; i++) {
		if (Dead[i] == 1) continue;  //죽은 물고기 무시

		int nowRow = Fish[i].row;
		int nowCol = Fish[i].col;
		int nowDir = Fish[i].dir;

		for (int d = nowDir; d < 8 + nowDir; d++) {
			int nextDir = d;
			if (nextDir > 8) nextDir -= 8;
			int nextRow = nowRow + dr[nextDir];
			int nextCol = nowCol + dc[nextDir];
			//이동 불가 칸 : 상어, 범위 밖
			//2. 없으면 이동 X
			if (nextRow < 0 || nextCol < 0 || nextRow >= 4 || nextCol >= 4) continue;
			if (Map[nextRow][nextCol] == -1) continue;

			else if (Map[nextRow][nextCol] == 0) {  //그냥 빈칸인 경우 이동
					Map[nextRow][nextCol] = i;
					Map[nowRow][nowCol] = 0;
					Fish[i].row = nextRow;
					Fish[i].col = nextCol;
					Fish[i].dir = nextDir;
					break;
			}
			else {    //다른 물고기가 존재하는 경우
				//다른 물고기 있으면 Swap(방향 유지)
				int nextFish = Map[nextRow][nextCol];
				swap(Map[nextRow][nextCol], Map[nowRow][nowCol]);
				Fish[i].row = nextRow;
				Fish[i].col = nextCol;
				Fish[i].dir = nextDir;
				Fish[nextFish].row = nowRow;
				Fish[nextFish].col = nowCol;
				break;
			}
		}
	}

}