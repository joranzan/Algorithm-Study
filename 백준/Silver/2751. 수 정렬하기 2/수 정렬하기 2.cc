#include<iostream>
#include<vector>

using namespace std;


void MergeSort(int s, int e);
static vector<int> Num;
static vector<int> temp;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;
	cin >> N;
	Num = vector<int>(N, 0);
	temp = vector<int>(N, 0);
	
	for (int i = 0; i < N; i++)
	{
		cin >> Num[i];
	}

	MergeSort(0, N - 1);

	for (int i = 0; i < N; i++)
	{
		cout << Num[i] << "\n";
	}

	return 0;
}

void MergeSort(int s, int e)
{
	if (e - s < 1)  //
	{
		return;
	}
	int start = s;
	int end = e;
	int middle = (s + e) / 2;

	MergeSort(start, middle);
	MergeSort(middle + 1, end);

	for (int i = start; i <= end; i++)
	{
		temp[i] = Num[i];
	}
	//index1: 앞 데이터 시작점, index2: 뒷 데이터 시작점
	int index1 = start;
	int index2 = middle + 1;
	int k = start;

	while (index1 <= middle && index2 <= end)
	{
		if (temp[index1] < temp[index2])
		{
			Num[k] = temp[index1];
			index1++;
		}
		else
		{
			Num[k] = temp[index2];
			index2++;
		}
		k++;
	}
	if (index1 > middle)
	{
		while (index2 <= end)
		{
			Num[k] = temp[index2];
			index2++;
			k++;
		}
	}
	else if (index2 > end)
	{
		while (index1 <= middle)
		{
			Num[k] = temp[index1];
			index1++;
			k++;
		}
	}
}