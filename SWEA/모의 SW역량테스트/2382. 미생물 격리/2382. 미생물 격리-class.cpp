#include<iostream>
#include<vector>

using namespace std;

/*
7 2 9
1 1 7 1
2 1 7 1
5 1 5 4
3 2 8 4
4 3 14 1
3 4 3 3
1 5 8 2
3 5 100 1
5 5 1 1
*/

struct MAP {
	int colonyNum;  //지금 해당 셀을 차지한 군집 번호
	int cnt;  //해당 셀에 모인 미생물 총 합
};

struct Colony {
	int row, col, cnt, dir;
};

int N, M, K;
vector<Colony> colony;
vector<int> alive; //현재 살아있는 군집 목록

void init() {
	N = M = K = 0;
	colony.clear();
	alive.clear();
}
void input() {
	cin >> N >> M >> K;
	colony.push_back({ 0,0,0,0 });  //없는 군집이란 의미
	for (int i = 1; i <= K; i++) {
		int row, col, cnt, dir;
		cin >> row >> col >> cnt >> dir;
		colony.push_back({ row,col,cnt,dir });  //실제 존재하는 군집 1번부터
		alive.push_back(i); //초기엔 살아있다고 등록
	}
}
void simulation() {
	for (int time = 0; time < M; time++) { 
		MAP Map[110][100] = { 0, };   //colonynum : 초기값 0 (군집이 없다)

		const int dr[] = { 0,-1,1,0,0 };
		const int dc[] = { 0,0,0,-1,1 };
		for (int i = 0; i < alive.size(); i++) {
			int nowColonyNum = alive[i];
			Colony nowColony = colony[nowColonyNum];
			nowColony.row += dr[nowColony.dir];
			nowColony.col += dc[nowColony.dir];

			if (nowColony.row <= 0 || nowColony.col <= 0 || nowColony.row >= N - 1 || nowColony.col >= N - 1)
			{
				nowColony.cnt /= 2;
				nowColony.dir += 1;

				if (nowColony.dir % 2 == 1) nowColony.dir -= 2;
			}
			//가장자리에서 개수 처리

			//합치기 (Map에 등록)
			int maxColonyNum = Map[nowColony.row][nowColony.col].colonyNum;  //현재 좌표의 가장 많았던 군집
			Colony maxColony = colony[maxColonyNum];
			if (maxColony.cnt < nowColony.cnt) {  //내가 살고 기존은 삭제
				Map[nowColony.row][nowColony.col] = { nowColonyNum,
					Map[nowColony.row][nowColony.col].cnt +nowColony.cnt
				};
				colony[maxColonyNum].cnt = 0; //기존 삭제
			}
			else {   //내가 죽고 기존이 산다
				Map[nowColony.row][nowColony.col] = { maxColonyNum,
					Map[nowColony.row][nowColony.col].cnt + nowColony.cnt
				};
				nowColony.cnt = 0;  //내가 삭제
			}
			colony[nowColonyNum] = nowColony;  //임시로 다뤘던 nowColony 정보를 원본 갱신
		}
		//다음 턴 준비
		vector<int> next_alive;  //다음턴 살아있는 목록
		for (int i = 0; i < alive.size(); i++) {
			int nowColonyNum = alive[i];
			Colony nowColony = colony[nowColonyNum];
			if (nowColony.cnt == 0) continue;
			
			colony[nowColonyNum].cnt = Map[nowColony.row][nowColony.col].cnt;
			next_alive.push_back(nowColonyNum);
		}

		alive = next_alive;
	}
}
int solution() {

	simulation();
	int ret = 0;
	for (int i = 0; i < alive.size(); i++) {
		ret += colony[alive[i]].cnt;
	}
	return ret;
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		init();
		input();
		int answer = solution();
		cout << "#" << test << " " << answer << "\n";
	}

	return 0;
}