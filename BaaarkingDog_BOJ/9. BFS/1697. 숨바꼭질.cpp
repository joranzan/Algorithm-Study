#include<iostream>
#include<queue>
#include<climits>

using namespace std;


//문제 분석
// x-1 x+1 2*X 위치로 갈 수 있음
//
// //수빈이 찾기
int N, K;
long long Answer = LONG_MAX;
void BFS() {

	long long Visited[200000] = { 0 };
	queue<int> q;
	q.push(N);
	Visited[N] = 1;

	while (!q.empty()) {

		long long now = q.front();
		q.pop();

		if (now == K) {
			Answer = min(Answer, Visited[now] - 1);
		}

		long long d1 = now - 1;
		long long d2 = now + 1;
		long long d3 = now * 2;

		long long dir[3] = { d1, d2, d3 };

		for (int i = 0; i < 3; i++) {
			int next = dir[i];
			if (next < 0 || next>200000) continue;
			if (Visited[next] <= Visited[next] + 1) continue;
			Visited[next] = Visited[next] + 1;
			q.push(next);
		}
	}

}


int main() {

	cin >> N >> K;
	BFS();
	cout << Answer;

	return 0;
}

