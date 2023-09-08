#include<iostream>
#include<climits>
#include<queue>

using namespace std;

//문제 분석

//나이트 이동 방향 -> 방향 배열 만들기 8개짜리

//map 300 x 300
//현재 위치
//Target 위치

int N;
int Distance[300][300];
int start_r, start_c;
int target_r, target_c;

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Distance[i][j] = INT_MAX;
		}
	}
}

void input() {
	cin >> N;
	cin >> start_r >> start_c;
	cin >> target_r >> target_c;
}

int BFS() {

	queue<pair<int, int>> q;
	q.push({ start_r,start_c });
	Distance[start_r][start_c] = 1;

	const int dr[8] = { -2,-1,1,2,2,1,-1,-2 };
	const int dc[8] = { 1,2,2,1,-1,-2,-2,-1 };



	while (!q.empty()) {
		int now_r = q.front().first;
		int now_c = q.front().second;
		q.pop();

		if (now_r == target_r && now_c == target_c) {
			return Distance[now_r][now_c] - 1;
		}

		for (int i = 0; i < 8; i++) {
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];

			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= N) continue;
			if (Distance[next_r][next_c] <= Distance[now_r][now_c] + 1) continue;
			Distance[next_r][next_c] = Distance[now_r][now_c] + 1;
			q.push({ next_r,next_c });
		}
	}
}

void solution() {
	
	cout << BFS() << "\n";
}

int main() {

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		
		input();
		init();
		solution();
	}


	return 0;
}