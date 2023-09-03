#include<iostream>
#include<vector>
#define MAX 15

int N;
using namespace std;
int answer = 0;
int col[MAX] = {};


//수직, 대각선 검사
bool is_Available(int row, int column)
{
	for (int i = 0; i < row; i++) 
	{
		if ((col[i] == column) || (abs(col[i] - column) == abs(i - row)))
		{
			return false;
		}
	}
	return true;
}

void DFS(int current_row)
{
	if (current_row == N)
	{
		answer++;
		return;
	}
	
	
	for (int current_column = 0; current_column < N; current_column++)
	{
		if (is_Available(current_row, current_column))
		{
			col[current_row] = current_column;
			DFS(current_row + 1);
		}
	}
}

void Solve_Nqueen()
{
	DFS(0);
	cout << answer;
}


int main()
{
	cin >> N;
	Solve_Nqueen();

	return 0;
}