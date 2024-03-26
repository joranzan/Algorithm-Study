#include<iostream>


using namespace std;

int Board[1001][1001] = { 0, };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N, M;
	cin >> N >> M;
	int Answer = 0;
	for (int r = 0; r < N; r++) {
		string s;
		cin >> s;
		for (int c = 0; c < M; c++) {
			Board[r][c] = s[c]-'0';
			if (Board[r][c] == 0) continue;
			int nextdiagRow = r - 1;
			int nextdiagCol = c - 1;
			int leftRow = r;
			int leftCol = c - 1;
			int upRow = r - 1;
			int upCol = c;
			
			if (nextdiagRow < 0 || nextdiagCol < 0) {
				Answer = max(Board[r][c], Answer);
				continue;
			}
			int value = min(Board[nextdiagRow][nextdiagCol], Board[leftRow][leftCol]);
			value = min(value, Board[upRow][upCol]);
			Board[r][c] = value + 1;
			Answer = max(Board[r][c], Answer);
		}
	}

	cout << Answer * Answer;

	return 0;
}

/*
0100
0111
1110
0010

0 1 0 0
0 1 1 1
1 1 1 0
0 0 1 0



*/

/*
4 5
11111
11111
11111
11110
*/