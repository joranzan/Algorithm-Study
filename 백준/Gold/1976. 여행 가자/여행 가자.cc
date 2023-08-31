#include<iostream>
#include<vector>

using namespace std;

static vector<int> parent;
void unionfunc(int i, int j);
int find(int index);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	int cityarr[201][201];
	vector<int> planarr(M, 0);
	parent.resize(N + 1);

	for (int i = 1; i <= N; i++)
	{
		parent[i] = i;
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> cityarr[i][j];
		}
	}
	for (int i = 0; i < M; i++)
	{
		cin >> planarr[i];
		
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (cityarr[i][j] == 1)
			{
				unionfunc(i, j);
			}
		}
	}
	int pivot = find(planarr[0]);
	bool possible = true;

	for (int i = 1; i < M; i++)
	{
		if (pivot != find(planarr[i]))
		{
			cout << "NO\n";
			possible = false;
			break;
		}
	}
	if (possible) cout << "YES\n";

	return 0;
}

void unionfunc(int i, int j)
{
	i = find(i);
	j = find(j);
	if (i != j)
	{
		parent[j] = i;
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