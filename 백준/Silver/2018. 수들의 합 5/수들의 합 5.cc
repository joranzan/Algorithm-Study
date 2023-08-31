#include<iostream>
#include<vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	int start_index = 1;
	int end_index = 1;
	int count = 1;  //N 하나인 경우
	int sum = 1;

	while (end_index != N)
	{
		if (sum <= N)
		{
			if (sum == N) count++;
			end_index++;
			sum += end_index;
		}
		else if (sum > N)
		{
			sum -= start_index;
			start_index++;
		}
	}
	cout << count << "\n";

	return 0;
}