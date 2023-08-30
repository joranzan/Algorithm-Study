#include<iostream>
#include<vector>

using namespace std;

//���� ������ key point

//��ǥ. �� ����� ������ �ִ� �� ���ϱ�


// �̵�
// - �ð��� ������� ��ġ �־���
// - ����ڰ� ���ÿ� ���� ��ġ�� �̵� ����

// ���� 
//	- BC�� �Ÿ��ȿ� ������ �ش� BC���� ���� ����
//	- �Ÿ� ��� ��� : ��ǥ ���� ��
//	- �� ������ ���� BC������ ���ϸ� 1�� ����
//  -  ���� ������ ��� �� (������ ���� ���)



//�Է�
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
vector<vector<vector<int>>> graph;//[who], [time] -> ���� ������ bc��(index)
int M, A; //�̵��ð� , BC�� ����


void init() {

	M = A = 0;
	bc.clear();

}
void input() {
	cin >> M >> A;
	graph = vector<vector<vector<int>>>(2, vector<vector<int>>(M + 1));
	pos[0] = vector<int>(M + 1);  //M+1�� ¥���� ����
	pos[1] = vector<int>(M + 1);  //M+1�� ¥���� ����

	for (int i = 0; i < 2; i++) {  //0������� 1�����
		pos[i][0] = 0;  // 0�� �ð��� ���ڸ� �״�� �ִ�
		for (int j = 1; j <= M; j++) {
			cin >> pos[i][j];
		}
	}
	bc.push_back({ 0,0,500,0 });  //������ ��� X , (��� ��ǥ���� �� �� �ִ� ������)
	for (int i = 0; i < A; i++) {
		int row, col, range, P;
		cin >> col >> row >> range >> P;
		bc.push_back({ row,col,range,P });

	}
}

const int dr[5] = { 0,-1,0,1,0 };
const int dc[5] = { 0,0,1,0,-1 };

void makeGraph(int time, int who, int row, int col) { //�ð����� ��ġ�� ������ ã��
	//time�̶�� �ð��� who��� ����� row,col�� �ִ�

	//��������
	if (time > M) return;

	int nr = row + dr[pos[who][time]];
	int nc = col + dc[pos[who][time]];

	for (int i = 0; i <= A; i++) {
		BC nowbc = bc[i];
		int dist = abs(nowbc.row - nr) + abs(nowbc.col - nc);
		if (dist <= nowbc.range)
			//nowbc�� ���� ���� <- who ��� ����� time�̶�� �ð��� nowbc�� ���� ����
			graph[who][time].push_back(i);
	}
	makeGraph(time + 1, who, nr, nc);
}

int calcCharge(int time) {
	if (time > M) return 0; //�ð� ���ٵǸ� ���̻� ���� X




	int maxCharge = 0;
	for (int i = 0; i < graph[0][time].size(); i++) {
		for (int j = 0; j < graph[1][time].size(); j++) {
			
			int A = graph[0][time][i];
			int B = graph[1][time][j];
			if (A == B) {  //������ ���� 2���� 1�� ��밡��
				maxCharge = max(maxCharge, (bc[A].P)); 
				//¦���̹Ƿ� �׳� �ȳ����� �״�� ���ص���
				//maxCharge = max(maxCharge, (bc[A].P); 
				//maxCharge = max(maxCharge, (bc[B].P);
			}
			else {
				maxCharge = max(maxCharge, bc[A].P + bc[B].P);
			}
		}
	}

	int nextCharge = calcCharge(time + 1);  //time+1���� ������ �����ϸ� �󸶳�

	return maxCharge + nextCharge;    //���ݺ��� ���� �� �ִ� �ִ� ������
}

int solution() {
	makeGraph(0, 0, 1, 1); //0�ð��� 0����� (1,1)���� ����
	makeGraph(0, 1, 10, 10); //0�ð��� 1����� (10,10)���� ����
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







//----���� �κ� -----

// Simulation?
// �ð� ���⵵ (�־��� ��Ȳ)
// 100(�̵��ð�)
// �̿��� ���� ������ �� ��� BC�� ��ġ�� ��Ȳ : BC(8��) �� ���� -> 8 * 8 = 64��
// Simulation ����


//�ð����� ��ġ�� BC���� ã�� <- simulation���� �ð����� ��ġ�� ���� ã��
//�ش� �������� BC�� ������ �� �ִ� ��� ����(������ Case��)
//DFS(int index, int depth)
