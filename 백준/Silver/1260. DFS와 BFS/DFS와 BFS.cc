#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

static vector<vector<int>> AdjacentList; 
static vector<bool> Visited;

void DFS(int start);
void BFS(int start);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, M, Start;
	cin >> N >> M >> Start;

	AdjacentList.resize(N + 1);
	Visited = vector<bool>(N + 1, false);

	for (int i = 1; i <= M; i++)
	{
		int u, v;
		cin >> u >> v;
		AdjacentList[v].push_back(u);
		AdjacentList[u].push_back(v);
	}

	for (int i = 1; i <= N; i++)
	{
		sort(AdjacentList[i].begin(), AdjacentList[i].end());
	}

	DFS(Start);
	cout << "\n";
	Visited = vector<bool>(N + 1, false);
	//fill(Visited.begin(),Visited.end(),false);
	BFS(Start);
	cout << "\n";


	return 0;
}

void DFS(int start)
{
	cout << start << " ";
	Visited[start] = true;

	for (auto i : AdjacentList[start])
	{
		int next_node = i;
		if (Visited[next_node]) continue;
		DFS(i);
		
	}
}

void BFS(int start)
{
	queue<int> myQueue;
	myQueue.push(start);
	Visited[start] = true;

	while (!myQueue.empty())
	{
		int current_node = myQueue.front();
		myQueue.pop();
		cout << current_node << " ";
		for (auto i : AdjacentList[current_node])
		{
			if (!Visited[i])
			{
				Visited[i] = true;
				myQueue.push(i);
			}
		}
	}
}