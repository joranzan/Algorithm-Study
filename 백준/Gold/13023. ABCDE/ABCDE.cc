#include<iostream>
#include<vector>

using namespace std;

static vector<vector<int>> AdjacentList;
static vector<bool> Visited;
void DFS(int start, int depth);
static bool FriendYes;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, M;
	cin >> N >> M;
	AdjacentList.resize(N);
	Visited = vector<bool>(N, false);
	FriendYes = false;

	for (int i = 0; i < M; i++)
	{
		int u, v;
		cin >> u >> v;
		AdjacentList[u].push_back(v);
		AdjacentList[v].push_back(u);
	}

	for (int i = 0; i < N; i++)
	{
		if (Visited[i] == true) continue;
		DFS(i, 1);
		if (FriendYes)
		{
			cout << "1\n";
			break;
		}
	}
	if (!FriendYes) cout << "0\n";
	return 0;
}

void DFS(int start, int depth)
{
	if (depth == 5||FriendYes)
	{
		FriendYes = true;
		return;
	}
	if (Visited[start] == 1) return;
	
	depth++;
	Visited[start] = true;
	for (int i = 0; i < AdjacentList[start].size(); i++)
	{
		int current_node = AdjacentList[start][i];
		if (Visited[current_node] == 0)
		{
			DFS(current_node, depth);
		}
	}
	Visited[start] = false;
}