#include<iostream>
#include<vector>

using namespace std;


//���� �м�
//N : ���μ� (��)  M: ���μ�(��)
//������ ���μ� ���̿� ���μ� ���� �� ����
//������ ���μ����� H���� ���μ� ���� �� ����


//�� ���μ� ���� X
//���� ���ϸ� X
//���� ���μ� �ִ� ��ġ���� ���� �� ����

//���� ����
//���μ����� ����
//���� �� -> �Ʒ��� ����
//���μ� ������ ��ĭ �̵�

//��ǥ : i�� ��� i��

struct pos {
	int row;
	int col;
};

struct Edge{
	int rowNum;
	int from;
	int to;
};

int N, M;
int H;

int Answer = 2112345678;
Edge Map[31][11];
bool Visited[31][11] = { false, };

vector<Edge> candi;



bool check(int num) {

	int nowRow = 1, nowCol = num;

	if (Visited[1][3] && Visited[3][4] && Visited[4][2]) {
		int debugging = -1;
	}

	while (nowRow <= H) {

		if (nowCol == 1) {
			if (!Visited[nowRow][nowCol]) {
				nowRow++;
				continue;
			}
		}
		else if(nowCol==N){
			if (!Visited[nowRow][nowCol - 1]) {
				nowRow++;
				continue;
			}
		}
		else {
			if (!Visited[nowRow][nowCol - 1] && !Visited[nowRow][nowCol]) {
				nowRow++;
				continue;
			}
		}
		Edge nowEdge;
		if (Visited[nowRow][nowCol]) {
			nowEdge = Map[nowRow][nowCol];
			nowCol = nowEdge.to;
		}
		else if (Visited[nowRow][nowCol - 1]) {
			nowCol = nowCol - 1;
		}
		
		nowRow++;
	}

	if (nowCol == num) return true;
	else return false;
}

void SelectLine(int index, int depth) {

	if (Visited[1][3] && Visited[3][4] && Visited[4][2]&&!Visited[6][1]) {
		int debugging = -1;
	}

	if (Answer <= depth) return;
	if (depth > 3) return;
	//Ż�� ����
	bool flag = true;
	for (int i = 1; i <= N; i++) {
		if (!check(i)) {
			flag = false;
			break;
		}
	}

	if (flag) {
		Answer = min(Answer, depth);
		return;
	}

	

	//��ٸ� ��ġ
	for (int i = index; i < candi.size(); i++) {
		Edge next = candi[i];

		if (next.from == 1) {
			if (Visited[next.rowNum][next.from] || Visited[next.rowNum][next.from+1]) continue;
		}
		else if (next.from == N - 1) {
			if (Visited[next.rowNum][next.from] || Visited[next.rowNum][next.from - 1]) continue;

		}
		else {
			if (Visited[next.rowNum][next.from] || Visited[next.rowNum][next.from -1] || Visited[next.rowNum][next.from + 1]) {
				continue;
			}
		}

		Visited[next.rowNum][next.from] = true;
		Map[next.rowNum][next.from] = { next.rowNum,next.from,next.from + 1 };
		SelectLine(i + 1, depth + 1);
		Map[next.rowNum][next.from] = { 0,0,0 };
		Visited[candi[i].rowNum][candi[i].from] = false;
	}


}


void input() {

	cin >> N >> M; //1������ ����
	cin >> H;

	for (int i = 1; i <= M; i++) {
		int a, b;  //a�� ������   b�� �����ٿ��� b+1�� ���� ����
		cin >> a >> b;

		Map[a][b] = { a,b, b + 1 };
		Visited[a][b] = true;

	}

	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			
			if (j == 1) {
				if (Visited[i][j]||Visited[i][j+1]) continue;
			}
			else if (j == N) {
				continue;
			}
			else if (j == N - 1) {
				if (Visited[i][j] || Visited[i][j - 1]) {
					continue;
				}
			}
			else {
				if (Visited[i][j] || Visited[i][j - 1] || Visited[i][j + 1]) {
					continue;
				}
			}
			candi.push_back({ i, j, j + 1 });
		}
	}



}

void solution() {

	if (M == 0) {
		cout << "0\n";
		return;
	}
	
	bool already = true;
	for (int i = 1; i <= N; i++) {
		if (!check(i)) {
			already = false;
			break;
		}
	}

	if (already) {
		cout << "0\n";
		return;
	}

	SelectLine(0, 0);
	if (Answer > 3) {
		cout << "-1\n";
	}
	else cout << Answer << "\n";

}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	input();
	solution();

	return 0;
}

