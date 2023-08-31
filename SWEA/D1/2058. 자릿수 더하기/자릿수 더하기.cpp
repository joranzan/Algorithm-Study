#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main()
{
	string mystr;
	cin >> mystr;
	vector<int> num;
	int answer = 0;
	for (int i = 0; i < mystr.length(); i++)
	{
		int tmp = mystr[i] - '0';
		num.push_back(tmp);
	}
	for (int i = 0; i < num.size(); i++)
	{
		answer += num[i];
	}

	cout << answer;

	return 0;
}