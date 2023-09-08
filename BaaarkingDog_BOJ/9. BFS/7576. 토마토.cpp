#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

//���� �м�
//���� �丶��, ������ �丶��
//���� �� 1�� �� (�����¿�) ����
//�� �ʹ� �ּ� �� �� -> Flood Fill? Visited�迭�� ���� ����?

//1: ���� �丶��, 0: ������ �丶��  -1: �丶�� ����

int N, M;
int Map[1000][1000] = { 0, };
int Visited[1000][1000] = { 0, };
vector<pair<int, int>> wellDone; //�ʱ� ���� �ֵ��� ��ǥ ���


void input() {

	cin >> M >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			Visited[i][j] = INT_MAX;
			if (Map[i][j] == 1) {
				wellDone.push_back({ i,j });
			}
			else if (Map[i][j] == -1) {
				Visited[i][j] = -1;
			}
		}
	}
}

int BFS() {

	
	queue<pair<int, int>> q;
	for (int i = 0; i < wellDone.size(); i++) {
		q.push(wellDone[i]);
		Visited[wellDone[i].first][wellDone[i].second] = 1;
	}

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	while (!q.empty()) {

		int now_r = q.front().first;
		int now_c = q.front().second;
		q.pop();
		
		for (int dir = 0; dir < 4; dir++) {
			int next_r = now_r + dr[dir];
			int next_c = now_c + dc[dir];
			if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= M) continue;
			if (Map[next_r][next_c] == -1) continue;
			if (Visited[next_r][next_c] <= Visited[now_r][now_c] + 1) continue;
			Visited[next_r][next_c] = Visited[now_r][now_c] + 1;
			q.push({ next_r,next_c });
		}
	}


	//1�� �ں��� �����µ� �ʱ���� 1�� ��Ƴ�����
	bool valid = true;
	int max_day = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] == -1) continue;
			if (Visited[i][j] == INT_MAX) {
				valid = false;
				break;
			}
			max_day = max(max_day, Visited[i][j]);
		}
		if (!valid) break;
	}
	//INT_MAX �����ϸ� -1 return
	if (!valid) {
		return -1;
	}
	//0�� ������ϸ� (Max�� -1) return
	else {
		return max_day - 1;
	}

}


void solution() {

	cout<< BFS();

}





int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();



	return 0;
}

//����
//NxM 1000x1000
//Flood Fill �� Ǯ�� 

//��� ���� ���ϸ� 0-> ���� Visited�� �湮���� ���� ���