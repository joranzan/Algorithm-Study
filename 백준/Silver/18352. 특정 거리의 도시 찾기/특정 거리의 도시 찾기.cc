#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

static int N, K;
static vector<vector<int>> AdjacentList;
static vector<bool> Visited;
static vector<int> Result;

void BFS(int start);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	int M, X;
	cin >> N >> M >> K >> X;
	AdjacentList.resize(N + 1);
	Visited = vector<bool>(N + 1, false);
	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> from >> to;
		AdjacentList[from].push_back(to);
	}
	BFS(X);
	
	sort(Result.begin(), Result.end());

	if (Result.empty())
	{
		cout << "-1\n";
	}
	for (int i = 0; i < Result.size(); i++)
	{
		cout << Result[i] << "\n";
	}

	return 0;
}

void BFS(int start)
{
	queue<pair<int,int>> myQueue;

	myQueue.push(make_pair(start,0));
	Visited[start] = true;
	while (!myQueue.empty())
	{
		int current_node = myQueue.front().first;
		int current_length = myQueue.front().second;
		myQueue.pop();
		

		if (current_length == K)
		{
			Result.push_back(current_node);
			continue;
		}		
		
		for (auto i : AdjacentList[current_node])
		{
			if (Visited[i]) continue;
			myQueue.push(make_pair(i, current_length + 1));
			Visited[i] = true;
		}

	}
}