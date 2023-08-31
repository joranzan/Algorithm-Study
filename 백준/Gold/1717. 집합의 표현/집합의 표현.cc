#include<iostream>
#include<vector>

using namespace std;

static vector<int> arr;

int find(int index);
void unionfunc(int a, int b);
bool checkSame(int a, int b);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;
	arr.resize(N + 1);
	for (int i = 0; i <= N; i++)
	{
		arr[i] = i;
	}
	int op, node1, node2;
	for (int i = 0; i < M; i++)
	{
		cin >> op >> node1 >> node2;
		if (op == 0)
		{
			unionfunc(node1, node2);
		}
		else
		{
			if (checkSame(node1, node2)) cout << "YES" << "\n";
			else cout << "NO\n";
		}
	}
}
void unionfunc(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a != b)
	{
		arr[b] = a;
	}
}
int find(int index)
{
	if (index == arr[index])
	{
		return index;
	}
	else
	{
		return arr[index] = find(arr[index]);
	}
}
bool checkSame(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a != b) return false;
	else return true;
}