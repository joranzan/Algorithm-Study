#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//문제 분석( TC당 500만)
//NxN 맵 (숫자: 지형의 높이)
// 최대한 긴 등산로
//
// 
// 규칙
// 가장 높은 봉우리 시작
// 상하좌우
// start의 높이 > next의 높이 (같아도 안됨) 
// 딱 한곳 정해서 K깊이 만큼 깎는 공사 가능


//제약 조건
//가장 높은 봉우리 최대 5개

struct pos {
	int row;
	int col;
};

int N, K;
int Map[8][8] = { 0, };
vector<pair<int, int>> Highest;


void init() {
	N = K = 0;
	Highest.clear();
}

void input() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
		}
	}
}

int findMax() {
	int max_num = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			max_num = max(max_num, Map[i][j]);
		}
	}
	return max_num;
}

int BFS() {
	int ret = 0;
	
	
	//높은 봉우리마다 BFS
	for (int mountain = 0; mountain < Highest.size(); mountain++) {

		int start_r = Highest[mountain].first;
		int start_c = Highest[mountain].second;

		const int dr[4] = { -1,1,0,0 };
		const int dc[4] = { 0,0,-1,1 };

		queue<pos> q;
		int Distance[8][8] = { 0, };

		q.push({ start_r,start_c });
		Distance[start_r][start_c] = 1;

		while (!q.empty()) {

			pos Now = q.front();
			q.pop();

			int now_r = Now.row;
			int now_c = Now.col;

			for (int dir = 0; dir < 4; dir++) {
				int next_r = now_r + dr[dir];
				int next_c = now_c + dc[dir];
				if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= N) continue;
				if (Map[next_r][next_c] >= Map[now_r][now_c]) continue;
				if (Distance[next_r][next_c] >= Distance[now_r][now_c] + 1) continue;
				Distance[next_r][next_c] = Distance[now_r][now_c] + 1;
				q.push({ next_r,next_c });
			}

		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				ret = max(ret, Distance[i][j]);
				//디버깅 코드
				if (Distance[i][j] == 5)
				{
					int debugging = -1;
				}
			}
		}
	}
	
	
	int debugging = -1;



	return ret;
}



int solution() {
	int Answer = 1;
	int max_num = findMax();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] == max_num) {
				Highest.push_back({ i,j });
			}
		}
	}
	
	for (int k = 0; k <= K; k++) {

		for (int i = 0; i < N; i++) {  //각 좌표마다 땅 파기
			for (int j = 0; j < N; j++) {

				//디버깅용
				if (i == 2 && j == 3 && k == 1) 
					int debugging = -1;
				//
				int temp = Map[i][j];
				Map[i][j] -= k;
				if (Map[i][j] < 0) {
					int debugging = -1;
				}
				Answer = max(Answer, BFS());
				Map[i][j] = temp;
			}
		}
	}
	return Answer;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {

		init();
		input();

		cout << "#" << test << " " << solution() << "\n";

	}

	return 0;
}

//깎는 방법 
//좌표 64개 * 깎기(5) = 320번 BFS돌려야함
//BFS 연산: 10000이하여야함 -> 가능할듯?   