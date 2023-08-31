#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

bool isPalindrome(long Num)
{
	string temp_str = to_string(Num);
	vector<int> temp(temp_str.length(),0);
	for (int i = 0; i < temp_str.length(); i++)
	{
		temp[i] = temp_str[i] - '0';
	}
	int start = 0;
	int end = temp.size() - 1;
	bool found = true;
	while (start < end)
	{
		if (temp[start] != temp[end])
		{
			found = false;
			break;
		}
		else
		{
			start++;
			end--;
		}
	}
	return found;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	long N;
	cin >> N;
	vector<long> PrimeNum(2000000 + 1, 1);

	PrimeNum[0] = 0;
	PrimeNum[1] = 0;
	for (int i = 2; i <= 2000000; i++)
	{
		if (PrimeNum[i] == 0) continue;
		if (isPalindrome(i) && i >= N)
		{
			cout << i << "\n";
			break;
		}
		for (int j = i + i; j <= 2000000; j = j + i)
		{
			PrimeNum[j] = 0;
		}
		
	}

	return 0;
}