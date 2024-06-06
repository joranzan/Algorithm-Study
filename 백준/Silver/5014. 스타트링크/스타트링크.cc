#include<iostream>
#include<queue>

using namespace std;

int Floor, Start, Goal, Up, Down;

int Visited[1000001] = { 0, };
int BFS() {

	queue<int> q;
	q.push(Start);
	Visited[Start] = 1;

	while (!q.empty()) {

		int now = q.front();
		q.pop();

		if (now == Goal) {
			return Visited[now] - 1;
		}

		int next_up = now + Up;
		int next_down = now - Down;

		if (next_up <= Floor&&Visited[next_up]==0) {
			Visited[next_up] = Visited[now] + 1;
			q.push(next_up);
		}

		if (next_down > 0 && Visited[next_down]==0) {
			Visited[next_down] = Visited[now] + 1;
			q.push(next_down);
		}

	}
	return -1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> Floor >> Start >> Goal >> Up >> Down;

	int answer = BFS();

	if (answer == -1) cout << "use the stairs\n";
	else cout << answer;

	return 0;
}

/*
문제 분석

총 F층

스타트링크 : G층

강호 : S층

U만큼 D만큼

*/