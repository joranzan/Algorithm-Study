#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

//목표: 최대한 빠른 시간

//문제 분석
//이동 완료 시간: 모든 사람들이 계단을 내려가 아래 층으로 이동완료 시간
// 계단 입구까지 시간 + 대기 시간 + 아래층으로 이동하는 시간
// 
// 계단 입구까지 이동시간 (row차이) + (col 차이)
// 계단 도착: 1분 후 내려 갈 수 있음
// 계단: 최대 3명 나머지는 대기
// 계단 길이 : K -> 내려가는데 K분
// 
//

struct student {
	int row;
	int col;
	int num; //학생 번호
};
struct stairInfo {
	int row;
	int col;
	int length;
};

struct stair {
	int distance;
	int start_time;
	int end_time;

	bool operator<(stair next) const {
		if (distance < next.distance) return false;
		if (distance > next.distance) return true;
		return false;
	}
};
int Simulation();

int N;
int Map[10][10] = { 0, };
int Visited[10] = { 0, };
//int alreadyStair[10] = { 0, }; //대기:0, 계단 위 : 1 계단 끝 : 2
vector<student> student_info;  //학생들 좌표 입력받는 용
vector<stairInfo> stair_info;  //계단 좌표 입력받는 용
priority_queue<stair> Waiting[2];  //대기 우선순위 큐
queue<stair> Stair[2];  //현재 계단 큐
vector<stair> temp[2];  //선택한 계단들
int Answer = INT_MAX;

void init() {

	Answer = INT_MAX;
	student_info.clear();
	stair_info.clear();

	for (int i = 0; i < 10; i++) {
		Visited[i] = 0;
		//alreadyStair[i] = 0;
	}
	for (int i = 0; i < 2; i++) {
		Waiting[i] = priority_queue<stair>();
		Stair[i] = queue<stair>();
		temp[i].clear();
	}
}

void input() {
	cin >> N;
	int num = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 1) {
				student_info.push_back({ i,j,num });
				num++;
			}
			else if (Map[i][j] >= 2) {
				stair_info.push_back({ i,j,Map[i][j] });
			}
		}
	}
}

void DFS(int depth) {

	//기저 조건
	if (depth == student_info.size()) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < temp[i].size(); j++) {
				Waiting[i].push(temp[i][j]);
			}
		}
		Answer = min(Answer, Simulation());
		return;
	}

	for (int i = 0; i < 2; i++) {
		student now = student_info[depth];  //학생
		
		stairInfo choose = stair_info[i];  //고른 계단
		
		//도착까지 거리 계산
		int distance = abs(now.row - choose.row) + abs(now.col - choose.col);

		//현재 계단
		if (Visited[now.num] == 1) continue;
		//일단 대기배열에 다 넣기
		Visited[now.num] = 1;
		temp[i].push_back({ distance,distance + 1, distance + 1 + choose.length });
		//계단 2개중 하나 골랐으니 가라
		DFS(depth + 1);
		//다른 계단 선택하기 위해 골랐던 계단 빼기
		Visited[now.num] = 0;
		temp[i].pop_back();
	}

}

int Simulation() {

	//계단 내려가기 시작하는 시간들 Stair배열에 넣을 때 업데이트

	for (int i = 0; i < 3; i++) {
		if (!Waiting[0].empty()) {
			Stair[0].push(Waiting[0].top());
			Waiting[0].pop();
		}
		if (!Waiting[1].empty()) {
			Stair[1].push(Waiting[1].top());
			Waiting[1].pop();
		}		
	}

	int current_time[2] = { 0, 0 };
	for (int i = 0; i < 2; i++) {
		if (i == 1) {
			int debugging = -1;
		}
		while (!(Waiting[i].empty()) || !(Stair[i].empty())) {
			//기다리는 사람 없는 경우
			if (Waiting[i].size() == 0) {
				while (!Stair[i].empty()) {

					current_time[i] = Stair[i].front().end_time;
					Stair[i].pop();
				}
				break;
			}

			stair Now = Waiting[i].top();

			//이미 3명 있는 경우
			if (Stair[i].size() >= 3) {

				stair First = Stair[i].front();
				Stair[i].pop();
				current_time[i] = First.end_time;
				if (current_time[i] <= Now.start_time) //계단까지 도착하기 전이면
				{
					Stair[i].push(Now);
					Waiting[i].pop();
				}
				else {  //이미 도착해서 대기중이라면
					Now.start_time = current_time[i];
					Now.end_time = Now.start_time + stair_info[i].length;
					Stair[i].push(Now);
					Waiting[i].pop();
				}
			}
		}
	}
	int ret = 0;
	ret = max(current_time[0], current_time[1]);
	/*for (int i = 0; i < 2; i++) {
		if (current_time[i] <= 0) continue;
		ret = min(ret, current_time[i]);
	}*/
	if (ret == 7) {
		int debugging = -1;
	}
	return ret;
}


void solution() {
	DFS(0);
}

int main() {

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {

		init();
		input();
		solution();
		cout << "#" << test << " " << Answer << "\n";
	}

	return 0;
}

//설계

//계단 올라갔는지 여부 DAT or Visited
//우선순위 큐 2개 사용    -> 이미 계단 올라갔거나 끝났으면 그냥 pop()

//1024가지 DFS로 만들고 pq에 넣은 뒤에 탐색(시간복잡도 : 1024) 

//2개의 계단마다 대기 배열도 만들기 -> 현재 계단 queue에 데이터 3개면 대기

//struct 각 계단마다 만들기 ( 우선순위 다르니까)
//계단 1까지 거리
//계단 2까지 거리
//시작 시간(거리가까운애들이 더 빠르겠지?)
//끝나는 시간

