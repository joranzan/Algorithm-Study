#include<iostream>

using namespace std;

//목표: 3번째 장대로 옮기기

//문제 분석
//3개의 장대
//N개의 반경 다른 원판 (N 20이하)

int Hanoi[3][21] = { 0 ,};   //0:없음 1:있음
int N;

void input() {

	cin >> N;
	for (int i = 1; i <= N; i++) {
		Hanoi[1][i] = 1;
	}

}

void DFS() {
	


	
}

void solution() {

}

int main() {

	input();
	solution();

	return 0;
}