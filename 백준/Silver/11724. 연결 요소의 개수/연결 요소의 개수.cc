#include<iostream>
#include<vector>

using namespace std;

static vector<vector<int>> AdjacentList;
static vector<bool> Visited;
void DFS(int start);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;
	AdjacentList.resize(N + 1);
	Visited = vector<bool>(N + 1, false);

	for (int i = 1; i <= M; i++)
	{
		int u, v;
		cin >> u >> v;
		AdjacentList[u].push_back(v);
		AdjacentList[v].push_back(u);
	}
	int answer = 0;

	for (int i = 1; i <= N; i++)
	{
		if (Visited[i] == false)
		{
			DFS(i);
			answer++;
		}
	}
	cout << answer << "\n";

	return 0;
}

void DFS(int start)
{
	if (Visited[start]) return;
	Visited[start] = true;
	for (int i = 0; i < AdjacentList[start].size(); i++)
	{
		int current_node = AdjacentList[start][i];
		if (Visited[current_node]) continue;
		DFS(current_node);
	}
}