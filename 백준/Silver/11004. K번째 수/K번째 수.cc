#include<iostream>
#include<vector>

using namespace std;

void QuickSort(vector<int>& Num, int S, int E, int K);
int partition(vector<int>& Num, int S, int E);
void swap(vector<int>& Num, int i, int j);




int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, K;
	cin >> N >> K;
	vector<int> Num(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> Num[i];
	}

	QuickSort(Num, 0, Num.size() - 1, K-1);
	cout << Num[K - 1];
	
    
}

void QuickSort(vector<int>& Num, int S, int E, int K)
{
	int pivot = partition(Num, S, E);

	if (pivot == K) 
        return;
	else if (pivot > K)
	{
		QuickSort(Num, S, pivot - 1, K);
	}
	else
	{
		QuickSort(Num, pivot + 1, E, K);
	}	
}
int partition(vector<int>& Num, int S, int E)
{
	if (S + 1 == E)
	{
		if (Num[S] > Num[E])
		{
			swap(Num, S, E);
		}
		return E; // 왜 S말고 E????????????????
	}

	int M = (S + E) / 2;
	swap(Num, S, M);
    int pivot = Num[S];
	int i = S + 1;
	int j = E;

	while (i <= j)
	{
		while (pivot < Num[j] && j>0)
		{
			j--;
		}
		while (pivot > Num[i] && i < Num.size() - 1)
		{
			i++;
		}
		if (i <= j)
		{
			swap(Num, i++, j--);
		}
	}
	Num[S] = Num[j];
	Num[j] = pivot;
	return j;
}
void swap(vector<int>& Num, int i, int j)  //swap 할 때는 참조로 ~~~
{
	int temp = Num[i];
	Num[i] = Num[j];
	Num[j] = temp;
}