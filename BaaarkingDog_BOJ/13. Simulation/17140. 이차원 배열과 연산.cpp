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


	for (int i = 0; i < nowRowSize; i++) {

		int DAT[101] = { 0, };
		vector<rule> temp;

		for (int j = 0; j < 100; j++) {

			int nowNum = Board[i][j];
			if (nowNum == 0) continue;
			Board[i][j] = 0;
			DAT[nowNum]++;
		}

		for (int j = 1; j <= 100; j++) {
			if (DAT[j] <= 0) continue;
			temp.push_back({ j,DAT[j] });
		}

		sort(temp.begin(), temp.end());
		Board[i].clear();
		for (int j = 0; j < 100; j++) {
			if (j >= temp.size()) break;
			Board[i].push_back(temp[j].value);
			if (Board[i].size() >= 100) break;
			Board[i].push_back(temp[j].cnt);
			if (Board[i].size() >= 100) break;
		}
		int tempsize = Board[i].size();
		nowRowSize = max(tempsize, nowRowSize);
	}
}

void CSort() {



}


void input() {
	cin >> R >> C >> K;
	R -= 1;
	C -= 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int temp;
			cin >> temp;
			Board[i].push_back(temp);
		}
	}
}
void solution() {

	for (int time = 1; time <= 100; time++) {

		int rowSize = Board[0].size(); //하나의 행의 크기
		int colSize = Board.size(); //하나의 열의 크기


		if (rowSize >= colSize) {
			RSort();
		}
		else if (rowSize < colSize) {
			CSort();
		}

		//조건 만족하면 time 출력 후 탈출
	}

	//조건 만족 못했으면 -1
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();


	return 0;
}