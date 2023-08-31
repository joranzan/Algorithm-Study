#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	long long A, B;
	cin >> A >> B;

	if (A < B)
	{
		swap(A, B);
	}

	long long temp_A = A;
	long long temp_B = B;
	long long residue;
	while (1)
	{
		residue = temp_A % temp_B;
		if (residue == 0) break;
		temp_A = temp_B;
		temp_B = residue;
	}

	for (long long i = 0; i < temp_B; i++)
	{
		cout << "1";
	}

	return 0;
}