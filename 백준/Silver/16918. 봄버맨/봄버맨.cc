#include<iostream>
#include<vector>


using namespace std;

struct pos {
	int row;
	int col;
};

const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

int R, C, N;
int Map[201][201] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> R >> C >> N;

	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			char temp;
			cin >> temp;
			if (temp == 'O') Map[r][c] = 2;
		}
	}
	N--;

	while(N){

		vector<pos> explode;

		
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				if (Map[r][c] == 0) Map[r][c] = 2;
				else Map[r][c]--;
			}
		}
		N--;
		if (N == 0) break;


		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				if (Map[r][c] == 1) explode.push_back({ r,c });
			}
		}
		

		for (int i = 0; i < explode.size(); i++) {
			int nowRow = explode[i].row;
			int nowCol = explode[i].col;
			Map[nowRow][nowCol] = 0;
			for (int dir = 0; dir < 4; dir++) {
				int nextRow = nowRow + dr[dir];
				int nextCol = nowCol + dc[dir];

				if (nextRow < 0 || nextCol < 0 || nextRow >= R || nextCol >= C) continue;
				Map[nextRow][nextCol] = 0;
			}
		}
		N--;
	}

	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (Map[r][c] == 0) cout << ".";
			else cout << "O";
		}
		cout << "\n";
	}

	return 0;
}