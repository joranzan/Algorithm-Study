#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<deque>
using namespace std;

//문제 분석
//NxN 땅 (1,1)부터 시작

//양분 조사 로봇
//1x1칸에 들어있는 양분 조사
//모든 칸에 대해서 조사
//초기 : 5만큼 들어있음

//나무 제테크(묘묙을 키워서 팔아재끼는 재테크)
//M개의 나무 구매
//한칸에 여러개 나무 심을 수 있음

//재테크 과정



//2. 여름
//죽은 나무 양분으로 바뀜
//죽은 나무의 나이 / 2 만큼 양분 추가

//3. 가을
//번식
//조건 : 나무 나이 5의 배수
//인접한 8칸에 나무 생김 (땅 벗어나지 않는 곳만)

//4. 겨울
//로봇이 양분 추가함 A[r][c] : 입력


//목표: K년 뒤 살아있는 나무의 개수

struct tree {
	int row;
	int col;
	int age;
	bool alive;

	bool operator<(tree next) const {
		if (age < next.age) return false;
		if (age > next.age) return true;

		return false;
	}
};

int N, M, K;
int A[11][11] = { 0, };
int Map[11][11] = { 0, };
deque<int> Tree[11][11];
vector<tree> dead;   //죽은 나무들 모음
int Ans = 0;

void spring() {
	//1. 봄
	//나무 : 자신의 나이만큼 양분 섭취 후 나이++
	//(여러개 나무일 때 나이가 어린나무부터 양분 먹음)
	//땅에 양분 < 나무 나이 -> 죽음
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int last = Tree[i][j].size();
			for (int t = 0; t < Tree[i][j].size(); t++) {
				if (Map[i][j] < Tree[i][j][t]) {
					last = t;
					break;
				}
				Map[i][j] -= Tree[i][j][t];
				Tree[i][j][t]++;
				
			}
			int deadNum = 0;
			int T = Tree[i][j].size();
			for (int t = 0; t < T - last; t++) {
				if (Tree[i][j].size() == 0) continue;
				deadNum += (Tree[i][j][Tree[i][j].size() - 1] / 2);
				Tree[i][j].pop_back();
			}

			Map[i][j] += deadNum;
		}
	}
}

void summer() {
	//2. 여름
	//죽은 나무 양분으로 바뀜
	//죽은 나무의 나이 / 2 만큼 양분 추가
	for (int i = 0; i < dead.size(); i++) {
		tree now = dead[i];
		Map[now.row][now.col] += (now.age / 2);
	}
}
void autumn() {
	//3. 가을
	//번식
	//조건 : 나무 나이 5의 배수
	//인접한 8칸에 나무 생김 (땅 벗어나지 않는 곳만)

	const int dr[8] = { -1,1,0,0,-1,-1,1,1 };
	const int dc[8] = { 0,0,-1,1,-1,1,-1,1 };

	vector<int> temp[11][11];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			
			for (int t = 0; t < Tree[i][j].size(); t++) {
				if (Tree[i][j][t] % 5 != 0) continue;
				for (int dir = 0; dir < 8; dir++) {
					int next_r = i + dr[dir];
					int next_c = j + dc[dir];
					if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) continue;
					tree next = { next_r, next_c , 1, true };
					temp[next_r][next_c].push_back(1);
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 0; k < temp[i][j].size(); k++) {
				Tree[i][j].push_front(temp[i][j][k]);
			}
		}
	}
}

void winter() {
	//4. 겨울
	//로봇이 양분 추가함 A[r][c] : 입력
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Map[i][j] += A[i][j];
		}
	}
}


void simulation() {

	spring();
	//summer();
	autumn();
	winter();
	
}

void init() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Map[i][j] = 5;
			sort(Tree[i][j].begin(), Tree[i][j].end());
		}
	}
}

void input() {
	//입력
	//N,M,K
	cin >> N >> M >> K;
	
	//A배열 (추가할 양분)
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	//x y,z : x(r) y(c) 나이
	for (int i = 0; i < M; i++) {
		int r, c, old;
		cin >> r >> c >> old;
		Tree[r][c].push_back(old);
	}

	init();
}

void solution() {

	for (int i = 1; i <= K; i++) {
		dead.clear();
		simulation();
	}

	//살아있는 나무 세서 출력하기
	Ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Ans += Tree[i][j].size();
		}
	}

	cout << Ans << "\n";

}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}