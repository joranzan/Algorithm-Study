#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

//문제 분석
//익은 토마토, 안익은 토마토
//보관 후 1일 뒤 (상하좌우) 익음
//다 익는 최소 일 수 -> Flood Fill? Visited배열에 깊이 저장?

//1: 익은 토마토, 0: 안익은 토마토  -1: 토마토 없음

int N, M;
int Map[1000][1000] = { 0, };
int Visited[1000][1000] = { 0, };
vector<pair<int, int>> wellDone; //초기 익은 애들의 좌표 등록


void input() {

	cin >> M >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			Visited[i][j] = INT_MAX;
			if (Map[i][j] == 1) {
				wellDone.push_back({ i,j });
			}
			else if (Map[i][j] == -1) {
				Visited[i][j] = -1;
			}
		}
	}
}

int BFS() {

	
	queue<pair<int, int>> q;
	for (int i = 0; i < wellDone.size(); i++) {
		q.push(wellDone[i]);
		Visited[wellDone[i].first][wellDone[i].second] = 1;
	}

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	while (!q.empty()) {

		int now_r = q.front().first;
		int now_c = q.front().second;
		q.pop();
		
		for (int dir = 0; dir < 4; dir++) {
			int next_r = now_r + dr[dir];
			int next_c = now_c + dc[dir];
			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= M) continue;
			if (Map[next_r][next_c] == -1) continue;
			if (Visited[next_r][next_c] <= Visited[now_r][now_c] + 1) continue;
			Visited[next_r][next_c] = Visited[now_r][now_c] + 1;
			q.push({ next_r,next_c });
		}
	}


	//1일 뒤부터 퍼지는데 초기부터 1로 잡아놨으니
	bool valid = true;
	int max_day = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] == -1) continue;
			if (Visited[i][j] == INT_MAX) {
				valid = false;
				break;
			}
			max_day = max(max_day, Visited[i][j]);
		}
		if (!valid) break;
	}
	//INT_MAX 존재하면 -1 return
	if (!valid) {
		return -1;
	}
	//0이 존재안하면 (Max값 -1) return
	else {
		return max_day - 1;
	}

}


void solution() {

	cout<< BFS();

}





int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();



	return 0;
}

//설계
//NxM 1000x1000
//Flood Fill 로 풀기 

//모두 익지 못하면 0-> 아직 Visited에 방문하지 못한 경우