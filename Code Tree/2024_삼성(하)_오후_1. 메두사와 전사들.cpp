#include<iostream>
#include<vector>
#include<queue>

using namespace std;

/*
����
N : 4�̻� 50����
M : 0�̻� 300����
*/
struct pos {
	int row;
	int col;
};

struct Warrior {
	int id;   //���� ID ��ȣ
	pos wpos; //���� ���� ��ġ
	bool stone = false;  //���� �Ǿ����� ����
	bool dead = false;   //��������� ����
};


int N, M;   //N(�� ũ��), M(���� ��)
pos Snake;  //�޵λ� �� ��ġ
pos Park;   //�޵λ� ���� ��ġ
vector<Warrior> WarriorInfo;     //������� ����
int RoadMap[51][51] = { 0, };    //���� ���� (����(0), �񵵷�(1))
vector<int> WarriorMap[51][51];  //���� ��ġ ���� ID(1~M)�� ����(���� ���� ���� ���� ����)->�޵λ� �þ߰� ���� �� DAT
int SightMap[51][51] = { 0, };   //�þ߰� �迭 (1 : ����) (-1 : �Ⱥ���)
int ans_dist = 0;
int ans_stone = 0;
int ans_attack = 0;
bool arrived = false;

void input() {
	//N , M : ���� ũ��, ���� ��
	//(sr, sc), (er, ec) : ���� ��ġ, ������ ��ġ
	//(r1,c1) ~ : ������ ��ġ
	//���� ����
	cin >> N >> M;
	cin >> Snake.row >> Snake.col;
	cin >> Park.row >> Park.col;

	Warrior Dummy = { 0,{0,0} };
	WarriorInfo.push_back(Dummy);

	for(int i = 1; i <= M; i++) {
		Warrior temp;
		temp.id = i;
		cin >> temp.wpos.row >> temp.wpos.col;
		WarriorInfo.push_back(temp);
		WarriorMap[temp.wpos.row][temp.wpos.col].push_back(temp.id);
	}

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> RoadMap[r][c];
		}
	}

	

}

bool check_valid() {

	queue<pos> q;
	q.push(Snake);
	int Visited[51][51] = { 0, };
	Visited[Snake.row][Snake.col] = 1;

	int dr[4] = { -1,1,0,0 };
	int dc[4] = { 0,0,-1,1 };

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();
		if (nowRow == Park.row && nowCol == Park.col) {
			return true;
		}
		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) continue;
			if (Visited[nextRow][nextCol] == 1) continue;
			if (RoadMap[nextRow][nextCol] == 1) continue;
			Visited[nextRow][nextCol] = 1;
			q.push({ nextRow, nextCol });
		}
	}
	return false;
}

void snake_move() {
	queue<pos> q;    //{���� ��ġ, ���� ��ġ}
	q.push(Snake);
	int Visited[51][51] = { 0, };
	Visited[Snake.row][Snake.col] = 1;

	pair<pos, int> temp[51][51];

	int dr[4] = { -1,1,0,0 };
	int dc[4] = { 0,0,-1,1 };

	int SelectedDir = -1;

	while (!q.empty()) {
		int nowRow = q.front().row;
		int nowCol = q.front().col;
		q.pop();

		if (nowRow == Park.row && nowCol == Park.col) {
			int nowDir = -1;
			while (nowRow != Snake.row || nowCol != Snake.col) {
				nowDir = temp[nowRow][nowCol].second;
				int tempRow = nowRow;
				int tempCol = nowCol;
				nowRow = temp[tempRow][tempCol].first.row;
				nowCol = temp[tempRow][tempCol].first.col;
			}
			SelectedDir = nowDir;
			//SelectedDir = temp[Snake.row][Snake.col].second;
			break;
		}

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr[dir];
			int nextCol = nowCol + dc[dir];
			if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) continue;
			if (Visited[nextRow][nextCol] == 1) continue;
			if (RoadMap[nextRow][nextCol] == 1) continue;
			Visited[nextRow][nextCol] = 1;
			temp[nextRow][nextCol].first = { nowRow, nowCol };
			temp[nextRow][nextCol].second = dir;
			q.push({ nextRow, nextCol });
		}
	}

	//�޵λ� �̵�
	Snake.row += dr[SelectedDir];
	Snake.col += dc[SelectedDir];

	//1-1) �̵��� ĭ�� ���� ���� ��� : ����� �����
	for (int i = 0; i < WarriorMap[Snake.row][Snake.col].size(); i++) {
		int nowID = WarriorMap[Snake.row][Snake.col][i];
		WarriorInfo[nowID].dead = true;
	}

	if (Snake.row == Park.row && Snake.col == Park.col) arrived = true;

}



void snake_sight() {
	//2. �޵λ��� �ü�
	//	1) �����¿� �� �ϳ��� �ٶ�(���縦 ���� �� �� �ִ� ���� �ٶ�, ������ �� �����¿� ��)
	//	2) 90�� �þ߰�(ó�� ��� ���� ���->�밢��) * *********************************
	//	2 - 1) ���簡 �þ߰��� ���� ��� ���� ��
	//	- �ٸ� ���翡 ������ ��� �޵λ翡�� ������ ����(������� ��ġ) ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? �׷� �밢���� �����¿� ���� ������ ?
	//	-�޵λ簡 �ٶ󺸴� ���⿡ ���� Mapping �ʿ� or �þ߰� Map ���� ����� ĭ����� ������� Ž��(cnt : �� ���� ��� ���������� �׸�)
	//	- ��(�Ʒ�)�� ��� Col�������� ���� ������

	//	2 - 2) ���� ���� ����� ���� ���� ������ �� ����
	//	2 - 3) �� �� �̻��� ������� ���� ĭ�� ��� �Ѵ� ��!

	vector<int> result[4];  //���⺰ �ٶ� �� �ִ� ������ ID
	int diag_dr[4] = { -1,-1,1,1 };
	int diag_dc[4] = { -1,1,-1,1 };
	int tempMap[51][51] = { 0, };
	int maxDist = max(max(max(N - 1 - Snake.row, Snake.row), N - 1 - Snake.col), Snake.col);


	//��
	for (int r = 1; r <= Snake.row; r++) {
		int nowRow = Snake.row - r;
		int lineCnt = 0;
		int invalidCnt = 0;
		for (int nowCol = Snake.col - r; nowCol <= Snake.col + r; nowCol++) {
			if (nowCol < 0 || nowCol >= N) continue;
			lineCnt++;
			if (tempMap[nowRow][nowCol] == -1) {
				invalidCnt++;
				continue;
			}
			
			tempMap[nowRow][nowCol] = 1;
			bool warrior_exist = false;
			for (int i = 0; i < WarriorMap[nowRow][nowCol].size(); i++) {
				if (!WarriorInfo[WarriorMap[nowRow][nowCol][i]].dead) {
					result[0].push_back(WarriorMap[nowRow][nowCol][i]);
					warrior_exist = true;
				}
			}

			if (warrior_exist) {
				for (int t_r = 1; t_r <= nowRow; t_r++) {
					int tempRow = nowRow - t_r;
					if (nowCol == Snake.col) tempMap[tempRow][nowCol] = -1;
					else if (nowCol < Snake.col) {
						for (int tempCol = nowCol - t_r; tempCol <= nowCol; tempCol++) {
							if (tempCol < 0 || tempCol >= N) continue;
							tempMap[tempRow][tempCol] = -1;
						}
					}
					else {
						for (int tempCol = nowCol; tempCol <= nowCol + t_r; tempCol++) {
							if (tempCol < 0 || tempCol >= N) continue;
							tempMap[tempRow][tempCol] = -1;
						}
					}
				}
			}
			
		}

		if (invalidCnt == lineCnt) break;
	}
	//�밢�� 4���� �ʱ�ȭ
	for (int i = 1; i <= maxDist; i++) {
		for (int dir = 0; dir < 4; dir++) {
			int nowRow = Snake.row + diag_dr[dir] * i;
			int nowCol = Snake.col + diag_dc[dir] * i;
			if (nowRow < 0 || nowCol < 0 || nowRow >= N || nowCol >= N) continue;
			tempMap[nowRow][nowCol] = 0;
		}
	}

	//��
	for (int r = 1; r <= N - 1 - Snake.row; r++) {
		int nowRow = Snake.row + r;
		int lineCnt = 0;
		int invalidCnt = 0;
		for (int nowCol = Snake.col - r; nowCol <= Snake.col + r; nowCol++) {
			if (nowCol < 0 || nowCol >= N) continue;
			lineCnt ++;
			if (tempMap[nowRow][nowCol] == -1) {
				invalidCnt++;
				continue;
			}

			tempMap[nowRow][nowCol] = 1;
			bool warrior_exist = false;

			for (int i = 0; i < WarriorMap[nowRow][nowCol].size(); i++) {
				if (!WarriorInfo[WarriorMap[nowRow][nowCol][i]].dead) {
					result[1].push_back(WarriorMap[nowRow][nowCol][i]);
					warrior_exist = true;
				}
				
			}
			if (warrior_exist) {
				for (int t_r = 1; t_r <= N - 1 - nowRow; t_r++) {
					int tempRow = nowRow + t_r;
					if (nowCol == Snake.col) tempMap[tempRow][nowCol] = -1;
					else if (nowCol < Snake.col) {
						for (int tempCol = nowCol - t_r; tempCol <= nowCol; tempCol++) {
							if (tempCol < 0 || tempCol >= N) continue;
							tempMap[tempRow][tempCol] = -1;
						}
					}
					else {
						for (int tempCol = nowCol; tempCol <= nowCol + t_r; tempCol++) {
							if (tempCol < 0 || tempCol >= N) continue;
							tempMap[tempRow][tempCol] = -1;
						}
					}
					
				}
			}
			
		}

		if (invalidCnt == lineCnt) break;
	}
	//�밢�� 4���� �ʱ�ȭ
	for (int i = 1; i <= maxDist; i++) {
		for (int dir = 0; dir < 4; dir++) {
			int nowRow = Snake.row + diag_dr[dir] * i;
			int nowCol = Snake.col + diag_dc[dir] * i;
			if (nowRow < 0 || nowCol < 0 || nowRow >= N || nowCol >= N) continue;
			tempMap[nowRow][nowCol] = 0;
		}
	}

	//��
	for (int c = 1; c <= Snake.col; c++) {
		int nowCol = Snake.col - c;
		int lineCnt = 0;
		int invalidCnt = 0;
		for (int nowRow = Snake.row - c; nowRow <= Snake.row + c; nowRow++) {
			if (nowRow < 0 || nowRow >= N) continue;
			lineCnt++;
			if (tempMap[nowRow][nowCol] == -1) {
				invalidCnt++;
				continue;
			}

			tempMap[nowRow][nowCol] = 1;
			bool warrior_exist = false; 

			for (int i = 0; i < WarriorMap[nowRow][nowCol].size(); i++) {
				if (!WarriorInfo[WarriorMap[nowRow][nowCol][i]].dead) {
					result[2].push_back(WarriorMap[nowRow][nowCol][i]);
					warrior_exist = true;
				}
				
			}
			if (warrior_exist) {
				for (int t_c = 1; t_c <= nowCol; t_c++) {
					int tempCol = nowCol - t_c;
					if (nowRow == Snake.row) tempMap[nowRow][tempCol] = -1;
					else if (nowRow < Snake.row) {
						for (int tempRow = nowRow - t_c; tempRow <= nowRow; tempRow++) {
							if (tempRow < 0 || tempRow >= N) continue;
							tempMap[tempRow][tempCol] = -1;
						}
					}
					else {
						for (int tempRow = nowRow; tempRow <= nowRow + t_c; tempRow++) {
							if (tempRow < 0 || tempRow >= N) continue;
							tempMap[tempRow][tempCol] = -1;
						}
					}
					
				}
			}
		}

		if (invalidCnt == lineCnt) break;
	}
	
	//�밢�� 4���� �ʱ�ȭ
	for (int i = 1; i <= maxDist; i++) {
		for (int dir = 0; dir < 4; dir++) {
			int nowRow = Snake.row + diag_dr[dir] * i;
			int nowCol = Snake.col + diag_dc[dir] * i;
			if (nowRow < 0 || nowCol < 0 || nowRow >= N || nowCol >= N) continue;
			tempMap[nowRow][nowCol] = 0;
		}
	}

	//��
	for (int c = 1; c <= N - 1 - Snake.col; c++) {
		int nowCol = Snake.col + c;
		int lineCnt = 0;
		int invalidCnt = 0;
		for (int nowRow = Snake.row - c; nowRow <= Snake.row + c; nowRow++) {
			if (nowRow < 0 || nowRow >= N) continue;
			lineCnt++;
			if (tempMap[nowRow][nowCol] == -1) {
				invalidCnt++;
				continue;
			}

			tempMap[nowRow][nowCol] = 1;
			bool warrior_exist = false;

			for (int i = 0; i < WarriorMap[nowRow][nowCol].size(); i++) {
				if (!WarriorInfo[WarriorMap[nowRow][nowCol][i]].dead) {
					result[3].push_back(WarriorMap[nowRow][nowCol][i]);
					warrior_exist = true;
				}
				
			}
			if (warrior_exist) {
				for (int t_c = 1; t_c <= N - 1 - nowCol; t_c++) {
					int tempCol = nowCol + t_c;
					if (nowRow == Snake.row) tempMap[nowRow][tempCol] = -1;
					else if (nowRow < Snake.row) {
						for (int tempRow = nowRow - t_c; tempRow <= nowRow; tempRow++) {
							if (tempRow < 0 || tempRow >= N) continue;
							tempMap[tempRow][tempCol] = -1;
						}
					}
					else {
						for (int tempRow = nowRow; tempRow <= nowRow + t_c; tempRow++) {
							if (tempRow < 0 || tempRow >= N) continue;
							tempMap[tempRow][tempCol] = -1;
						}
					}
				}
			}
		}

		if (invalidCnt == lineCnt) break;
	}
	//�밢�� 4���� �ʱ�ȭ
	for (int i = 1; i <= maxDist; i++) {
		for (int dir = 0; dir < 4; dir++) {
			int nowRow = Snake.row + diag_dr[dir] * i;
			int nowCol = Snake.col + diag_dc[dir] * i;
			if (nowRow < 0 || nowCol < 0 || nowRow >= N || nowCol >= N) continue;
			tempMap[nowRow][nowCol] = 0;
		}
	}


	//���� ���ϱ�
	int maxDir = 0;
	int maxWarrior = 0;
	for (int i = 0; i < 4; i++) {
		int debugging = -1;
		//cout << "result[" << i << "].size(): " << result[i].size() << ", maxWarrior: " << maxWarrior << endl;
		int result_size = result[i].size();
		if (maxWarrior < result_size) {
			maxWarrior = result_size;
			maxDir = i;
		}
	}

	int debugging = -1;

	//���� �þ߰� ó��
	switch (maxDir) {
	case 0:
		for (int r = 1; r <= Snake.row; r++) {
			int nowRow = Snake.row - r;
			for (int nowCol = Snake.col - r; nowCol <= Snake.col + r; nowCol++) {
				if (nowCol < 0 || nowCol >= N) continue;
				if (SightMap[nowRow][nowCol] == -1) {
					continue;
				}

				SightMap[nowRow][nowCol] = 1;

				if (WarriorMap[nowRow][nowCol].size() > 0) {
					for (int t_r = 1; t_r <= nowRow; t_r++) {
						int tempRow = nowRow - t_r;
						if (nowCol == Snake.col) SightMap[tempRow][nowCol] = -1;
						else if (nowCol < Snake.col) {
							for (int tempCol = nowCol - t_r; tempCol <= nowCol; tempCol++) {
								if (tempCol < 0 || tempCol >= N) continue;
								SightMap[tempRow][tempCol] = -1;
							}
						}
						else {
							for (int tempCol = nowCol; tempCol <= nowCol + t_r; tempCol++) {
								if (tempCol < 0 || tempCol >= N) continue;
								SightMap[tempRow][tempCol] = -1;
							}
						}
						
					}
				}

			}
		}
		break;
	case 1:
		for (int r = 1; r <= N - 1 - Snake.row; r++) {
			int nowRow = Snake.row + r;
			for (int nowCol = Snake.col - r; nowCol <= Snake.col + r; nowCol++) {
				if (nowCol < 0 || nowCol >= N) continue;
				if (SightMap[nowRow][nowCol] == -1) {
					continue;
				}

				SightMap[nowRow][nowCol] = 1;


				if (WarriorMap[nowRow][nowCol].size() > 0) {
					for (int t_r = 1; t_r <= N - 1 - nowRow; t_r++) {
						int tempRow = nowRow + t_r;
						if (nowCol == Snake.col) SightMap[tempRow][nowCol] = -1;
						else if (nowCol < Snake.col) {
							for (int tempCol = nowCol - t_r; tempCol <= nowCol; tempCol++) {
								if (tempCol < 0 || tempCol >= N) continue;
								SightMap[tempRow][tempCol] = -1;
							}
						}
						else {
							for (int tempCol = nowCol; tempCol <= nowCol + t_r; tempCol++) {
								if (tempCol < 0 || tempCol >= N) continue;
								SightMap[tempRow][tempCol] = -1;
							}
						}
						
					}
				}

			}
		}
		break;
	case 2:
		for (int c = 1; c <= Snake.col; c++) {
			int nowCol = Snake.col - c;
			for (int nowRow = Snake.row - c; nowRow <= Snake.row + c; nowRow++) {
				if (nowRow < 0 || nowRow >= N) continue;
				if (SightMap[nowRow][nowCol] == -1) {
					continue;
				}

				SightMap[nowRow][nowCol] = 1;

				if (WarriorMap[nowRow][nowCol].size() > 0) {
					for (int t_c = 1; t_c <= nowCol; t_c++) {
						int tempCol = nowCol - t_c;
						if (nowRow == Snake.row) SightMap[nowRow][tempCol] = -1;
						else if (nowRow < Snake.row) {
							for (int tempRow = nowRow - t_c; tempRow <= nowRow; tempRow++) {
								if (tempRow < 0 || tempRow >= N) continue;
								SightMap[tempRow][tempCol] = -1;
							}
						}
						else {
							for (int tempRow = nowRow; tempRow <= nowRow + t_c; tempRow++) {
								if (tempRow < 0 || tempRow >= N) continue;
								SightMap[tempRow][tempCol] = -1;
							}
						}
						
					}
				}
			}
		}
		break;
	case 3 :
		for (int c = 1; c <= N - 1 - Snake.col; c++) {
			int nowCol = Snake.col + c;
			for (int nowRow = Snake.row - c; nowRow <= Snake.row + c; nowRow++) {
				if (nowRow < 0 || nowRow >= N) continue;
				if (SightMap[nowRow][nowCol] == -1) {
					continue;
				}

				SightMap[nowRow][nowCol] = 1;

				if (WarriorMap[nowRow][nowCol].size() > 0) {
					for (int t_c = 1; t_c <= N - 1 - nowCol; t_c++) {
						int tempCol = nowCol + t_c;
						if (nowRow == Snake.row) SightMap[nowRow][tempCol] = -1;
						else if (nowRow < Snake.row) {
							for (int tempRow = nowRow - t_c; tempRow <= nowRow; tempRow++) {
								if (tempRow < 0 || tempRow >= N) continue;
								SightMap[tempRow][tempCol] = -1;
							}
						}
						else {
							for (int tempRow = nowRow ; tempRow <= nowRow + t_c; tempRow++) {
								if (tempRow < 0 || tempRow >= N) continue;
								SightMap[tempRow][tempCol] = -1;
							}
						}
					}
				}
			}
		}
		break;
	}


	//�þ߰� ���� ����� ���� ����
	for (int i = 0; i < result[maxDir].size(); i++) {
		int id = result[maxDir][i];
		ans_stone++;
		WarriorInfo[id].stone = true;
	}
}

void warriors_move() {


	for (int i = 1; i <= M; i++) {
		if (WarriorInfo[i].dead) continue;
		if (WarriorInfo[i].stone) continue;

		//2) �޵λ縦 ���� �ִ� 2ĭ(��ĭ��) �̵�
		//	2-1) ù ��° �̵�
		//	- �޵λ�� �Ÿ��� ���� �� �ִ� �������� �� ĭ �̵�(�����¿� ��)
		//	- ���� ��, �޵λ��� �þ߿� ������ ������ �̵� ����-------- > �þ߰� �迭�� �������� �����ؾ���
		//	2-2) �� ��° �̵�
		//	- �޵λ�� �Ÿ��� ���� �� �ִ� �������� �� ĭ �̵�(�¿���� ��)
		//	- ���� ��, �޵λ��� �þ߿� ������ ������ �̵� ����------->�þ߰� �迭�� �������� �����ؾ���

		int dr1[4] = { -1,1,0,0 };
		int dc1[4] = { 0,0,-1,1 };

		int nowRow = WarriorInfo[i].wpos.row;
		int nowCol = WarriorInfo[i].wpos.col;

		int minDist = abs(Snake.row - nowRow) + abs(Snake.col - nowCol);
		int minDir = -1;

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr1[dir];
			int nextCol = nowCol + dc1[dir];
			if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) continue;
			if (SightMap[nextRow][nextCol] == 1) continue;
			int dist = abs(Snake.row - nextRow) + abs(Snake.col - nextCol);
			if (dist < minDist) {
				minDist = dist;
				minDir = dir;
			}
		}

		if (minDir == -1) continue;

		ans_dist++;
		WarriorInfo[i].wpos.row += dr1[minDir];
		WarriorInfo[i].wpos.col += dc1[minDir];


		//�ι�° �̵�

		//minDist = 5000;
		minDir = -1;

		nowRow = WarriorInfo[i].wpos.row;
		nowCol = WarriorInfo[i].wpos.col;
		if (nowRow == Snake.row && nowCol == Snake.col) {
			WarriorInfo[i].dead = true;
			ans_attack++;
			continue;
		}

		int dr2[4] = { 0,0,-1,1 };
		int dc2[4] = { -1,1,0,0 };

		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr2[dir];
			int nextCol = nowCol + dc2[dir];
			if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N) continue;
			if (SightMap[nextRow][nextCol] == 1) continue;
			int dist = abs(Snake.row - nextRow) + abs(Snake.col - nextCol);
			if (dist < minDist) {
				minDist = dist;
				minDir = dir;
			}
		}
		if (minDir == -1) continue;
		ans_dist++;
		WarriorInfo[i].wpos.row += dr2[minDir];
		WarriorInfo[i].wpos.col += dc2[minDir];

		nowRow = WarriorInfo[i].wpos.row;
		nowCol = WarriorInfo[i].wpos.col;
		if (nowRow == Snake.row && nowCol == Snake.col) {
			WarriorInfo[i].dead = true;
			ans_attack++;
		}
	}

	
}

void setting_back() {



	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			SightMap[r][c] = 0;
			WarriorMap[r][c].clear();
		}
	}

	for (int i = 1; i <= M; i++) {
		if (WarriorInfo[i].dead) continue;
		if (WarriorInfo[i].stone) WarriorInfo[i].stone = false;
		WarriorMap[WarriorInfo[i].wpos.row][WarriorInfo[i].wpos.col].push_back(i);
	}
}

void solution() {
	input();
	//�޵λ簡 ������ ������ �� �ִ��� �˻�
	bool valid = check_valid();
	if (!valid) {
		cout << "-1";
		return;
	}

	while (Snake.row != Park.row || Snake.col != Park.col) {
		ans_dist = 0;
		ans_stone = 0;
		ans_attack = 0;
		//�޵λ� �̵�
		snake_move();
		//�޵λ� �ü� ó��
		if (arrived) break;
		snake_sight();
		//���� �̵� + ���� ��ġ���� �ʱ�ȭ & ���� + ���� ����
		warriors_move();
		//���� ��� + �ʱ�ȭ(�þ߰� �迭, ����� �� ����)
		setting_back();
		cout << ans_dist << " " << ans_stone << " " << ans_attack << "\n";
	}
	
	cout << "0";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	solution();

	return 0;
}





/*
���� �м� 08:37

����)
1. NxN �� (0 ~ N-1)
    - ����:0
    - ���� �ƴ� ��: 1

���� : M ��
1) �ʱ� ��ġ : (ri, ci)
2) �޵λ縦 ���� �ִ� ���
3) ����/�񵵷� ��� �̵� ����


�޵λ� ��ǥ : (Sr, Sc)
���� ��ǥ : (Er, Ec)
1) �޵λ�� ���θ� �̵� ����
2) ��, ���� ��� �׻� ���� ��
3) ��, ���� ��� ��ǥ �ٸ�
4) �ʱ���� ���� ������� ��ġ�ϴ� ��� ����
5) ������� �����̱� ���� ���� ����� ���� �� ����



����)


1. �޵λ��� �̵�
1) ���θ� ���� �������� �ִܰ�η� ��ĭ �̵�
	1-1) �̵��� ĭ�� ���� ���� ��� : ����� �����
	1-2) �ִܰ�� �켱���� : �����¿�
	1-3) ��->�������� ��ΰ� ���� ���� ���� ******************************

2. �޵λ��� �ü�
1) �����¿� �� �ϳ��� �ٶ� (���縦 ���� �� �� �ִ� ���� �ٶ�, ������ �� �����¿� ��)
2) 90�� �þ߰� (ó�� ��� ���� ��� -> �밢��) **********************************
	2-1) ���簡 �þ߰��� ���� ��� ���� ��
		- �ٸ� ���翡 ������ ��� �޵λ翡�� ������ ���� (������� ��ġ) ??????????????????? �׷� �밢���� �����¿� ���� ������?
		- �޵λ簡 �ٶ󺸴� ���⿡ ���� Mapping �ʿ� or �þ߰� Map ���� ����� ĭ����� ������� Ž�� (cnt :�� ���� ��� ���������� �׸�)
			- ��(�Ʒ�)�� ��� Col�������� ���� ������

	2-2) ���� ���� ����� ���� ���� ������ �� ����
	2-3) �� �� �̻��� ������� ���� ĭ�� ��� �Ѵ� ��!

		  
3. ������� �̵�
1) ���� ������ ���� ����� �̵�
2) �޵λ縦 ���� �ִ� 2ĭ(��ĭ��) �̵�
	2-1) ù ��° �̵� 
		- �޵λ�� �Ÿ��� ���� �� �ִ� �������� �� ĭ �̵� (�����¿� ��)
		- ���� ��, �޵λ��� �þ߿� ������ ������ �̵� ���� --------> �þ߰� �迭�� �������� �����ؾ���
	2-2) �� ��° �̵�
		- �޵λ�� �Ÿ��� ���� �� �ִ� �������� �� ĭ �̵� (�¿���� ��)
		- ���� ��, �޵λ��� �þ߿� ������ ������ �̵� ����  -------> �þ߰� �迭�� �������� �����ؾ���


4. ������ ����
1) �޵λ�� ���� ĭ�� ������ ����� �޵λ縦 ����
2) ������ ����� �����
3) �� �ϸ���
	- ��� ���簡 �̵��� �Ÿ��� ��
	- ���� �� ������ ��
	- �޵λ縦 ������ ������ ��
	- �޵λ簡 ������ �����Ѵٸ� 0 ��� �� ���α׷� ����


*/


/*
�ڷᱸ��

 Map1 : ���� ����
 Map2 : ���� ��ġ ���� (���� ���� ���� ���� ����) -> �޵λ� �þ߰� ���� �� DAT
 Map3 : �þ߰� �迭 (1 : ����) (-1 : �Ⱥ���)

 N(�� ũ��), M(����)
�޵λ� �� ��ġ
�޵λ� ���� ��ġ

������� ������ ��� �ڷᱸ��
{
1) ���� ��ġ r,c
2) �� ����
3) ����� ����
}
*/