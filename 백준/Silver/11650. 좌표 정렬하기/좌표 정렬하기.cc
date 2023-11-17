#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct pos {
	int row;
	int col;

	bool operator<(pos next) const {
		if (row < next.row) return true;
		else if (row > next.row) return false;
		else {
			if (col < next.col) return true;
			else return false;
		}
	}
};

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	vector<pos> v;

	for (int i = 0; i < N; i++) {
		int r, c;
		cin >> r >> c;
		v.push_back({ r,c });
	}

	sort(v.begin(), v.end());

	for (int i = 0; i < N; i++) cout << v[i].row << " " << v[i].col << "\n";


	return 0;
}