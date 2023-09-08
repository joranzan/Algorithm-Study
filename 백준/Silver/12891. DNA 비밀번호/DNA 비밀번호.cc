#include<iostream>
#include<vector>

using namespace std;

vector<int> Check_Num(vector<int> v, char c)
{
	switch (c)
	{
	case 'A':
	{
		v[0]++;
		break;
	}
	case 'C':
	{
		v[1]++;
		break;
	}
	case 'G':
	{
		v[2]++;
		break;
	}
	case 'T':
	{
		v[3]++;
		break;
	}
	}
	return v;
}

vector<int> Delete_Num(vector<int> v, char c)
{
	switch (c)
	{
	case 'A':
	{
		v[0]--;
		break;
	}
	case 'C':
	{
		v[1]--;
		break;
	}
	case 'G':
	{
		v[2]--;
		break;
	}
	case 'T':
	{
		v[3]--;
		break;
	}
	}
	return v;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	string DNA;
	int S, P;
	cin >> S >> P;
	cin >> DNA;

	vector<char> DNA_array(S, '0');
	vector<int> Rule(4, 0);   //ACGT
	int Answer = 0;
	
	for (int i = 0; i < S; i++)
	{
		DNA_array[i] = DNA[i];
	}
	for (int i = 0; i < 4; i++)
	{
		cin >> Rule[i];
	}

	bool password_OK = true;
	int start = 0;
	int end = start + P - 1;
	vector<int> check(4, 0);
	for (int i = 0; i < P; i++)
	{
		check = Check_Num(check, DNA_array[start + i]);
	}
	for (int i = 0; i < 4; i++)
	{
		if (Rule[i] > check[i])
		{
			password_OK = false;
			//break;
		}
	}
	if (password_OK) Answer++;

	start++; end++;

	while (end < S)
	{
		password_OK = true;
		check = Delete_Num(check, DNA_array[start - 1]);
		check = Check_Num(check, DNA_array[end]);
		for (int i = 0; i < 4; i++)
		{
			if (Rule[i] > check[i])
			{
				password_OK = false;
				//break;
			}
		}
		if (password_OK) Answer++;

		start++; end++;
	}

	cout << Answer << "\n";	

	return 0;
}
