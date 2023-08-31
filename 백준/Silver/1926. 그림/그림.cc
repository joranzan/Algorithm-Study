#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

//문제 분석


//목표: 그림의 개수, 그림의 넓이 중 최대 
//1로 연결된 애들이 그림

//BFS로 풀어보자~!

int N, M;
int Map[501][501] = { 0, };
int Visited[501][501] = { 0, };
vector<int> Answer;  //찾은 넓이 넣는 배열

void input() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
		}
	}
}

void BFS(int row, int col) {

	queue<pair<int, int>> q;
	q.push({ row,col });

	int cnt = 1; //넓이 담을 변수

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
			if (Map[next_r][next_c] == 0) continue;
			if (Visited[next_r][next_c] == 1) continue;
			Visited[next_r][next_c] = 1;
			cnt++;
			q.push({ next_r,next_c });
		}
	}

	Answer.push_back(cnt);
}

void solution() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] == 0) continue; //색칠안되어있으면 무시
			if (Visited[i][j] == 1) continue; //이미 방문해서 검사한 위치면 무시
			Visited[i][j] = 1;
			BFS(i, j);
		}
	}

	
	int max_area = 0;
	for (int i = 0; i < Answer.size(); i++) {
		max_area = max(max_area, Answer[i]);
	}

	cout << Answer.size() << "\n";
	cout << max_area;
}

int main() {

	input();
	solution();

	return 0;
}

//BFS설계

//세로 N 가로 M  (500x500)  -> 시간복잡도 BFS 충분


//Visited배열도 만들어야함
//BFS에서 cnt로 넓이 찾은다음에 Answer 벡터에 Push 하자
//벡터 크기, 최대값 구하기
