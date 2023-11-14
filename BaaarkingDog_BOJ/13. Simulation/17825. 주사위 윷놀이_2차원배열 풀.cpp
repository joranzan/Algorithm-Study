#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//���� �м�

//���� : �� 4��

//�̵� ����
	//1) ȭ��ǥ ����
	//2) �Ķ��� ĭ ��� : �Ķ��� ȭ��ǥ��
	//3) ������ : ���� ȭ��ǥ
	//4) ���� ĭ : �ֻ��� ������� ����

// 10���� �� (1~5 �ֻ���) 
// ���� ���� �� �̵�(�ֻ��� ����ŭ)
// ���� �̵��ϴ� ĭ�� �ٸ� �� ������ �� �� �� �� *********
// �̵��� ������ ĭ ���� +=

void input();

int Dice[10] = { 0, };
int Route[4][24] = { 0, };
int Visited[4][24] = { 0, };
int Index[4] = { 0, };
int routeNow[4] = { 0, };
int Answer = 0;


void DFS(int depth, int sum) {

	if (sum + (10 - depth) * 40 <= Answer) return;

	if (depth >= 10) {
		//Answer ����
		Answer = max(Answer, sum);
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
			DFS(depth + 1, sum);
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
			DFS(depth + 1, sum + Route[nextroute][nextIndex]);
		}		

		//��� ȣ��
		

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

	int nextIndex = Dice[0];
	if (Route[0][nextIndex] == 10) {
		routeNow[0] = 1;
	}

	Index[0] = nextIndex;
	Visited[routeNow[0]][nextIndex] = 1;


	DFS(1,Route[0][nextIndex]);

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

