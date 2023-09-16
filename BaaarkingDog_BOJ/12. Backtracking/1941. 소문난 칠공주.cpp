#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

//25명 5x5 배열
// 이다솜파 변경 규칙
// 7명
// 가로세로 인접
// 반드시 이다솜일 필요없음
// 이다솜파가 4명이상!

struct pos {
	int row;
	int col;
};

char Map[5][5] = {};  //맵
vector<pos> Candi;    //후보군

int arr[25] = { 0 };   //조합을 위한 배열 (0: 7개)


bool check() {

	int numY = 0;
	int numS = 0;

	for (int i = 0; i < Candi.size(); i++) {
		int row = Candi[i].row;
		int col = Candi[i].col;

		if (Map[row][col] == 'Y') numY++;
		else if (Map[row][col] == 'S') numS++;

		if (numY > 3) return false;
	}
	return true;
}

bool Adjacent() {

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	bool Visited[5][5] = { false, };

	int nodeCnt = 0;
	queue<pos> q;
	q.push(Candi[0]);
	Visited[Candi[0].row][Candi[0].col] = true;

	while (!q.empty()) {

		nodeCnt++;

		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextRow = nowRow + dr[i];
			int nextCol = nowCol + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= 5 || nextCol >= 5) continue;
			if (arr[nextRow * 5 + nextCol] != 0) continue;
			if (Visited[nextRow][nextCol]) continue;
			Visited[nextRow][nextCol] = true;
			q.push({ nextRow,nextCol });
		}
	}
	
	if (nodeCnt == 7) return true;
	return false;
}


int solution() {

	int cnt = 0;

	do {
		for (int i = 0; i < 25; i++) {
			if (arr[i] == 0) {
				int row = i / 5;
				int col = i % 5;
				Candi.push_back({ row,col });
			}
		}
		if (check() && Adjacent()) cnt++;

		Candi.clear();


	} while (next_permutation(arr, arr + 25));

	return cnt;
}


int main() {

	for (int i = 7; i < 25; i++) {
		arr[i] = 1;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> Map[i][j];
		}
	}



	cout << solution();

	return 0;
}