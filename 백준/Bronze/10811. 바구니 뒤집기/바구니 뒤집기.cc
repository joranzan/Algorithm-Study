#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int arr[101] = { 0, };
	int N, M;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		arr[i] = i;
	}

	for (int q = 0; q < M; q++) {
		int i, j;
		cin >> i >> j;

		while (i < j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	for (int i = 1; i <= N; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}
































/*
using namespace std;

//문제 분석

//NxN 맵 (1x1)
//마법사 상어 :  ((N+1)/2, (N+1)/2)

//구슬 (1번 2번 3번) => 상어 있는 칸 제외
//같은 번호를 가진 구슬이 연속 -> 연속하는 구슬

//마법 시전
//1. d(방향 상하좌우 1234) s(거리) d방향으로 거리가 s이하인 모든 칸에 얼음 던짐
//2. 구슬 파괴 후 빈칸 됨 (빈칸 나타낼 숫자 정하기)
//3. 벽은 파괴 X

//구슬 이동
//1. 해당 칸의 번호보다 1 작은 칸이 빈칸인 경우
//2. 해당 칸의 구슬이 작은칸으로 이동

//구슬 폭발 (연속 구슬 4개 이상)
//1. 연속 구슬 폭발 -> 빈칸됨
//2. 구슬 다시 이동
//3. 이 과정을 구슬 폭발 없을 때 까지 반복
//**************터뜨릴수있는애들 모두 터뜨린후에 옮기기********

//구슬 변화
//1. 그룹 : 연속하는 구슬 
//2. 하나의 그룹 2개의 구슬로 변화 : { 그룹에 들어있는 구슬의 개수, 구슬의 번호}
//***구슬이 칸 넘어가면 사라짐


//목표 : 폭발 1구슬 개수 * 1 + 폭발2구슬 개수 *2 + 폭발3구슬 개수 *3


struct pos {
	int row;
	int col;
	int dir;
};

struct query {
	int d;
	int s;
};

int N, M;
int Map[50][50] = { 0, };
pos ID_Mapping[2500];
query Query[100];
const int dr[5] = { 0,-1,1,0,0 };
const int dc[5] = {0, 0, 0, -1, 1};


void Magic(int d, int s) {
	//마법 시전
	//1. d(방향 상하좌우 1234) s(거리) d방향으로 거리가 s이하인 모든 칸에 얼음 던짐
	//2. 구슬 파괴 후 빈칸 됨 (빈칸 나타낼 숫자 정하기 : 0)
	//3. 벽은 파괴 X
}

void Explosion() {
	vector<int> temp1;  
	queue<int> ReadyQ;
	//계속 폭발시키기
	pair<int, int> InsideCnt = {0,0}; //마지막 숫자, 개수

	for (int i = 1; i < N * N; i++) {
		int nowRow = ID_Mapping[i].row;
		int nowCol = ID_Mapping[i].col;
		if (Map[nowRow][nowCol] == 0) continue; //빈칸이면 Continue
		if (InsideCnt.first == 0 && InsideCnt.second == 0) {
			//첫번째면 그냥 넣고 Continue
			temp1.push_back(Map[nowRow][nowCol]);
			InsideCnt.first = Map[nowRow][nowCol];
			InsideCnt.second = 1;
			continue;
		}

		if (InsideCnt.first == Map[nowRow][nowCol]) {  //다음 칸에 연속이면
			//readyQ에 넣기
			ReadyQ.push(Map[nowRow][nowCol]);
			InsideCnt.second++;
		}
		else {  //다음칸 다른 구슬이면
			//1. cnt가 4이상이면 안넣기
			if (InsideCnt.second >= 4) {
				temp1.pop_back();
				ReadyQ = queue<int>();
			}
			//2. 아니면 다 vector에 넣어줌
			else {
				while (!ReadyQ.empty()) {
					temp1.push_back(ReadyQ.front());
					ReadyQ.pop();
				}
			}
			//InsideCnt 갱신
			InsideCnt.first = Map[nowRow][nowCol];
			InsideCnt.second = 1;
			temp1.push_back(Map[nowRow][nowCol]);
		}
	}

	//다 돌고나서 남아있는 애들
	if (!ReadyQ.empty()) {
		if (InsideCnt.second >= 4) temp1.pop_back();
		else {
			while (!ReadyQ.empty()) {
				temp1.push_back(ReadyQ.front());
				ReadyQ.pop();
			}
		}
	}

	//*************************************
	//여기 구현한 로직으로 풀면 문제 발생!
	//Temp벡터에 들어있는 마지막 값과 ReadyQ에 있는 값 모두 폭발한 후
	//다음 값과 이미 이전에 들어있던 마지막  값과 같을 때
	//이미 들어있는 값은 안터뜨림...
	//vector에 연속되는 수도 같이 저장해야할듯..


}

void input() {
	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		Query[i] = { d,s };
	}

	int init_Temp[51][51] = { 0, };
	int init_Row[4] = { (N + 1) / 2, (N + 1) / 2 + 1 , (N + 1) / 2 + 1 , (N + 1) / 2 - 1 };
	int init_Col[4] = { (N + 1) / 2 - 1 , (N + 1) / 2 - 1 , (N + 1) / 2 + 1 ,(N + 1) / 2 + 1 };

	int init_dr[4] = { -1,1,1,-1 };
	int init_dc[4] = { -1,-1,1,1 };
	int dir[4] = { 2,4,1,3 };

	for (int i = 0; i < N/2; i++) {
		for (int j = 0; j < 4; j++) {
			init_Temp[init_dr[j] * i + init_Row[j]][init_dc[j] * i + init_Col[j]] = dir[j];
		}
	}

	
	
	int nowRow = (N + 1) / 2;
	int nowCol = (N + 1) / 2;
	int nowDir = 3;
	init_Temp[nowRow][nowCol] = 0;

	for (int i = 0; i < N * N; i++) {
		if (init_Temp[nowRow][nowCol] != 0) nowDir = init_Temp[nowRow][nowCol];
		ID_Mapping[i] = { nowRow, nowCol, nowDir };
		nowRow += dr[nowDir];
		nowCol += dc[nowDir];
	}

	int debugging = -1;
}
void solution() {

	for (int q = 0; q < M; q++) {
		Magic(Query[q].d, Query[q].s);
		Explosion();
	}

}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

*/