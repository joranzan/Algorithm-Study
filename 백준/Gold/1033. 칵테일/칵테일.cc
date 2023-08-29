#include<iostream>
#include<vector>
#include<tuple>
using namespace std;

vector < tuple<int, int, int>> Adjacent[10]; //인덱스: 노드  (인접노드, 분자, 분모)
long LCM = 1;
bool Visited[10]={false,};
long Result[10];
int N;
long gcd(long a, long b);
void DFS(int node);


int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N - 1; i++)
	{
		int a, b, p, q;
		cin >> a >> b >> p >> q;
		Adjacent[a].push_back(make_tuple(b, p, q));
		Adjacent[b].push_back(make_tuple(a, q, p));
		LCM *= p * (q / gcd(p, q));
	}

	Result[0] = LCM;
	DFS(0);
	long mgcd = Result[0];
	for (int i = 1; i < N; i++)
	{
		mgcd = gcd(mgcd, Result[i]);
	}
	for (int i = 0; i < N; i++)
	{
		cout << Result[i] / mgcd << " ";
	}

	return 0;
}
void DFS(int node)
{
	Visited[node] = true;
	for (tuple<int, int, int> i : Adjacent[node])
	{
		int next_node = get<0>(i);
		if (!Visited[next_node])
		{
			Result[next_node] = Result[node] * get<2>(i) / get<1>(i);
			DFS(next_node);
		}
	}
}


long gcd(long a, long b)
{
	if (a < b)
	{
		swap(a, b);
	}
	while (1)
	{
		long residue = a % b;
		if (residue == 0) break;
		a = b;
		b = residue;
	}
	return b;
}