#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int M, N;
	cin >> M >> N;
	vector<int> array(N + 1, 1);
	array[0] = 0;
	array[1] = 0;
	for (int i = 2; i <= N; i++)
	{
		if (array[i] == 0) continue;
		int multiple = 2;
		while (multiple * i <= N)
		{
			array[multiple * i] = 0;
			multiple++;
		}
	}
	for (int i = M; i <= N; i++)
	{
		if (array[i] == 0) continue;
		cout << i << "\n";
	}


	return 0;
}