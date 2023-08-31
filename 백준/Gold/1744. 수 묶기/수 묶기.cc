#include<iostream>
#include<queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;
	cin >> N;
	priority_queue<int, vector<int>, greater<>> Minus_Q;  //음수는 오름차순
	priority_queue<int> Plus_Q; //양수는 내림차순
	int zero_num = 0;
	int one_num = 0;
	int temp = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		if (temp == 0) zero_num++;
		else if (temp == 1) one_num++;
		else if (temp < 0) Minus_Q.push(temp);
		else Plus_Q.push(temp);
	}

	int data1 = 0;
	int data2 = 0;
	int answer = 0;

	while (Plus_Q.size() >= 2)
	{
		data1 = Plus_Q.top();
		Plus_Q.pop();
		data2 = Plus_Q.top();
		Plus_Q.pop();
		answer += (data1 * data2);
	}
	if (!Plus_Q.empty())
	{
		data1 = Plus_Q.top();
		Plus_Q.pop();
		answer += data1;
	}

	while (Minus_Q.size() >= 2)
	{
		data1 = Minus_Q.top();
		Minus_Q.pop();
		data2 = Minus_Q.top();
		Minus_Q.pop();
		answer += (data1 * data2);
	}
	if (!Minus_Q.empty())
	{
		data1 = Minus_Q.top();
		Minus_Q.pop();
		if (zero_num == 0)
		{
			answer += data1;
		}
	}

	answer += one_num;

	cout << answer << "\n";
	return 0;
}