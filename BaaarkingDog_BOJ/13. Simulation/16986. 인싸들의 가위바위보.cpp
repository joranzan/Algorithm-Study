#include<iostream>

using namespace std;


//�ϴ��� ���
//1. �ʿ��� �¼�, ��� ���� ���� ���ϱ�

//��� ����
//1. ��� ��� : ���� ���� �� ���� ����� �̱� ������ ����
//2. ���� ����� ���� - ���� ��� ���� ���� ��� -> ���� ����
//3. Ư�� ����� �̸� ���ǵ� �¼��� �޼��� �� ���� (2�� ����) �ݺ�
//4. ���ǵ� �¼��� ���ʷ� �޼��� ��� -> ���!


int N, K;
int Standard[10][10] = { 0, }; 
//2: ���� �� �̱� 
//1: ��� 
//0: ���� ������ ��
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


void DFS(int depth, int foe) {  //1: ���� 2: MinHo  
										
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

		if (result == 2) {  //���ΰ��� �̰��� ��
				
				J_Sum++;
				if (foe == 1) DFS(depth + 1, 2);
				else if (foe == 2) DFS(depth + 1, 1);
				J_Sum--;
				
		}
		else {  //���ΰ��� ���ų� ���� ��
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
	//���� ���� ��ȣ ��

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

//��ǥ : ��� �յ��� �ٸ��� ���� ����� �� �ִ°�?
// ������ ��ſ� ���л�Ȱ�� ���� �ν� ������������ ��ǥ �־���
// ����, ��ȣ�� �� �յ����� ������ �־����� ��



//void DFS(int depth, int foe, int orderJ) {  //1: ���� 2: MinHo  
//											//orderJ  1: ��  2: ��
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
//		if (orderJ == 1) {   //���ΰ��� �ռ����϶�
//			int result = Standard[i][foeChoice];
//
//			if (result == 2) {  //���ΰ��� �̰��� ��
//
//				J_Sum++;
//				if (foe == 1) DFS(depth + 1, 2, 1);
//				else if (foe == 2) DFS(depth + 1, 1, 1);
//				J_Sum--;
//
//			}
//			else {  //���ΰ��� ���ų� ���� ��
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
//		else if (orderJ == 2) { //���ΰ��� �޼����϶�
//			int result = Standard[i][foeChoice];
//
//			if (result == 0) {  //���ΰ��� ������
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
//			else {   //���ΰ��� �̱�ų� ����� ��
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