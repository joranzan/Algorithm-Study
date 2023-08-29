#include<iostream>
#include<map>
#include<vector>
#include<cstring>
#include<string>

using namespace std;

int main()
{
	int max = 0;
	vector<char> Answer;
	string mystr;
	bool same = false;
	map<int, int> num;
	cin >> mystr;
	for (int i = 0; i < mystr.length(); i++)
	{
		int c = mystr[i];
		if (c > 93) c -= 32;
		if (num.find(c) == num.end())
		{
			num.insert(make_pair(c, 1));
		}
		else
		{
			num[c]++;
		}
		if (num[c] > max) max = num[c];
	}
	auto iterator = num.begin();
	while (iterator != num.end())
	{
		if (iterator->second == max)
		{
			Answer.push_back(iterator->first);
		}
		if (Answer.size() > 1)
		{
			cout << "?\n";
			same = true;
			break;
		}
		iterator++;
	}
	if (!same)
	{
		cout << (Answer.front());
	}
	return 0;
}