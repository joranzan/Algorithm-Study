#include<iostream>
#include<vector>

using namespace std;

int main()
{

	int N;
	cin >> N;

	vector<int> time(N, 0);
	vector<int> sum(N, 0);

	for (int i = 0; i < N; i++)
	{
		cin >> time[i];
	}

	for (int i = 1; i < N; i++)
	{
		int insert_value = time[i];
		int insert_point = i;
		for (int j = i - 1; j >= 0; j--)
		{
			/*if (j == 0)
			{
				time[j] = insert_value;
				break;
			}*/
			if (time[j] <= insert_value)
			{
				insert_point = j + 1;
				break;
			}
			else if (time[j] > insert_value)
			{
				time[j + 1] = time[j];
				insert_point = j;
			}
		}
		time[insert_point] = insert_value;
	}
	sum[0] = time[0];
	for (int i = 1; i < N; i++)
	{
		sum[i] = sum[i - 1] + time[i];
	}

	int answer = 0;
	for (int i = 0; i < N; i++)
	{
		answer += sum[i];
	}
	
	cout << answer;

	return 0;
}