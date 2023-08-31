#include<iostream>
#include<vector>
#include<queue>
#include<limits.h>

using namespace std;

typedef pair<int, int> edge;

int main()
{
	int N, M;
	cin >> N >> M;
	vector<vector<edge>> AdjacentList(N + 1);
	vector<int> Cost(N + 1, INT_MAX);
	vector<bool> Visited(N + 1, false);
	priority_queue<edge, vector<edge>, greater<edge>> pq; //오름차순 우선순위 큐

	for (int i = 0; i < M; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		AdjacentList[u].push_back(make_pair(v, w));
	}

	int start, destin;
	cin >> start >> destin;

	pq.push(make_pair(0,start)); //비용 넣는 이유: 비용으로 정렬할라고
	Cost[start] = 0;

	while (!pq.empty())
	{
		int current_node = pq.top().second;
		pq.pop();
		if (Visited[current_node]) continue;  //우선순위 큐로 각 노드에 가장 작은 경로 top에 update되므로 중복X
		Visited[current_node] = true; 

		for (auto &next : AdjacentList[current_node])
		{
			int next_node = next.first;
			int next_value = next.second;
			if (Cost[next_node] > Cost[current_node] + next_value)
			{
				Cost[next_node] = Cost[current_node] + next_value;
				pq.push(make_pair(Cost[next_node], next_node));
			}
		}
	}
	cout << Cost[destin] << "\n";
	return 0;
}