#include<iostream>

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

int Dice[10] = { 0, };



void solution() {




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

}