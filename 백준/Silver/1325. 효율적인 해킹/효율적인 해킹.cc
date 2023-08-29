#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

static int N;
static vector<vector<int>> AdjacentList;
static vector<bool> Visited;
static vector<int> Result;

int BFS(int start);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int M;
	cin >> N >> M;
	AdjacentList.resize(N + 1);
	Visited = vector<bool>(N + 1, false);
	Result = vector<int>(N + 1, 0);
	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> to >> from;
		AdjacentList[from].push_back(to);
	}

	for (int i = 1; i <= N; i++)
	{
		fill(Visited.begin(), Visited.end(), false);
		int depth = BFS(i);
		Result[i] = depth;
	}

	int max_depth = *max_element(Result.begin() + 1, Result.end());
	for (int i = 1; i <= N; i++)
	{
		if (Result[i] == max_depth)
		{
			cout << i << " ";
		}
	}

	return 0;
}

int BFS(int start)
{
	int depth = 1;
	queue<int> myQueue;
	myQueue.push(start);
	Visited[start] = true;

	while (!myQueue.empty())
	{
		int current_node = myQueue.front();
		myQueue.pop();
		for (auto i : AdjacentList[current_node])
		{
			if (Visited[i]) continue;
			Visited[i] = true;
			depth++;
			myQueue.push(i);
		}
	}
	return depth;
}