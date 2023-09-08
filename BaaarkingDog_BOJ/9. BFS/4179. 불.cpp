#include<iostream>
#include<vector>

using namespace std;

//내가 처음에 한 실수 : 초기 입력 값들에 대하여 Visited배열을 업데이트 안했음 ㅠ


//문제 분석

//이동
//불이 붙은 위치 감안
//불: 상하좌우 (벽 통과X)
//지훈: 상하좌우 1분에 1칸씩 (벽 통과 X)
// 
// 탈출
// 가장자리 접한 곳 0,R-1 C-1 0
// 
// 목표
//불에 타기 전 탈출 여부
//얼마나 빨리
struct pos {
	int row;
	int col;
};


int R, C;
char Map[1000][1000] = { 0, };
int Visited_Fire[1000][1000] = { 0, };
int Visited_JH[1000][1000] = { 0, };
vector<pos> JH;  // JH가 현재 갈 수 있는 위치들
vector<pos> Fire; //불이 현재 퍼질 수 있는 위치들


void input() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 'J') {
				JH.push_back({ i,j });
				Visited_JH[i][j] = 1;
			}
			else if (Map[i][j] == 'F') {
				Fire.push_back({ i,j });
				Visited_Fire[i][j] = 1;
			}
		}
	}

}

const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

void fire_BFS() { //한번단 최대 시간복잡도 16

	vector<pos> temp = Fire;
	Fire.clear();
	for (int coord = 0; coord < temp.size(); coord++) {
		int now_r = temp[coord].row;
		int now_c = temp[coord].col;

		for (int dir = 0; dir < 4; dir++) {
			int next_r = now_r + dr[dir];
			int next_c = now_c + dc[dir];
			if (next_r < 0 || next_c < 0 || next_r >= R || next_c >= C) continue;
			if (Map[next_r][next_c] == '#') continue;
			if (Visited_Fire[next_r][next_c] == 1) continue;  //이미 검사했으면 무시
			Visited_Fire[next_r][next_c] = 1;
			Fire.push_back({ next_r,next_c });
		}
	}

}

void JH_BFS() {   //한번단 최대 시간복잡도 16
	vector<pos> temp = JH;
	JH.clear();
	for (int coord = 0; coord < temp.size(); coord++) {
		int now_r = temp[coord].row;
		int now_c = temp[coord].col;

		for (int dir = 0; dir < 4; dir++) {
			int next_r = now_r + dr[dir];
			int next_c = now_c + dc[dir];
			if (next_r < 0 || next_c < 0 || next_r >= R || next_c >= C) continue;
			if (Map[next_r][next_c] == '#') continue;
			if (Visited_Fire[next_r][next_c] == 1) continue; //이미 불 옮겨진 곳 무시
			if (Visited_JH[next_r][next_c] == 1) continue;  //이미 검사했으면 무시
			Visited_JH[next_r][next_c] = 1;
			JH.push_back({ next_r,next_c });		
		}
	}
}


void solution() {


	int time = 0;
	while (1) {

		bool escapeValid = false;

		//탈출 불가능한 경우
		//JH가 가장자리가 아니었는데 더이상 갈곳이 없다(size=0)
		if (JH.size() == 0) {
			cout << "IMPOSSIBLE";
			break;
		}
		//갈곳 있다면
		else {
			for (int i = 0; i < JH.size(); i++) {
				pos coord = JH[i];
				//탈출 가능한 경우
				//if(가장자리일 경우가 존재한다면!) 시간 출력
				if (coord.row == 0 || coord.row == R - 1 || coord.col == 0 || coord.col == C - 1) {
					cout << time + 1;
					escapeValid = true;
					break;
				}
			}
		}

		if (escapeValid) break;
		//Keep going
		//JH가 가장자리는 아니지만 갈 곳은 남은 상황(size!=0)

		time++;
		fire_BFS();
		JH_BFS();

	}

}

int main() {

	input();
	solution();



	return 0;
}

//설계

//BFS 가능 (1000 1000)

//Fire 먼저 Flood Fill
//지훈 이동할 수 있는 곳 Visited ++


//전역변수로 Queue_Fire  Queue_JH (vector로 해도 될듯한데??)

//while(1)
//while문 빠져나올 조건
//탈출 가능한 경우
//if(가장자리일 경우가 존재한다면!) 시간 출력

//탈출 불가능한 경우
//JH가 가장자리가 아니었는데 더이상 갈곳이 없다(size=0)

//Keep going
//JH가 가장자리는 아니지만 갈 곳은 남은 상황(size!=0)
