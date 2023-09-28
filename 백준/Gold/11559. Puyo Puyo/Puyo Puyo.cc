#include<iostream>
#include<queue>
#include<vector>

using namespace std;

struct pos {
	int row;
	int col;
};

char Map[12][6];
bool Visited[12][6] = { false, };
vector<pos> v;
int Answer = 0;

//떨어뜨리는 과정
void drop() {

	for (int col = 0; col < 6; col++) {
		vector<char> temp;
		for (int row = 11; row >= 0; row--) {
			if (Map[row][col] == '.') continue;
			temp.push_back(Map[row][col]);
			Map[row][col] = '.';
		}
		for (int i = 11; i >= 0; i--) {
			if (11 - i >= temp.size()) {
				break;
			}
			else {
				Map[i][col] = temp[11 - i];
			}
		}
	}
}

//인접한 애들 몇개인지 체크
void check(int startRow, int startCol) {

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	int cnt = 1;

	queue<pos> q;
	
	char color = Map[startRow][startCol];
	q.push({ startRow, startCol });
	v.push_back({ startRow, startCol });
	Visited[startRow][startCol] = true;

	while (!q.empty()) {

		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextRow = nowRow + dr[i];
			int nextCol = nowCol + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= 12 || nextCol >= 6) continue;
			if (Map[nextRow][nextCol] != color) continue;
			if (Visited[nextRow][nextCol]) continue;
			Visited[nextRow][nextCol] = true;
			q.push({ nextRow, nextCol });
			v.push_back({ nextRow, nextCol });
		}

	}
}

//제거하는 과정
bool explosion() {

	bool flag = false;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (Map[i][j] == '.') continue;
			if (Visited[i][j]) continue;
			check(i, j);
			if (v.size() >= 4) {
				flag = true;
				for (int k = 0; k < v.size(); k++) {
					Map[v[k].row][v[k].col] = '.';
				}
			}
			v.clear();
		}
	}

	return flag;
}


void solution() {


	while (1) {
		drop();

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				Visited[i][j] = false;
			}
		}

		bool exploded = explosion();
		if (exploded) Answer++;
		else break;
	}
	//drop
	//Visited 초기화
	//explosion
	cout << Answer;

}


int main() {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> Map[i][j];
		}
	}

	solution();

	return 0;
}