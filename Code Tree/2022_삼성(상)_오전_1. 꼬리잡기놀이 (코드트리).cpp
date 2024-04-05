#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//Team ���� ��� ����?

struct pos {
	int row;
	int col;
};

struct Team {

	int railID;
	pos nowHead;
	pos nowBeforeTail;
	pos nowTail;
	int memberNum;
};

const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

int N; // Map ũ�� (3�̻� 20����)
int M; // ���� ���� (1�̻� 5����)
int K; // ���� �� (1�̻� 1000����)

int Map[21][21] = { 0, };
int TeamNumInfo[21][21] = { 0, };
bool Visited[21][21] = { 0, };
int teamNum = 0;
long Answer = 0;
vector<Team> teamInfo;
vector<vector<pos>> RailInfo;

void findRail(int row, int col, int railNum) {
	
	//����� ���� ã�ƾ���
	vector<pos> nowTeam;    //�� ����� ��ġ
	vector<pos> nowRail;    //�ش� ���� ���
	queue<pos> q;
	q.push({ row, col });
	Visited[row][col] = true;
	nowRail.push_back({ row,col });
	TeamNumInfo[row][col] = teamNum;

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Map[nextRow][nextCol] == 0 || Map[nextRow][nextCol] == 4||Map[nextRow][nextCol]==3) continue;
			if (Visited[nextRow][nextCol]) continue;
			Visited[nextRow][nextCol] = true;
			TeamNumInfo[nextRow][nextCol] = teamNum;
			nowRail.push_back({ nextRow, nextCol });
			q.push({ nextRow, nextCol });
		}
	}

	for (int dir = 0; dir < 4; dir++) {
		int nextRow = nowRail[nowRail.size() - 1].row + dr[dir];
		int nextCol = nowRail[nowRail.size() - 1].col + dc[dir];
		if (Map[nextRow][nextCol] == 3) {
			nowRail.push_back({ nextRow, nextCol });
			break;
		}

	}


	Team t;
	t.railID = railNum;
	t.nowHead = nowRail[0];
	t.nowTail = nowRail[nowRail.size()-1];
	t.nowBeforeTail = nowRail[nowRail.size() - 2];
	t.memberNum = nowRail.size();
	//������� 1������ 3������ ������� �������
	//team ���� �ֱ�


	teamInfo.push_back(t);
	

	q.push(t.nowTail);
	TeamNumInfo[t.nowTail.row][t.nowTail.col] = teamNum;
	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			for (int dir = 0; dir < 4; dir++) {
				int nextRow = nowRow + dr[dir];
				int nextCol = nowCol + dc[dir];
				if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
				if (Map[nextRow][nextCol] != 4) continue;
				if (Visited[nextRow][nextCol]) continue;
				Visited[nextRow][nextCol] = true;
				nowRail.push_back({ nextRow, nextCol });
				q.push({ nextRow, nextCol });
				TeamNumInfo[nextRow][nextCol] = teamNum;
			}
		}
	}
	teamNum++;
	RailInfo.push_back(nowRail);
	
	
}

void init() {

	RailInfo.clear();
	teamInfo.clear();
	teamNum = 0;
	Answer = 0;
	cin >> N >> M >> K;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			Visited[r][c] = false;
			cin >> Map[r][c];
			TeamNumInfo[r][c] = 0;
		}
	}

	int railNum = 0;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (Map[r][c] != 1) continue;
			if (Visited[r][c]) continue;
			findRail(r, c, railNum);
			railNum++;
		}
	}

	int debugging = -1;

}


void moveTeam() {

	for (int i = 0; i < teamInfo.size();i++) {

		pos nowHead = teamInfo[i].nowHead;
		pos nowTail = teamInfo[i].nowTail;
		pos nowBeforeTail = teamInfo[i].nowBeforeTail;

		//�Ӹ�
		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowHead.row + dr[dir];
			int nextCol = nowHead.col + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Map[nextRow][nextCol] == 4 || Map[nextRow][nextCol]==3) {

				Map[nowHead.row][nowHead.col] = 2;
				teamInfo[i].nowHead.row = nextRow;
				teamInfo[i].nowHead.col = nextCol;
				Map[nextRow][nextCol] = 1;
				break;
			}
		}

		//����
		Map[nowBeforeTail.row][nowBeforeTail.col] = 3;
		if(Map[nowTail.row][nowTail.col]==3) Map[nowTail.row][nowTail.col] = 4;   //�̹� 1�̸� Pass ��������
		teamInfo[i].nowTail.row = nowBeforeTail.row;
		teamInfo[i].nowTail.col = nowBeforeTail.col;


		//���� �ٷ� ��
		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowBeforeTail.row + dr[dir];
			int nextCol = nowBeforeTail.col + dc[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (Map[nextRow][nextCol] == 2) {

				teamInfo[i].nowBeforeTail.row = nextRow;
				teamInfo[i].nowBeforeTail.col = nextCol;
				break;
			}
		}

	}

	int debugging = -1;
}

void getScore(pos selected) {
	
	int nowTeamNum = TeamNumInfo[selected.row][selected.col];
	long cnt = 1;
	//���°���� ã��
	if (Map[selected.row][selected.col] == 3) {
		cnt = teamInfo[nowTeamNum].memberNum;
	}
	else if (Map[selected.row][selected.col] == 2) {
		bool VisitedTemp[21][21] = { false, };
		bool endofTeam = true;
		queue<pos> q;
		q.push({ teamInfo[nowTeamNum].nowHead.row, teamInfo[nowTeamNum].nowHead.col });
		Visited[teamInfo[nowTeamNum].nowHead.row][teamInfo[nowTeamNum].nowHead.col] = true;


		while (!q.empty()) {
			int nowRow = q.front().row;
			int nowCol = q.front().col;
			q.pop();
			if (nowRow == selected.row && nowCol == selected.col) {
				break;
			}

			for (int dir = 0; dir < 4; dir++) {
				int nextRow = nowRow + dr[dir];
				int nextCol = nowCol + dc[dir];
				if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
				if (Map[nextRow][nextCol] != 2) continue;
				if (VisitedTemp[nextRow][nextCol]) continue;
				VisitedTemp[nextRow][nextCol] = true;
				q.push({ nextRow, nextCol });
				cnt++;
			}

		}

	}
	//cout << cnt<<"\n";
	Answer += (cnt*cnt);

	
	pos nowTail = teamInfo[nowTeamNum].nowTail;
	pos nowHead = teamInfo[nowTeamNum].nowHead;
	pos nowBeforeTail = teamInfo[nowTeamNum].nowBeforeTail;

	//Head�� Tail �ٲٰ� Before Tail �����ؾ���
	Map[nowTail.row][nowTail.col] = 1;
	Map[nowHead.row][nowHead.col] = 3;
	for (int dir = 0; dir < 4; dir++) {
		int nextRow = nowHead.row + dr[dir];
		int nextCol = nowHead.col + dc[dir];
		if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
		if (Map[nextRow][nextCol] == 2) {
			teamInfo[nowTeamNum].nowBeforeTail.row = nextRow;
			teamInfo[nowTeamNum].nowBeforeTail.col = nextCol;
			break;
		}
	}

	teamInfo[nowTeamNum].nowTail = nowHead;
	teamInfo[nowTeamNum].nowHead = nowTail;

	

}

void solution() {
	


	for (int round = 1; round <= K; round++) {

		moveTeam();
		int nowBallway = round % (4 * N);
		bool getHit = false;
		pos getHitPerson;
		if (nowBallway > 0 && nowBallway <= N) {
			

			for (int i = 1; i <= N; i++) {
				if (Map[nowBallway][i] != 0 && Map[nowBallway][i] != 4) {
					getHit = true;
					getHitPerson.row = nowBallway;
					getHitPerson.col = i;
					break;
				}
			}
		}
		else if (nowBallway > N && nowBallway <= 2 * N) {
			int startPoint = nowBallway % N;
			if (startPoint == 0) startPoint = N;
			for (int i = N; i >= 1; i--) {
				if (Map[i][startPoint] != 0 && Map[i][startPoint] != 4) {
					getHit = true;
					getHitPerson.row = i;
					getHitPerson.col = startPoint;
					break;
				}
			}
		}
		else if (nowBallway > 2 * N && nowBallway <= 3 * N) {
			int startPoint = nowBallway % (2*N);   //1~N���� ����
			startPoint = N - startPoint + 1;
			for (int i = N; i >= 1; i--) {
				if (Map[startPoint][i] != 0 && Map[startPoint][i] != 4) {
					getHit = true;
					getHitPerson.row = startPoint;
					getHitPerson.col = i;
					break;
				}
			}
		}
		else if ((nowBallway > 3 * N && nowBallway < 4 * N) || nowBallway ==  0){
			
			
			int startPoint = nowBallway % (3*N);
			if (startPoint == 0) {
				startPoint = 1;
			}
			else {
				startPoint = N - startPoint + 1;
			}
			
			//cout << round << "��° ���� ������ : " << startPoint << "\n";
			for (int i = 1; i <= N; i++) {
				if (Map[i][startPoint] != 0 && Map[i][startPoint]!=4) {
					getHit = true;
					getHitPerson.row = i;
					getHitPerson.col = startPoint;
					break;
				}
			}
		}
		//cout << round << "��° ���� : ";
		int debugging = -1;

		if (!getHit) {
			//cout << "����\n";
			continue;
		}

		getScore(getHitPerson);

	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	solution();
	cout << Answer;

	return 0;
}

/*
���� �м�

NxN Map

1. �� ����

�� : 3�� �̻� (�ջ���� �㸮 ��� ������)
	- �Ǿ� : �Ӹ�
	- �ǵ� : ����

2. �̵�
- �־��� �̵� ���� ���󼭸� �̵� (��ȯ��)
- �̵����� ��ġ�� ����


3. ���� ���� (���庰)

1) �Ӹ� �����̵�, �� ���Ŀ� �ڿ� �� �� ĭ�� �����

2) ���� �̵� (�ݺ�)   
0    - (1 ~ N ��° ����) : ���� ����->���� Row�� ���ƿ�
1	- (N+1 ~ 2N ��° ����) : ���� �ϴ�->��� ��� Column���� ���ƿ�
2	- (2N+1 ~ 3N ��° ����) : ���� ����->���� ��� Row�� ���ƿ�
3	- (3N+1 ~ 4N ���� ����) : ���� ���->�ϴ� ��� Column���� ���ƿ�

3) �� ����� �� ����� ������ **����**�� ���� ����

���� : �Ӹ��κ��� k��° ��� : k^2

	- ������ ���� ��
		1) �Ӹ��� ���� ���� (������ �ٲ�)
			0�̸� 1 / 1�̸� 0

	- �ƹ��� ���ٸ� Continue

4) ���� ����



*/

/*
���� Ǯ��

�Ӹ��� ���� �ĺ��� 2�� �ۿ� ����

1. Team ���� ����
	- �� �� �뼱
	- �Ӹ� ��� (���� �Ӹ� :0, ���� ���� : 1)
	- ���� �Ӹ� : 
	- ���� ���� : 

	- ��� ���� �ʿ�(�Ӹ��κ��� ���°���� Ȯ�� �ʿ�)
		���� �Ӹ� [�Ӹ�, �㸮 ........�㸮, ����]
		���� ���� [����, �㸮 ........�㸮, �Ӹ�]
	- ����

2. (1~K)���庰 �� ���� �� �ε���(�� ������� Row/Col) ���� ����

3. �ش� ��/���� �ִ� ���� ã�Ƽ� ���� �ֱ� (���°���� Ȯ�� �ʿ�)

4. �ش� �� ���� �ٲٱ�

*/