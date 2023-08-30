#include<iostream>
#include<vector>

using namespace std;


//문제 분석
//NxN 도시  마름모 모양 제공(중앙 포함 K만큼 뻗어나감)
//운영비용: K^2 + (k-1)^2   
//도시 벗어난 경우에도 운영비용은 그대로

//집이 지불할 수 있는 비용: M

//목표: "손해보지않으며" "가장 많은 집" 제공하는 서비스영역 -> 이때 제공받는 집의 수

struct pos {
	int row, col;
};

int N, M;
int Answer = 0;
vector<pos> House;  //집 위치 정보

void init() {
	N = M = 0;
	Answer = 0;
	House.clear();
}
void input() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int temp;
			cin >> temp;
			if (temp == 1) {
				House.push_back({ i,j });
			}
		}
	}
}

void check(int row, int col) {

	int ret = 0;

	for (int k = 1; k <= N+1; k++) {

		int cost = k * k + (k - 1) * (k - 1);
		int cnt = 0; //범위 내 집 개수

		for (int i = 0; i < House.size(); i++) {
			int house_row = House[i].row;
			int house_col = House[i].col;

			int dist = abs(house_row - row) + abs(house_col - col);

			//서비스 거리 안닿는 경우
			if (dist > k-1 ) continue;
			//이미 손해보는 경우 더이상 계산 안함
			cnt++;
		}
		//범위내 집 개수 * M - cost >=0   (손해 안봄)
		int margin = cnt * M - cost;
		if (margin < 0) continue;
		//Answer와 비교
		Answer = max(Answer, cnt);
	}
}

void solution() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			check(i, j);
		}
	}
}


int main() {


	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//freopen_s(new FILE*, "input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int test = 1; test <= T; test++) {
		init();
		input();
		solution();
		cout << "#" << test << " " << Answer << "\n";
	}


}

//설계

//가능한 범위 찾기 -> 그 안의 집 개수 파악
//(M*집의 수) - (운영비용) >= 0 이여야 서비스 제공 가능


