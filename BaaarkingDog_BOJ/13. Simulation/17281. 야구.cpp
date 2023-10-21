#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

struct Info {
	int id;
	map<int, int> hit;  //뭐칠지
};

Info DAT[10];
int N;
int order[10];
int nowPlayer = 0;

int playStart() {
	int inning = 1;
	int score = 0;
	nowPlayer = 1;
	
	while (inning <= N) {
		int Base[4] = { 0, };
		int out = 0;
		while (out < 3) {

			int playerNum = order[nowPlayer];
			int batting = DAT[playerNum].hit[inning];
			
			if (batting > 0 && batting<=3) {
				//안타(1) : 타자와 모든 주자 1루 진루
				//2루타(2) : 2루 진루
				//3루타(3) : 3루 진루
				for (int i = 3; i >= 1; i--) {
					if (Base[i] == 0) continue;
					int nextBase = i + batting;
					if (nextBase >= 4) {
						Base[i] = 0;
						score++;
					}
					else {
						Base[nextBase] = Base[i];
						Base[i] = 0;
					}
				}
				Base[batting] = playerNum;
			}
			else if (batting == 4) {
				//홈런(4) : 모든 주자 홈
				int cnt = 0;
				for (int i = 1; i <= 3; i++) {
					if (Base[i] != 0) cnt++;
					Base[i] = 0;
				}
				score += (cnt + 1);
			}
			else if (batting == 0) {
				//아웃(0) : 모든 주자 그대로 , out 추가
				out++;
			}

			nowPlayer++;
			if (nowPlayer > 9) nowPlayer = 1;
		}
		inning++;
	}
	if (score == 48) {
		int debugging = -1;
	}
	if (score == 43) {
		int debugging = -1;
	}
	return score;
}

void input() {
	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= 9; j++) {
			int s;
			cin >> s;
			DAT[j].id = j;
			DAT[j].hit[i] = s;
		}
	}

	for (int i = 1; i <= 9; i++) {
		order[i] = i;
	}

}
void solution() {
	int Answer = 0;

	do {

		Answer = max(Answer, playStart());

	} while (next_permutation(order + 1, order + 10));

	cout << Answer << "\n";
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

//36만 가지

//문제분석
//N이닝
//1이닝 3아웃  -> 공수교대 & 이닝 끝

//경기 시작 전
//타순 정하기

//경기 도중
//타순 변경 금지 
//3out 안나면 다시 처음부터 순서 로테이션
//이전 경기 타순 이어서 진행

//1루 2루 3루  거쳐서 홈 도착 -> 1점

//안타(1) : 타자와 모든 주자 1루 진루
//2루타(2) :                 2루 진루
//3루타(3) :                 3루 진루
//홈런(4) : 모든 주자 홈
//아웃(5) : 모든 주자 그대로 , out 추가

//선수 정보 1번 ~ 9번
//가장 많은 득점을 하는 타순 구하기