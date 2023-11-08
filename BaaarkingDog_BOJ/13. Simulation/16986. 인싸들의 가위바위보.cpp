#include<iostream>

using namespace std;


//일대일 경기
//1. 필요한 승수, 경기 진행 순서 정하기

//경기 시작
//1. 비긴 경우 : 진행 순서 상 뒤인 사람이 이긴 것으로 간주
//2. 이전 경기의 승자 - 이전 경기 참여 안한 사람 -> 승자 결정
//3. 특정 사람이 미리 합의된 승수를 달성할 때 까지 (2번 과정) 반복
//4. 합의된 승수에 최초로 달성한 사람 -> 우승!


int N, K;
int Standard[10][10] = { 0, }; 
//2: 행이 열 이김 
//1: 비김 
//0: 행이 열한테 짐
int KyungHee[21] = { 0, };
int MinHo[21] = { 0, };

bool flag = false;
int J_Sum = 0;
int K_Sum = 0;
int M_Sum = 0;
int Visited[10] = { 0, };

void DFS(int depth, int foe, int orderJ) {  //1: 경희 2: MinHo  
											//orderJ  1: 앞  2: 뒤
	if (J_Sum >= 3) {
		flag = true;
		return;
	}
	if (depth > N) {
		return;
	}


	for (int i = 1; i <= N; i++) {
		if (Visited[i] == 1) continue;
		int foeChoice;
		if (foe == 1) {
			foeChoice = KyungHee[depth];
		}
		else if (foe == 2) {
			foeChoice = MinHo[depth];
		}

		if (orderJ == 1) {   //주인공이 앞순서일때
			int result = Standard[i][foeChoice];

			if (result == 2) {  //주인공이 이겼을 때
				
				
			}
			else {  //주인공이 비기거나 졌을 때

			}

		}
		else if (orderJ == 2) { //주인공이 뒷순서일때
			int result = Standard[i][foeChoice];

			if (result == 0) {  //주인공이 졌을때

			}
			else {   //주인공이 이기거나 비겼을 때

			}

		}

	}


}


void input() {
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Standard[i][j];
		}
	}

	for (int i = 1; i <= 20; i++) {
		cin >> KyungHee[i];
	}

	for (int i = 1; i <= 20; i++) {
		cin >> MinHo[i];
	}
}

void solution() {
	//지우 경희 민호 순




}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	input();
	solution();

	return 0;
}

//목표 : 모두 손동작 다르게 내어 우승할 수 있는가?
// 지우의 즐거운 대학생활을 위해 인싸 가위바위보의 상성표 주어짐
// 경희, 민호가 낼 손동작의 순서가 주어졌을 때