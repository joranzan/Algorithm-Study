#include<iostream>
#include<map>
#include<vector>

using namespace std;

//문제 분석

//돌릴 수 있는 면 : 6개

//한 면당 90도 양방향
// h r c
//윗 : 흰(W)  (h==0)
//아래 : 노란색 (Y)  (h==2)
//앞 : 빨 (R)    (c===2)
//뒷면 : 주황 (O) (c==0)
//왼 : 초록 (G)  (r==0)
//오 : 파랑 (B)  (r==2)


vector<pair<int,char>> Cube[3][3][3];
int T;

//윗면일 때 시계방향 매핑
const int Mapping[6][2][6] = {
	{
	{ 0,1,4,5,3,2 }, //U C
	{0,1,5,4,2,3}  //U CW
	},
	{
	{0,1,5,4,2,3}, //D C
	{0,1,4,5,3,2}  //D CW
	},
	{
	{5,4,2,3,0,1}, //F C
	{4,5,2,3,1,0}  //F CW
	},
	{
	{4,5,2,3,1,0}, //B C
	{5,4,2,3,0,1}  //B CW
	},
	{
	{2,3,1,0,4,5}, //L C
	{3,2,0,1,4,5}, //L CW
	},
	{
	{3,2,0,1,4,5}, //R C
	{2,3,1,0,4,5}, //R CW
	}
};


// h r c
//윗 : 흰(W)  (h==0)
//아래 : 노란색 (Y)  (h==2)
//앞 : 빨 (R)    (c===2)
//뒷면 : 주황 (O) (c==0)
//왼 : 초록 (G)  (r==0)
//오 : 파랑 (B)  (r==2)

void rotationU(int dir) {   //0
	vector<pair<int, char>> temp[3][3];

		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				for (int i = 0; i < Cube[0][r][c].size(); i++) {
					int face = Mapping[0][dir][Cube[0][r][c][i].first];
					char color = Cube[0][r][c][i].second;
					if (dir == 0) {
						temp[c][2 - r].push_back({ face,color });
					}
					else if (dir == 1) {
						temp[2 - c][r].push_back({ face,color });
					}
					
				}
			}
		}
		//다시 옮겨담기
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				Cube[0][r][c] = temp[r][c];
			}
		}
		int debugging = -1;
}
void rotationD(int dir) {   //1
	vector<pair<int, char>> temp[3][3];

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			for (int i = 0; i < Cube[2][r][c].size(); i++) {
				int face = Mapping[1][dir][Cube[2][r][c][i].first];
				char color = Cube[2][r][c][i].second;
				if (dir == 0) {
					temp[2-c][r].push_back({ face,color });
				}
				else if (dir == 1) {
					temp[c][2- r].push_back({ face,color });
				}
			}
		}
	}
	//다시 옮겨담기
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Cube[2][r][c] = temp[r][c];
		}
	}
}
void rotationF(int dir) {
	vector<pair<int, char>> temp[3][3];

	for (int h = 0; h < 3; h++) {
		for (int c = 0; c < 3; c++) {
			for (int i = 0; i < Cube[h][2][c].size(); i++) {
				int face = Mapping[2][dir][Cube[h][2][c][i].first];
				char color = Cube[h][2][c][i].second;
				if (dir == 0) {
					temp[c][2 - h].push_back({ face,color });
				}
				else if (dir == 1) {
					temp[2 - c][h].push_back({ face,color });
				}

			}
		}
	}
	//다시 옮겨담기
	for (int h = 0; h < 3; h++) {
		for (int c = 0; c < 3; c++) {
			Cube[h][2][c] = temp[h][c];
		}
	}
	int debugging = -1;
}
void rotationB(int dir) {
	vector<pair<int, char>> temp[3][3];

	for (int h = 0; h < 3; h++) {
		for (int c = 0; c < 3; c++) {
			for (int i = 0; i < Cube[h][0][c].size(); i++) {
				int face = Mapping[3][dir][Cube[h][0][c][i].first];
				char color = Cube[h][0][c][i].second;
				if (dir == 0) {
					temp[2-c][h].push_back({ face,color });
				}
				else if (dir == 1) {
					temp[c][2-h].push_back({ face,color });
				}
			}
		}
	}
	//다시 옮겨담기
	for (int h = 0; h < 3; h++) {
		for (int c = 0; c < 3; c++) {
			Cube[h][0][c] = temp[h][c];
		}
	}
	int debugging = -1;
}
void rotationL(int dir) {

	vector<pair<int, char>> temp[3][3];

	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			for (int i = 0; i < Cube[h][r][0].size(); i++) {
				int face = Mapping[4][dir][Cube[h][r][0][i].first];
				char color = Cube[h][r][0][i].second;
				if (dir == 0) {
					temp[r][2 - h].push_back({ face,color });
				}
				else if (dir == 1) {
					temp[2 - r][h].push_back({ face,color });
				}
				
			}
		}
	}
	//다시 옮겨담기
	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			Cube[h][r][0] = temp[h][r];
			int debugging = -1;
		}
	}
}
void rotationR(int dir) {

	vector<pair<int, char>> temp[3][3];

	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			for (int i = 0; i < Cube[h][r][2].size(); i++) {
				int face = Mapping[5][dir][Cube[h][r][2][i].first];
				char color = Cube[h][r][2][i].second;
				if (dir == 0) {
					temp[2- r][h].push_back({ face,color });
				}
				else if (dir == 1) {
					temp[r][2-h].push_back({ face,color });
				}
			}
		}
	}
	//다시 옮겨담기
	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			Cube[h][r][2] = temp[h][r];
		}
	}
}

void simulation(char plane, char dir) {

	int temp_dir;
	if (dir == '+') {   //시계방향 90도 : 0
		temp_dir = 0;
	}
	else if (dir == '-') { //반시계방향 90도 : 1
		temp_dir = 1;
	}


	if (plane == 'U') { // 윗면 
		rotationU(temp_dir);
	}
	else if (plane == 'D') {  //아랫면 돌리기
		rotationD(temp_dir);
	}
	else if (plane == 'F') {  //앞면 돌리기
		rotationF(temp_dir);
	}
	else if (plane == 'B') {  //뒷면 돌리기
		rotationB(temp_dir);
	}
	else if (plane == 'L') {  //왼쪽면 돌리기
		rotationL(temp_dir);
	}
	else if (plane == 'R') {  //오른쪽면 돌리기
		rotationR(temp_dir);
	}

}

void init() {

	//초기화
	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				Cube[h][r][c].clear();
			}
		}
	}

	// 윗면 아랫면 채우기
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			//윗면 채우기
			Cube[0][r][c].push_back({ 0,'w' });
			//아랫면 채우기
			Cube[2][r][c].push_back({ 1,'y' });
		}
	}
	//앞 뒤 면 채우기
	for (int h = 0; h < 3; h++) {
		for (int c = 0; c < 3; c++) {
			//앞면 채우기
			Cube[h][2][c].push_back({ 2,'r' });
			//뒷면 채우기
			Cube[h][0][c].push_back({ 3,'o' });
		}
	}

	//왼쪽면 오른쪽면 채우기
	for (int h = 0; h < 3; h++) {
		for (int r = 0; r < 3; r++) {
			//왼쪽면
			Cube[h][r][0].push_back({ 4,'g' });
			//오른쪽면
			Cube[h][r][2].push_back({ 5,'b' });
		}
	}

	int debugging = -1;
}

void input() {
	cin >> T;
	for (int test = 0; test < T; test++) {
		init();
		int N;
		cin >> N;

		for (int i = 0; i < N; i++) {
			char plane;
			char dir;
			cin >> plane >> dir;

			simulation(plane, dir);
		}

		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				for (int i = 0; i < Cube[0][r][c].size(); i++) {
					if (Cube[0][r][c][i].first == 0) {
						cout << Cube[0][r][c][i].second;
						break;
					}
				}
			}
			cout << "\n";
		}
	}
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	
	input();
	

	return 0;
}