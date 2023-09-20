#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

vector<vector<int>> Adj;
int Visited[100001] = { 0, };
int N;

void BFS() {

	queue<int> q;
	q.push(1);
	Visited[1] = 1;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int i = 0; i < Adj[now].size(); i++) {
			int next = Adj[now][i];
			if (Visited[next] != 0) continue;
			Visited[next] = now;
			q.push(next);			
		}
	}
}

int main()
{
	cin >> N;
	Adj.resize(N + 1);
	for (int i = 0; i < N-1; i++)
	{
		int from, to;
		cin >> from >> to;

		Adj[from].push_back(to);
		Adj[to].push_back(from);
	}
	BFS();

	for (int i = 2; i <= N; i++) {
		cout << Visited[i] << "\n";
	}


	return 0;
}