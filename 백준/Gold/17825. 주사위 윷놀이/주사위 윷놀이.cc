#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//문제 분석

//시작 : 말 4개

//이동 조건
	//1) 화살표 방향
	//2) 파란색 칸 출발 : 파란색 화살표만
	//3) 나머지 : 빨간 화살표
	//4) 도착 칸 : 주사위 상관없이 종료

// 10개의 턴 (1~5 주사위) 
// 도착 안한 말 이동(주사위 수만큼)
// 말이 이동하는 칸에 다른 말 있으면 그 말 못 고름 *********
// 이동할 때마다 칸 점수 +=

void input();

int Dice[10] = { 0, };
int Route[4][24] = { 0, };
int Visited[4][24] = { 0, };
int Index[4] = { 0, };
int routeNow[4] = { 0, };
int Answer = 0;




vector<int> debugging;

void DFS(int depth, int sum) {

	if (depth >= 10) {
		//Answer 갱신
		Answer = max(Answer, sum);
		if (sum == 218) {
			int hello = -1;
		}
		
		return;
	}

	bool flag = true;
	for (int i = 0; i < 4; i++) {
		if (Index[i] != -1) {
			flag = false;
			break;
		}
	}
	if (flag) {
		Answer = max(Answer, sum);
		if (sum == 218) {
			int hello = -1;
		}
		return;
	}

	int nowDice = Dice[depth];

	for (int i = 0; i < 4; i++) {
		if (Index[i] == -1) continue;
		int nowIndex = Index[i];
		int route = routeNow[i];
		int nextroute = route;
		int nextIndex = nowIndex + nowDice;
		if (nextIndex > 23 || Route[route][nextIndex] == 0) {
			Visited[route][nowIndex] = 0;
			Index[i] = -1;
			debugging.push_back(i);
			DFS(depth + 1, sum);
			debugging.pop_back();
		}
		else {
			if (route == 0) {
				if (Route[0][nextIndex] == 10) nextroute = 1;
				else if (Route[0][nextIndex] == 20) nextroute = 2;
				else if (Route[0][nextIndex] == 30) nextroute = 3;
			}

			// 9 10 11 12
			// 13 14 15 16
			// 19 20 21 22
			if ((route == 1 && nextIndex == 9) || (route == 2 && nextIndex == 13) || (route == 3 && nextIndex == 19)) {
				if (Visited[1][9] || Visited[2][13] || Visited[3][19]) continue;
			}
			else if ((route == 1 && nextIndex == 10) || (route == 2 && nextIndex == 14) || (route == 3 && nextIndex == 20)) {
				if (Visited[1][10] || Visited[2][14] || Visited[3][20]) continue;
			}
			else if ((route == 1 && nextIndex == 11) || (route == 2 && nextIndex == 15) || (route == 3 && nextIndex == 21)) {
				if (Visited[1][11] || Visited[2][15] || Visited[3][21]) continue;
			}
			else if ((route==0&&nextIndex==20)||(route == 1 && nextIndex == 12) || (route == 2 && nextIndex == 16) || (route == 3 && nextIndex == 22)) {
				if (Visited[0][20] || Visited[1][12] || Visited[2][16] || Visited[3][22]) continue;
			}


			if (Visited[nextroute][nextIndex]==1||Visited[route][nextIndex]) continue;

			routeNow[i] = nextroute;
			Visited[nextroute][nextIndex] = 1;
			Visited[route][nowIndex] = 0;
			Index[i] = nextIndex;
			debugging.push_back(i);
			DFS(depth + 1, sum + Route[nextroute][nextIndex]);
			debugging.pop_back();
		}		

		//재귀 호출
		

		if (nextIndex > 22 || Route[route][nextIndex] == 0) {

			Visited[route][nowIndex] = 1;
			Index[i] = nowIndex;
		}
		else {
			routeNow[i] = route;
			Visited[route][nowIndex] = 1;
			Visited[nextroute][nextIndex] = 0;
			Index[i] = nowIndex;
		}

	}

}

void solution() {

	DFS(0,0);

	cout << Answer;
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


	input();
	solution();

	return 0;
}




void input() {
	for (int i = 0; i < 10; i++) {
		cin >> Dice[i];
	}

	for (int i = 1; i <= 20; i++) {
		Route[0][i] = i * 2;
		if (i <= 5) Route[1][i] = i * 2;
		if (i <= 10) Route[2][i] = i * 2;
		if (i <= 15) Route[3][i] = i * 2;
	}
	Route[1][6] = 13; Route[1][7] = 16; Route[1][8] = 19;
	Route[3][16] = 28; Route[3][17] = 27; Route[3][18] = 26;
	Route[2][11] = 22; Route[2][12] = 24; 
	
	Route[1][9] = 25; Route[1][10] = 30; Route[1][11] = 35; Route[1][12] = 40;
	Route[2][13] = 25; Route[2][14] = 30; Route[2][15] = 35; Route[2][16] = 40;
	Route[3][19] = 25; Route[3][20] = 30; Route[3][21] = 35; Route[3][22] = 40;


}

