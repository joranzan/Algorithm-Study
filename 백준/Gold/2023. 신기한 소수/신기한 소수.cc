#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

static int N;
void DFS(int n, int digit);
bool Prime(int n);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	DFS(2, 1);
	DFS(3, 1);
	DFS(5, 1);
	DFS(7, 1);

	return 0;
}

void DFS(int n, int digit)
{
	if (digit == N)
	{
		cout << n << "\n";
		return;
	}
	digit++;
	for (int i = 1; i <= 9; i++)
	{
		if (i % 2 == 0) continue;
		int next_n = n * 10 + i;
		if (Prime(next_n))
		{
			DFS(next_n, digit);
		}
	}
}

bool Prime(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}