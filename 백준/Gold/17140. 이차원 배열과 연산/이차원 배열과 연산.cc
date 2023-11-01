#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//배열 3x3 (인덱스 1부터 시작)
//1초 지날때마다 연산 적용

//R연산 (행의 개수 >= 열의 개수) : 모든 행에 대해서 정렬 수행 
//C연산 (행의 개수 < 열의 개수) : 모든 열에 대해서 정렬

//정렬하기 위해서 각각의 수가 몇번 나왔는지 알아야함
//정렬 기준 (0은 무시)
	// 등장횟수 커지는 순
	// 수가 커지는 순
//다시 넣을 때 : 수 / 등장횟수 모두 넣음

//100개 넘어가면 나머지 제외

//목표 : A[r][c] =k 일때까지 몇초

struct rule {
	int value;
	int cnt;

	bool operator<(rule next) const {
		if (cnt < next.cnt) return true;
		else if (cnt > next.cnt) return false;
		else {
			if (value < next.value) return true;
			else if (value > next.value) return false;
			else return false;
		}
	}
};

int Board[100][100] = { 0,0 }; //99까지만 가능

int R, C, K;
int nowRowSize = 3;  //하나의 행의 크기
int nowColSize = 3;  //하나의 열의 크기

void RSort() {

	int max_index = 0;

	for (int r = 0; r < nowRowSize; r++) {
		int DAT[101] = { 0, };
		vector<rule> temp;

		for (int c = 0; c < 100; c++) {
			if (Board[r][c] == 0) continue;
			DAT[Board[r][c]]++;
			Board[r][c] = 0;
		}

		for (int j = 1; j <= 100; j++) {
			if (DAT[j] == 0) continue;
			temp.push_back({ j,DAT[j] });
		}

		sort(temp.begin(), temp.end());

		int index = 0;
		for (int j = 0; j < temp.size(); j++) {
			Board[r][index] = temp[j].value;
			index++;
			if (index >= 100) break;
			Board[r][index] = temp[j].cnt;
			index++;
			if (index >= 100) break;
		}
		max_index = max(max_index, index);
	}
	nowColSize = max_index;
}

void CSort() {

	int max_index = 0;

	for (int c = 0; c < nowColSize; c++) {
		int DAT[101] = { 0, };
		vector<rule> temp;

		for (int r = 0; r < 100; r++) {
			if (Board[r][c] == 0) continue;
			DAT[Board[r][c]]++;
			Board[r][c] = 0;
		}

		for (int j = 1; j <= 100; j++) {
			if (DAT[j] == 0) continue;
			temp.push_back({ j,DAT[j] });
		}

		sort(temp.begin(), temp.end());

		int index = 0;
		for (int j = 0; j < temp.size(); j++) {
			Board[index][c] = temp[j].value;
			index++;
			if (index >= 100) break;
			Board[index][c] = temp[j].cnt;
			index++;
			if (index >= 100) break;
		}
		max_index = max(max_index, index);
	}
	nowRowSize = max_index;
}


void input() {
	cin >> R >> C >> K;
	R -= 1;
	C -= 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin>>Board[i][j];
		}
	}
}
int solution() {


	if (Board[R][C] == K) {
		return 0;
	}

	for (int time = 1; time <= 100; time++) {

		//조건 만족하면 time 출력 후 탈출


		if (nowRowSize >= nowColSize) {
			RSort();
		}
		else if (nowRowSize < nowColSize) {
			CSort();
		}

		//조건 만족하면 time 출력 후 탈출
		if (Board[R][C] == K) {
			return time;
		}

	}

	//조건 만족 못했으면 -1
	return -1;
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	cout << solution();


	return 0;
}