#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

static vector<int> Num;
bool isSearched(int i, int j, int search);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	vector<int> FindNum;
	cin >> N;
	Num = vector<int>(N, 0);
	
	for (int i = 0; i < N; i++)
	{
		cin >> Num[i];
	}
	sort(Num.begin(), Num.end());
	cin >> M;
	FindNum = vector<int>(M, 0);
	for (int i = 0; i < M; i++)
	{
		int search_num;
		cin >> search_num;
		if (isSearched(0, N - 1, search_num)) cout << "1\n";
		else cout << "0\n";
	}
	
	return 0;
}

bool isSearched(int i, int j, int search)
{
	if (j - i < 1)
	{
		if (Num[i] == search) return true;
		else return false;
	}

	int middle = (i + j) / 2;
	if (Num[middle] == search) return true;
	else if (Num[middle] > search)
	{
		return isSearched(i, middle - 1, search);
	}
	else
	{
		return isSearched(middle + 1, j, search);
	}
}