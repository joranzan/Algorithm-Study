#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<string> split(string s, char delimiter);
int solution(vector<string> s);


int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	string mystring;
	cin >> mystring;
	vector<string> v;
	int answer;

	v = split(mystring, '-');
	answer = solution(v);

	cout << answer << "\n";

	return 0;
}

vector<string> split(string s, char delimiter)
{
	vector<string> result;
	string str;

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == delimiter)
		{
			result.push_back(str);
			str.clear();
		}
		else
		{
			str.push_back(s[i]);
		}
	}
	result.push_back(str);
	return result;
}

int solution(vector<string> v)
{
	int sum = 0;
	for (int i = 0; i < v.size(); i++)
	{
		int temp_sum = 0;
		vector<string> temp = split(v[i], '+');
		for (int j = 0; j < temp.size(); j++)
		{
			temp_sum += stoi(temp[j]);
		}
		if (i == 0)
		{
			sum += temp_sum;
		}
		else
		{
			sum -= temp_sum;
		}
	}
	return sum;
}