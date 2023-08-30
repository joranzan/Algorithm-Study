#include<iostream>
#include<vector>

using namespace std;

//문제 설명의 key point

//목표. 두 사람의 충전량 최대 합 구하기


// 이동
// - 시간별 사용자의 위치 주어짐
// - 사용자가 동시에 같은 위치로 이동 가능

// 충전 
//	- BC의 거리안에 있으면 해당 BC에서 충전 가능
//	- 거리 계산 방법 : 좌표 차이 값
//	- 한 곳에서 여러 BC범위에 속하면 1개 선택
//  -  같은 충전기 사용 시 (반으로 나눠 사용)



//입력
/*
5
20 3
2 2 3 2 2 2 2 3 3 4 4 3 2 2 3 3 3 2 2 3
4 4 1 4 4 1 4 4 1 1 1 4 1 4 3 3 3 3 3 3
4 4 1 100
7 10 3 40
6 3 2 70

*/

struct BC {
	int row, col, range, P;
};

vector<int> pos[2];
vector<BC> bc;
vector<vector<vector<int>>> graph;//[who], [time] -> 충전 가능한 bc들(index)
int M, A; //이동시간 , BC의 개수


void init() {

	M = A = 0;
	bc.clear();

}
void input() {
	cin >> M >> A;
	graph = vector<vector<vector<int>>>(2, vector<vector<int>>(M + 1));
	pos[0] = vector<int>(M + 1);  //M+1개 짜리로 생성
	pos[1] = vector<int>(M + 1);  //M+1개 짜리로 생성

	for (int i = 0; i < 2; i++) {  //0번사람과 1번사람
		pos[i][0] = 0;  // 0의 시간엔 그자리 그대로 있다
		for (int j = 1; j <= M; j++) {
			cin >> pos[i][j];
		}
	}
	bc.push_back({ 0,0,500,0 });  //충전기 사용 X , (모든 좌표에서 고를 수 있는 선택지)
	for (int i = 0; i < A; i++) {
		int row, col, range, P;
		cin >> col >> row >> range >> P;
		bc.push_back({ row,col,range,P });

	}
}

const int dr[5] = { 0,-1,0,1,0 };
const int dc[5] = { 0,0,1,0,-1 };

void makeGraph(int time, int who, int row, int col) { //시가별로 겹치는 영역들 찾기
	//time이라는 시간에 who라는 사람이 row,col에 있다

	//기저조건
	if (time > M) return;

	int nr = row + dr[pos[who][time]];
	int nc = col + dc[pos[who][time]];

	for (int i = 0; i <= A; i++) {
		BC nowbc = bc[i];
		int dist = abs(nowbc.row - nr) + abs(nowbc.col - nc);
		if (dist <= nowbc.range)
			//nowbc를 충전 가능 <- who 라는 사람이 time이라는 시간에 nowbc를 충전 가능
			graph[who][time].push_back(i);
	}
	makeGraph(time + 1, who, nr, nc);
}

int calcCharge(int time) {
	if (time > M) return 0; //시간 오바되면 더이상 충전 X




	int maxCharge = 0;
	for (int i = 0; i < graph[0][time].size(); i++) {
		for (int j = 0; j < graph[1][time].size(); j++) {
			
			int A = graph[0][time][i];
			int B = graph[1][time][j];
			if (A == B) {  //같은거 고르면 2분의 1만 사용가능
				maxCharge = max(maxCharge, (bc[A].P)); 
				//짝수이므로 그냥 안나누고 그대로 더해도됨
				//maxCharge = max(maxCharge, (bc[A].P); 
				//maxCharge = max(maxCharge, (bc[B].P);
			}
			else {
				maxCharge = max(maxCharge, bc[A].P + bc[B].P);
			}
		}
	}

	int nextCharge = calcCharge(time + 1);  //time+1부터 끝까지 충전하면 얼마냐

	return maxCharge + nextCharge;    //지금부터 얻을 수 있는 최대 충전량
}

int solution() {
	makeGraph(0, 0, 1, 1); //0시간에 0사람이 (1,1)에서 시작
	makeGraph(0, 1, 10, 10); //0시간에 1사람이 (10,10)에서 시작
	return calcCharge(0);
}



int main() {

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







//----설계 부분 -----

// Simulation?
// 시간 복잡도 (최악의 상황)
// 100(이동시간)
// 이용자 둘이 겹쳤을 때 모든 BC가 겹치는 상황 : BC(8개) 중 선택 -> 8 * 8 = 64개
// Simulation 가능


//시간별로 겹치는 BC영역 찾기 <- simulation으로 시간마다 겹치는 영역 찾기
//해당 영역에서 BC를 선택할 수 있는 경우 조합(가능한 Case들)
//DFS(int index, int depth)
