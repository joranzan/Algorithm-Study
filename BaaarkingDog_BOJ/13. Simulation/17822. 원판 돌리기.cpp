#include<iostream>
#include<vector>

using namespace std;

//문제 분석
//반지름 : i -> i번째 원판

//i번째 원판 j번째 수 : i,j

//조건
//(i, 1)은 (i, 2), (i, M)과 인접
//(i, M)은 (i, M-1), (i, 1)과 인접
//(i, j)는 (i, j-1), (i, j+1)과 인접 (2 ≤ j ≤ M-1)
//(1, j)는 (2, j)와 인접
//(N, j)는 (N-1, j)와 인접
//(i, j)는 (i-1, j), (i+1, j)와 인접 (2 ≤ i ≤ N-1)

//회전 
//1) 독립적
//2) 수의 위치가 기준
//3) 회전 후 수의 위치는 회전 전 과 동일



//회전 방법 (x,d,k)
//1. 번호가 x의 배수인 원판을 d(0:시계, 1:반시계)방향으로 k칸 회전(%4) 
//2. 원판에 수가 남아있으면 인접하면서 수가 같은 것 모두 찾음
	//1) 인접하는 같은 수 있는 경우 : 인접하면서 같은수 모두 지움
    //2) 없는 경우 : 원판에 적힌 수의 평균 (큰 : -  작: +)

struct pos {
	int row;
	int col;
};

int N, M, T;
int Circle[51][51] = { 0, }; //NxM
vector<pos> v;

void Rotation(int num, int dir, int k) { //num 원을 dir방향으로 k만큼
	if (dir == 1) {//반시계
		k = M - k;
	}

	//시계방향 Rotation
	int temp[51] = { 0, };

	for (int i = 1; i <= M; i++) {  //4
		int next_index = i + k;
		if (next_index > M) {
			next_index -= M;
		}
		temp[next_index] = Circle[num][i];
	}
	int sum = 0;
	int cnt = 0;
	for (int i = 1; i <= M; i++) {
		Circle[num][i] = temp[i];
		if (Circle[num][i] == -1) continue;
		sum += Circle[num][i];
		cnt++;
	}

}

double findAverage() {

	double cnt = 0;
	double sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] == -1) continue;
			sum += Circle[i][j];
			cnt++;
		}
	}

	return sum / cnt;
}

void simulation() {

	

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] == -1) continue;

			int nowNum = Circle[i][j];
			int next_top = i + 1;
			int next_bottom = i - 1;
			int next_cw = j - 1;
			int next_c = j + 1;
			if (next_cw <= 0) next_cw = M;
			if (next_c > M) next_c = 1;


			if (next_top <= N&&Circle[next_top][j]!=-1) {
				if (nowNum == Circle[next_top][j]) {
					v.push_back({ next_top, j });
				}
			}
			if (next_bottom >= 1&& Circle[next_bottom][j]!=-1) {
				if (nowNum == Circle[next_bottom][j]) {
					v.push_back({ next_bottom,j });
				}
			}

			if (nowNum == Circle[i][next_cw]&& Circle[i][next_cw]!=-1) {
				v.push_back({ i, next_cw });
			}
			if (nowNum == Circle[i][next_c]&& Circle[i][next_c]!=-1) {
				v.push_back({ i, next_c });
			}

		}
	}
}

int input() {

	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {

		for (int j = 1; j <= M; j++) {
			cin >> Circle[i][j];
		}
	}

	for (int t = 0; t < T; t++) {
		v.clear();
		int x, d, k;
		cin >> x >> d >> k; //x의 배수인 원판을 d 방향으로 k칸 회전
		k = k % M;
		//회전시키기
		if (k != 0) {   //돌리는 횟수
			for (int i = 1; i <= N; i++) {

				if (i % x == 0) {
					Rotation(i, d, k);
				}
			}
		}

		int debugging = -1;
		double avg = findAverage();

		//2. 원판에 수가 남아있으면 인접하면서 수가 같은 것 모두 찾음

		simulation();

		if (v.size() == 0) {
			//인접하는 경우 없으면
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if (Circle[i][j] == -1) continue;
					if (Circle[i][j] > avg) Circle[i][j]--;
					else if (Circle[i][j] < avg) Circle[i][j]++;
				}
			}
		}
		else {
			for (int i = 0; i < v.size(); i++) {
				if (Circle[v[i].row][v[i].col] == -1) continue;
				Circle[v[i].row][v[i].col] = -1;
			}
		}

		int debugging2 = -1;
	}

	

	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] == -1) continue;
			sum += Circle[i][j];
		}
	}
	return sum;

}




int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cout << input();


	return 0;
}