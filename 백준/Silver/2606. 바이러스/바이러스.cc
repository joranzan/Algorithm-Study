#include<iostream>
#include<vector>

using namespace std;

static vector<vector<int>> AdjacentList;
static vector<bool> Visited;
int result = 0;
void DFS(int start);

int main()
{
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
	DFS(1);
	cout << result << "\n";

	return 0;
}

void DFS(int start)
{
	if (Visited[start]) return;

	Visited[start] = true;
	
	
	for (int i = 0; i < AdjacentList[start].size(); i++)
	{
		int next_node = AdjacentList[start][i];
		if (Visited[next_node]) continue;
		DFS(next_node);
		result++;
	}
}