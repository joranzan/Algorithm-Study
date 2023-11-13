#include<iostream>
#include<vector>

using namespace std;

//NxN 체스판
// 흰색, 빨간색, 파란색
//
 
//말 (개수 : K개) 1~k번
//1) 원판 모양
//2) 하나의 말 위에 다른 말 올리기 가능
//3) 상하좌우(이동방향 주어짐)


//이동 (다음칸)
//1. 흰색 칸의 경우
	//1) 일단 이동
	//2) 이미 말 존재 -> 가장 위에 올림
	//3) 위에 있는 말 모두 이동

//2. 빨간색 경우
	//1) 빨간색 칸 이동 (모든 말 같이)
	//2) 쌓은 순서 반대로 바꿈 (이동한 애들만)
	
//3. 파란색 경우 (==맵 벗어난 경우)
	//1) A번 말의 이동 방향 반대
	//2) 또 파란색 경우 이동 X
	//3) 이동


//턴 1번 : 1번부터 K번 말 이동 
//만약 4개 이상 쌓이면 그냥 종료


struct Info {
	int row;
	int col;
	int dir;
};


void input();


const int dr[5] = { 0,0,0,-1,1 };
const int dc[5] = { 0,1,-1,0,0 };
const int Oppdir[5] = { 0,2,1,4,3 };

int N, K;
int Map[13][13] = { 0, };
Info Horse[10];   //현재 N번 말의 위치 저장
vector<int> StackedMap[13][13];  //말 쌓인 정보

bool Exit = false;

void White(int num) {
	//1. 흰색 칸의 경우
	//1) 일단 이동
	//2) 이미 말 존재 -> 가장 위에 올림
	//3) 위에 있는 말 모두 이동
	int nowRow = Horse[num].row;
	int nowCol = Horse[num].col;
	int nowDir = Horse[num].dir;
	int nextRow = nowRow + dr[nowDir];
	int nextCol = nowCol + dc[nowDir];

	vector<int> temp;

	while (1) {
		temp.push_back(StackedMap[nowRow][nowCol].back());
		StackedMap[nowRow][nowCol].pop_back();
		if (temp.back() == num) break;
	}

	for (int i = temp.size()-1; i >=0; i--) {
		Horse[temp[i]].row = nextRow;
		Horse[temp[i]].col = nextCol;
		StackedMap[nextRow][nextCol].push_back(temp[i]);
	}

	if (StackedMap[nextRow][nextCol].size() >= 4) Exit = true;

}

void Red(int num) {
	//2. 빨간색 경우
	//1) 빨간색 칸 이동 (모든 말 같이)
	//2) 쌓은 순서 반대로 바꿈 (이동한 애들만)

	int nowRow = Horse[num].row;
	int nowCol = Horse[num].col;
	int nowDir = Horse[num].dir;
	int nextRow = nowRow + dr[nowDir];
	int nextCol = nowCol + dc[nowDir];

	vector<int> temp;
	while (1) {
		temp.push_back(StackedMap[nowRow][nowCol].back());
		StackedMap[nowRow][nowCol].pop_back();
		if (temp.back() == num) break;
	}

	for (int i = 0; i <temp.size(); i++) {
		Horse[temp[i]].row = nextRow;
		Horse[temp[i]].col = nextCol;
		StackedMap[nextRow][nextCol].push_back(temp[i]);
	}

	if (StackedMap[nextRow][nextCol].size() >= 4) Exit = true;

}

void Blue(int num) {
	//3. 파란색 경우 (==맵 벗어난 경우)
	//1) A번 말의 이동 방향 반대
	//2) 또 파란색 경우 이동 X
	//3) 이동

	int nowDir = Horse[num].dir;
	nowDir = Oppdir[nowDir];
	Horse[num].dir = nowDir;

	int nowRow = Horse[num].row;
	int nowCol = Horse[num].col;

	int nextRow = nowRow + dr[nowDir];
	int nextCol = nowCol + dc[nowDir];
	
	if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) return;
	if (Map[nextRow][nextCol] == 2) return;

	vector<int> temp;
	while (1) {
		temp.push_back(StackedMap[nowRow][nowCol].back());
		StackedMap[nowRow][nowCol].pop_back();
		if (temp.back() == num) break;
	}

	for (int i = temp.size() - 1; i >= 0; i--) {
		Horse[temp[i]].row = nextRow;
		Horse[temp[i]].col = nextCol;
		StackedMap[nextRow][nextCol].push_back(temp[i]);
	}

	if (StackedMap[nextRow][nextCol].size() >= 4) Exit = true;


}




void solution() {


	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= K; j++) {  //1 ~ K번까지
			if (i == 7) {
				int debugging = -1;
			}
			int nowRow = Horse[j].row;
			int nowCol = Horse[j].col;
			int nowDir = Horse[j].dir;

			int nextRow = nowRow + dr[nowDir];
			int nextCol = nowCol + dc[nowDir];


			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) {
				Blue(j);
			}
			else if (Map[nextRow][nextCol] == 0) {
				White(j);
			}
			else if (Map[nextRow][nextCol] == 1) {
				Red(j);
			}
			else if (Map[nextRow][nextCol] == 2) {
				Blue(j);
			}

			if (Exit) {
				cout << i;
				return;
			}

		}
	}
	cout << "-1";
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}


void input() {
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		int r, c, d;
		cin >> r >> c >> d;
		Horse[i] = { r,c,d };
		StackedMap[r][c].push_back(i);

	}

}


// 턴 반복문
// 흰색
// 빨간색
// -> 
// 파란색
