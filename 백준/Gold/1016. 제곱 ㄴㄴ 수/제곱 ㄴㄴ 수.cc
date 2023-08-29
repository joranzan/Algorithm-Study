#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	long long Min, Max;
	cin >> Min >> Max;
	vector<bool> Check(Max - Min + 1, true);

	

	for (long long i = 2; i * i <= Max; i++)
	{
		long long pow_num = i * i;
		long long start_index = 0;
		long long pow_num_temp = pow_num;
		if (Min % pow_num == 0)
		{
			pow_num_temp = Min;
		}
		else
		{
			pow_num_temp = Min - (Min % pow_num) + pow_num;
		}		
		
		while (pow_num_temp <= Max)
		{
			if (Check[pow_num_temp - Min] == false)
			{
				pow_num_temp += pow_num;
				continue;
			}
			else
			{
				Check[pow_num_temp - Min] = false;
				pow_num_temp += pow_num;
			}			
		}
		/*while (start_index < Max - Min + 1)
		{
			
			if ((Min + start_index) % pow_num==0)
			{
				Check[start_index] = false;
			}
			start_index++;
		}*/
	}
	int count = 0;
	for (long long i = 0; i < Check.size(); i++)
	{
		if (Check[i])
		{
			count++;
		}
	}

	cout << count << "\n";

	return 0;
}