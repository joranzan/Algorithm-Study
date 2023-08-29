#include<iostream>
#include<vector>

using namespace std;

static vector<int> parent;
static vector<vector<int>> Party;
static vector<int> Truth;

void unionfunc(int a, int b);
int find(int index);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	int answer = 0;
	cin >> N >> M;
	parent.resize(N + 1);
	for (int i = 1; i <= N; i++)
	{
		parent[i] = i;
	}
	int T;
	cin >> T;
	if (T == 0)
	{
		cout << M << "\n";
		return 0;
	}
	Truth.resize(T);
	for (int i = 0; i < T; i++)
	{
		cin >> Truth[i];
	}
	Party.resize(M);
	for (int i = 0; i < M; i++)
	{
		int member;
		cin >> member;
		for (int j = 0; j < member; j++)
		{
			int temp;
			cin >> temp;
			Party[i].push_back(temp);
		}
	}
	
	for (int i = 0; i < M; i++)
	{
		int firstmember = Party[i][0];
		for (int j = 1; j < Party[i].size(); j++)
		{
			unionfunc(firstmember, Party[i][j]);
		}
	}

	for (int i = 0; i < M; i++)
	{
		bool possible = true;
		int cur = Party[i][0];
		for (int j = 0; j < T; j++)
		{
			if (find(Truth[j]) == find(cur))
			{
				possible = false;
				break;
			}
		}
		if (possible)
		{
			answer++;
		}
	}
	cout << answer << "\n";
	return 0;
}

void unionfunc(int a, int b)
{
	a = find(a);
	b = find(b);

	if (a != b)
	{
		parent[b] = a;
	}
}

int find(int index)
{
	if (index == parent[index])
	{
		return index;
	}
	else
	{
		return parent[index] = find(parent[index]);
	}
}