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

int cnt[3] = { 0, };

bool flag = false;
int J_Sum = 0;
int K_Sum = 0;
int M_Sum = 0;
int Visited[10] = { 0, };
int debugging[21] = { 0, };

int winner(int turn, int p1, int p2) {


	int p1_result;
	int p2_result;
	if (p1 == 1) {
		p1_result = KyungHee[cnt[p1]];
	}
	else if (p1 == 2) {
		p1_result = MinHo[cnt[p1]];
	}

	if (p2 == 1) {
		p2_result = KyungHee[cnt[p2]];
	}
	else if (p2 == 2) {
		p2_result = MinHo[cnt[p2]];
	}

	int result = Standard[p1_result][p2_result];

	if (result == 2) {
		return p1;
	}
	else if(result==0) {
		return p2;
	}
	else {
		return max(p1, p2);
	}

}


void DFS(int depth, int foe) {  //1: 경희 2: MinHo  
										
	if (J_Sum >= K) {
		flag = true;
		return;
	}
	if (K_Sum >= K || M_Sum >= K) return;


	for (int i = 1; i <= N; i++) {
		if (Visited[i] != 0) continue;

		Visited[i] = depth;
		debugging[depth] = i;

		int foeChoice;
		if (foe == 1) {
			cnt[1]++;
			foeChoice = KyungHee[cnt[1]];
		}
		else if (foe == 2) {
			cnt[2]++;
			foeChoice = MinHo[cnt[2]];
		}

		int result = Standard[i][foeChoice];

		if (result == 2) {  //주인공이 이겼을 때
				
				J_Sum++;
				if (foe == 1) DFS(depth + 1, 2);
				else if (foe == 2) DFS(depth + 1, 1);
				J_Sum--;
				
		}
		else {  //주인공이 비기거나 졌을 때
			if (foe == 1) {
					K_Sum++;
					cnt[1]++;
					cnt[2]++;
					int next_winner = winner(depth + 1, 1, 2);
					if (next_winner == 1) {
						K_Sum++;
						DFS(depth + 2, next_winner);
						K_Sum--;
					}
					else if (next_winner == 2) {
						M_Sum++;
						DFS(depth + 2, next_winner);
						M_Sum--;
					}
					K_Sum--;
					cnt[1]--;
					cnt[2]--;
			}
			else if (foe == 2) {
				M_Sum++;
				cnt[1]++;
				cnt[2]++;
				int next_winner = winner(depth + 1, 2, 1);
				if (next_winner == 1) {
					K_Sum++;
					DFS(depth + 2, next_winner);
					K_Sum--;
				}
				else if (next_winner == 2) {
					M_Sum++;
					DFS(depth + 2, next_winner);
					M_Sum--;
				}
				M_Sum--;
				cnt[1]--;
				cnt[2]--;
			}
		}
		
		if (foe == 1) {
			cnt[1]--;
		}
		else if (foe == 2) {
			cnt[2]--;
		}

		Visited[i] = 0;
		debugging[depth] = 0;
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

	DFS(1, 1);
	if (flag) cout << "1";
	else cout << "0";
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



//void DFS(int depth, int foe, int orderJ) {  //1: 경희 2: MinHo  
//											//orderJ  1: 앞  2: 뒤
//	if (J_Sum >= K) {
//		flag = true;
//		return;
//	}
//	if (K_Sum >= K || M_Sum >= K) return;
//
//
//	for (int i = 1; i <= N; i++) {
//		if (Visited[i] != 0) continue;
//
//		Visited[i] = depth;
//		debugging[depth] = i;
//
//		int foeChoice;
//		if (foe == 1) {
//			foeChoice = KyungHee[depth];
//		}
//		else if (foe == 2) {
//			foeChoice = MinHo[depth];
//		}
//
//		if (orderJ == 1) {   //주인공이 앞순서일때
//			int result = Standard[i][foeChoice];
//
//			if (result == 2) {  //주인공이 이겼을 때
//
//				J_Sum++;
//				if (foe == 1) DFS(depth + 1, 2, 1);
//				else if (foe == 2) DFS(depth + 1, 1, 1);
//				J_Sum--;
//
//			}
//			else {  //주인공이 비기거나 졌을 때
//				if (foe == 1) {
//					K_Sum++;
//					int next_winner = winner(depth + 1, 1, 2);
//					if (next_winner == 1) {
//						K_Sum++;
//						DFS(depth + 2, next_winner, 2);
//						K_Sum--;
//					}
//					else if (next_winner == 2) {
//						M_Sum++;
//						DFS(depth + 2, next_winner, 2);
//						M_Sum--;
//					}
//					K_Sum--;
//				}
//				else if (foe == 2) {
//					M_Sum++;
//					int next_winner = winner(depth + 1, 2, 1);
//					if (next_winner == 1) {
//						K_Sum++;
//						DFS(depth + 2, next_winner, 2);
//						K_Sum--;
//					}
//					else if (next_winner == 2) {
//						M_Sum++;
//						DFS(depth + 2, next_winner, 2);
//						M_Sum--;
//					}
//					M_Sum--;
//				}
//			}
//		}
//		else if (orderJ == 2) { //주인공이 뒷순서일때
//			int result = Standard[i][foeChoice];
//
//			if (result == 0) {  //주인공이 졌을때
//				if (foe == 1) {
//					K_Sum++;
//					int next_winner = winner(depth + 1, 1, 2);
//
//					if (next_winner == 1) {
//						K_Sum++;
//						DFS(depth + 2, next_winner, 2);
//						K_Sum--;
//					}
//					else if (next_winner == 2) {
//						M_Sum++;
//						DFS(depth + 2, next_winner, 2);
//						M_Sum--;
//					}
//					K_Sum--;
//				}
//				else if (foe == 2) {
//					M_Sum++;
//					int next_winner = winner(depth + 1, 2, 1);
//
//					if (next_winner == 1) {
//						K_Sum++;
//						DFS(depth + 2, next_winner, 2);
//						K_Sum--;
//					}
//					else if (next_winner == 2) {
//						M_Sum++;
//						DFS(depth + 2, next_winner, 2);
//						M_Sum--;
//					}
//					M_Sum--;
//
//				}
//			}
//			else {   //주인공이 이기거나 비겼을 때
//				J_Sum++;
//				if (foe == 1) DFS(depth + 1, 2, 1);
//				else if (foe == 2) DFS(depth + 1, 1, 1);
//				J_Sum--;
//			}
//
//		}
//		Visited[i] = 0;
//		debugging[depth] = 0;
//	}
//
//
//}