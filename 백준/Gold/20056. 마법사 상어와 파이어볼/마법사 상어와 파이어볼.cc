#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;


void input();
void Simulation();
void Simulation2();

struct ball {
	int row;
	int col;
	int mass;
	int speed;
	int dir;
};

struct pos {
	int row;
	int col;
};

int N, M, K;
vector<ball> Map[51][51];
const int dr[8] = { -1,-1,0,1,1,1,0,-1 };
const int dc[8] = { 0,1,1,1,0,-1,-1,-1 };

vector<pos> Exist;



//Main 함수
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	for (int test = 0; test < K; test++) {

		Simulation2();
	}
	int Answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Map[i][j].size() == 0) continue;
			for (int k = 0; k < Map[i][j].size(); k++) {
				Answer += Map[i][j][k].mass;
			}
		}
	}

	cout << Answer;

	return 0;
}

void input() {
	cin >> N >> M >> K;
	int Visited[51][51] = { 0, };
	for (int i = 1; i <= M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		ball temp = { r,c,m,s,d };
		Map[r][c].push_back(temp);
		if (Visited[r][c] == 1) continue;
		Visited[r][c] = 1;
		Exist.push_back({ r,c });
	}
}

//Vector Temp 배열에 복사하는 방법
void Simulation() {

	vector<ball> Temp[51][51];
	//일단 이동시켜서 Temp에 저장


	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (Map[r][c].size() == 0) continue;
			//맵에 파이어볼 있다면
			for (int i = 0; i < Map[r][c].size(); i++) {
				ball now = Map[r][c][i];

				int nextRow = now.row + (now.speed % N) * dr[now.dir];
				if (nextRow > N) nextRow -= N;
				else if (nextRow <= 0) nextRow += N;
				int nextCol = now.col + (now.speed % N) * dc[now.dir];
				if (nextCol > N) nextCol -= N;
				else if (nextCol <= 0) nextCol += N;

				now.row = nextRow;
				now.col = nextCol;
				Temp[nextRow][nextCol].push_back(now);
			}
		}
	}
	//나눠야할 위치 구해놓기
	vector<pair<int, int>> SplitCandi;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (Temp[r][c].size() <= 1) continue;
			SplitCandi.push_back({ r,c });
		}
	}
	// 나눌 곳 없으면 그만
	if (SplitCandi.size() == 0) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				Map[i][j] = Temp[i][j];
			}
		}
		return;
	}

	for (int i = 0; i < SplitCandi.size(); i++) {
		int nowRow = SplitCandi[i].first;
		int nowCol = SplitCandi[i].second;
		int nowCnt = Temp[nowRow][nowCol].size(); //합쳐진 개수

		//1. 질량 : 합쳐진 질량 / 5 (질량 : 0 => 소멸)
		//2. 속력 : 합쳐진 속력의 합 / 합쳐진 볼 개수
		//3. 방향 : 모두 홀/짝(0 2 4 6)  그외 (1 3 5 7)
		ball division[4];
		int mass_sum = 0;  //질량합
		int speed_sum = 0;
		int odd_cnt = 0;
		int even_cnt = 0;

		for (int j = 0; j < nowCnt; j++) {
			ball Now = Temp[nowRow][nowCol][j];
			mass_sum += Now.mass;
			speed_sum += Now.speed;
			if (Now.dir % 2 == 0) even_cnt++;
			else odd_cnt++;
		}

		Temp[nowRow][nowCol].clear();

		//(질량 : 0 = > 소멸)
		if (mass_sum < 5) continue;

		for (int j = 0; j < 4; j++) {
			if (odd_cnt == nowCnt || even_cnt == nowCnt) {
				division[j] = { nowRow,nowCol, mass_sum / 5, speed_sum / nowCnt, j * 2 };
			}
			else {
				division[j] = { nowRow,nowCol, mass_sum / 5, speed_sum / nowCnt, j * 2 + 1 };
			}
		}

		for (int j = 0; j < 4; j++) {
			Temp[nowRow][nowCol].push_back(division[j]);
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Map[i][j] = Temp[i][j];
		}
	}


	int debugging = -1;
}

void Simulation2() {


	vector<ball> Temp;

	//이동시킨 파이어볼 Temp 에 저장
	for (int e = 0; e < Exist.size(); e++) {
		int r = Exist[e].row;
		int c = Exist[e].col;

		for (int i = 0; i < Map[r][c].size(); i++) {
			ball now = Map[r][c][i];
			int nextSpeed = now.speed % N;
			int nextRow = now.row + (nextSpeed)*dr[now.dir];
			if (nextRow > N) nextRow -= N;
			else if (nextRow <= 0) nextRow += N;
			int nextCol = now.col + (nextSpeed)*dc[now.dir];
			if (nextCol > N) nextCol -= N;
			else if (nextCol <= 0) nextCol += N;

			now.row = nextRow;
			now.col = nextCol;
			Temp.push_back(now);
		}
		Map[r][c].clear();
	}


	Exist.clear();

	int Visited[51][51] = { 0, };

	for (int i = 0; i < Temp.size(); i++) {
		ball now = Temp[i];
		Map[now.row][now.col].push_back(now);
		if (Visited[now.row][now.col] == 1) continue;
		Visited[now.row][now.col] = 1;
		Exist.push_back({ now.row, now.col });
	}


	//나눠야할 위치 구해놓기
	vector<pair<int, int>> SplitCandi;

	for (int e = 0; e < Exist.size(); e++) {
		int r = Exist[e].row;
		int c = Exist[e].col;
		if (Map[r][c].size() <= 1) continue;
		SplitCandi.push_back({ r,c });
	}

	// 나눌 곳 없으면 그만
	if (SplitCandi.size() == 0) {
		return;
	}

	for (int i = 0; i < SplitCandi.size(); i++) {
		int nowRow = SplitCandi[i].first;
		int nowCol = SplitCandi[i].second;
		int nowCnt = Map[nowRow][nowCol].size(); //합쳐진 개수

		//1. 질량 : 합쳐진 질량 / 5 (질량 : 0 => 소멸)
		//2. 속력 : 합쳐진 속력의 합 / 합쳐진 볼 개수
		//3. 방향 : 모두 홀/짝(0 2 4 6)  그외 (1 3 5 7)
		int mass_sum = 0;  //질량합
		int speed_sum = 0;
		int odd_cnt = 0;
		int even_cnt = 0;

		for (int j = 0; j < nowCnt; j++) {
			ball Now = Map[nowRow][nowCol][j];
			mass_sum += Now.mass;
			speed_sum += Now.speed;
			if (Now.dir % 2 == 0) even_cnt++;
			else odd_cnt++;
		}

		Map[nowRow][nowCol].clear();

		//(질량 : 0 = > 소멸)
		if (mass_sum < 5) continue;

		int nextMass = mass_sum / 5;
		int nextSpeed = speed_sum / nowCnt;
		for (int j = 0; j < 4; j++) {
			if (odd_cnt == nowCnt || even_cnt == nowCnt) {
				Map[nowRow][nowCol].push_back({ nowRow,nowCol, mass_sum / 5, speed_sum / nowCnt, j * 2 });
			}
			else {
				Map[nowRow][nowCol].push_back({ nowRow,nowCol, mass_sum / 5, speed_sum / nowCnt, j * 2 + 1 });
			}
		}
	}

	int debugging = -1;
}
