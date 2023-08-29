//선수 5 명을 선발할 수 없는 경우에는 "PREDAJA" (따옴표 없이)를 출력
//성의 첫 글자를 사전순으로 공백없이 모두 출력한다.

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

int main()
{
	int N;
	cin >> N;
	map<char,int> num;
	vector<char> result;
	bool found = false;
	for (int i = 0; i < N; i++)
	{
		string name;
		cin >> name;
		char c = name[0];
		if (num.find(c) == num.end())
			num.insert(make_pair(c, 1));
		else
			num[c]++;

		int count = num[c];
		if (num[c]==5)
		{
			found = true;
			result.push_back(c);
		}		
	}
	if (!found) 
		cout << "PREDAJA" << "\n";
	else
	{
		sort(result.begin(), result.end());
		for (int i = 0; i < result.size(); i++)
		{
			cout << result[i];
		}
	}

	return 0;
}