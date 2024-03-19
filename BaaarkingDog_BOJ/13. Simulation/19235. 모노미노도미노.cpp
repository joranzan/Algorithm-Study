#include<iostream>
#include<algorithm>


using namespace std;
/*
  0 1 2 3  0 1 2 3 4 5
0            파
1
2
3

0 초
1
2
3
4
5
*/

int N;
int blockID = 1;
int t, startRow, startCol;
// 1: 1x1 
// 2: 1x2
// 3: 2x1
const int t_size_r[4] = { 0,0,0,1 };  
const int t_size_c[4] = { 0,0,1,0 };
int typeVersion[10001] = { 0, };
int Green[6][4] = { 0, };
int Blue[4][6] = { 0, };
int score = 0;
//초록색 보드(6x4)
//파란색 보드(4x6)


void updateBoard(int boardtype, int updatedPos) {
	//초록색 없데이트
	if (boardtype == 0) {

		for (int r = updatedPos; r >= 0; r--) {
			for (int c = 0; c < 4; c++) {
				//블록 없으면 무시
				if (Green[r][c] == 0) continue;
				int nowID = Green[r][c];
				int nowType = typeVersion[nowID];
				//블록은 있는데 2x1 블록의 윗부분이면 무시 (이미 옮겼으므로)
				if (nowType == 3 && r != 5 && Green[r + 1][c] == nowID) continue;
				
				switch (nowType) {
				case 1: {    //1x1

					for (int temp_r = 5; temp_r > r; temp_r--) {
						if (Green[temp_r][c] == 0) {
							Green[temp_r][c] = nowID;
							Green[r][c] = 0;
							break;
						}
					}
					break;
				}
				case 2: {    //1x2
					if (c == 3) break;
					int result_r = r;
					for (int temp_r = r+1; temp_r <= 5; temp_r++) {
						if (Green[temp_r][c] == 0 && Green[temp_r][c + 1] == 0) {
							result_r = temp_r;
						}
						else break;
					}
					if (result_r == r) break;
					Green[result_r][c] = nowID;
					Green[r][c] = 0;
					if (Green[r][c + 1] != nowID) break;
					Green[result_r][c + 1] = nowID;
					Green[r][c + 1] = 0;
					

					break;
				}
				case 3: {    //2x1
					if (r == 0) break;
					int result_r = r;
					for (int temp_r = r+1; temp_r <= 5; temp_r++) {
						if (Green[temp_r][c] == 0) {
							result_r = temp_r;
						}
						else break;
					}
					if (result_r == r) break;
					Green[result_r][c] = nowID;
					Green[r][c] = 0;

					if (Green[r - 1][c] != nowID) break;
					Green[result_r - 1][c] = nowID;
					Green[r - 1][c] = 0;

					break;
				}
				}
			}
		}
	}
	//파란색 업데이트
	else if (boardtype == 1) {
		for (int c = updatedPos; c >= 0; c--) {
			for (int r = 0; r < 4; r++) {
				//블록 없으면 무시
				if (Blue[r][c] == 0) continue;
				int nowID = Blue[r][c];
				int nowType = typeVersion[nowID];
				//블록은 있는데 1x2 블록의 윗부분이면 무시 (이미 옮겼으므로)
				if (nowType == 2 && c != 5 && Blue[r][c+1] == nowID) continue;

				switch (nowType) {
				case 1: {  //1x1
					for (int temp_c = 5; temp_c > c; temp_c--) {
						if (Blue[r][temp_c] == 0) {
							Blue[r][temp_c] = nowID;
							Blue[r][c] = 0;
							break;
						}
					}
					break;
				}
				case 2: {  //1x2

					if (c == 0) break;
					int result_c = c;
					for (int temp_c = c+1; temp_c <= 5; temp_c++) {
						if (Blue[r][temp_c] == 0) {
							result_c = temp_c;
						}
						else break;
					}
					if (result_c == c) break;
					Blue[r][result_c] = nowID;
					Blue[r][c] = 0;
					if (Blue[r][c - 1] != nowID) break;
					Blue[r][result_c - 1] = nowID;
					Blue[r][c - 1] = 0;

					break;
				}
				case 3: {  //2x1
					if (r == 3) break;
					int result_c = c;
					for (int temp_c = c+1; temp_c <=5 ; temp_c++) {
						if (Blue[r][temp_c] == 0 && Blue[r + 1][temp_c] == 0) {
							result_c = temp_c;
						}
						else break;
					}
					if (result_c == c) break;
					Blue[r][result_c] = nowID;
					Blue[r][c] = 0;
					if (Blue[r + 1][c] != nowID) break;
					Blue[r + 1][result_c] = nowID;
					Blue[r + 1][c] = 0;

					break;
				}

				}
			}
		}

	}
}

void solution(){


	cin >> t >> startRow >> startCol; //(r,c)에 t type의 블록 
	typeVersion[blockID] = t;
	//초록색 보드에 이동할 수 있는 칸으로 이동 (경계 또는 블록 만날 때까지)   --> 나눠지지 않음
	//O(12)
	//int blockGreenRow = 0;   //최종적으로 놓을수 있는 행
	//for (int r = 5; r >= 0; r--) {   
	//	bool valid = true;
	//	for (int c = startCol; c <= startCol + t_size_c[t]; c++) {
	//		if (Green[r][c] != 0) valid = false;
	//	}

	//	if(valid) {
	//		blockGreenRow = r;
	//		break;
	//	}
	//}
	int blockGreenRow_1 = 0;
	int blockGreenRow_2 = 0;
	for (int r = 0; r <= 5; r++) {
		if (Green[r][startCol] != 0) break;
		blockGreenRow_1 = r;
	}
	for (int r = 0; r <= 5; r++) {
		if (Green[r][startCol + 1] != 0) break;
		blockGreenRow_2 = r;
	}


	if(t == 1){
		Green[blockGreenRow_1][startCol] = blockID;
	}
	else if (t == 2) {
		int row = min(blockGreenRow_1, blockGreenRow_2);
		Green[row][startCol] = blockID;
		Green[row][startCol + 1] = blockID;
	}
	else if (t == 3) {
		Green[blockGreenRow_1][startCol] = blockID;
		Green[blockGreenRow_1 - 1][startCol] = blockID;
	}
	
	
	
	//파란색 보드에 이동할 수 있는 칸으로 이동 (경계 또는 블록 만날 때까지)   --> 나눠지지 않음
	//O(12)
	//int blockBlueCol = 0;
	//for (int c = 5; c >= 0; c--) {
	//	bool valid = true;
	//	for (int r = startRow; r <= startRow + t_size_r[t]; r++) {
	//		if (Blue[r][c] != 0) valid = false;
	//	}
	//	if (valid) {
	//		blockBlueCol = c;
	//		break;
	//	}
	//}

	
	int blockBlueCol_1 = 0;
	int blockBlueCol_2 = 0;
	for (int c = 0; c <= 5; c++) {
		if (Blue[startRow][c] != 0) break;
		blockBlueCol_1 = c;
	}
	for (int c = 0; c <= 5; c++) {
		if (Blue[startRow + 1][c] != 0) break;
		blockBlueCol_2 = c;
	}
	


	if (t == 1) {
		Blue[startRow][blockBlueCol_1] = blockID;
	}
	
	else if (t == 2) {
		Blue[startRow][blockBlueCol_1] = blockID;
		Blue[startRow][blockBlueCol_1 - 1] = blockID;
	}
	else if (t == 3) {
		
		int col = min(blockBlueCol_1, blockBlueCol_2);
		Blue[startRow][col] = blockID;
		Blue[startRow + 1][col] = blockID;
	}

	/*
	(만약 1x1 또는 1x2가 특별칸에 걸쳤다면 continue)

	초록색 보드의 행이 차있는 곳 있는지 확인
	있다면 -> 없어질 때까지 수행 (점수++)
	*/

	bool greenFilled = true;
	if (t == 1) {
		if (blockGreenRow_1 <= 1) greenFilled = false;
	}
	else if (t == 2) {
		if (min(blockGreenRow_1, blockBlueCol_2) <= 1) greenFilled = false;
	}

	while (greenFilled) {
		
		bool isUpdated = false;

		for (int r = 2; r <= 5; r++) {
			bool isFilled = true;
			for (int c = 0; c < 4; c++) {
				if (Green[r][c] == 0) {
					isFilled = false;
					break;
				}
			}

			//만약 차있다면
			if (isFilled) {
				score++;
				for (int c = 0; c < 4; c++) {
					Green[r][c] = 0;
				}
				updateBoard(0, r);
				isUpdated = true;
				break;
			}
		}

		if (!isUpdated) break;
	}

	/*
	(만약 1x1 또는 2x1가 특별칸에 걸쳤다면 continue)

	파란색 보드의 열이 차있는 곳 있는지 확인
	있다면 -> 없어질 때까지 수행 (점수++)
	*/
	bool blueFilled = true;
	if (t == 1) {
		if (blockBlueCol_1 <= 1) blueFilled = false;
	}
	else if (t == 2) {
		if (min(blockBlueCol_1, blockBlueCol_2) <= 1) {
			blueFilled = false;
		}
	}

	while (blueFilled) {

		bool isUpdated = false;

		for (int c = 2; c <= 5; c++) {
			bool isFilled = true;
			for (int r = 0; r < 4; r++) {
				if (Blue[r][c] == 0) {
					isFilled = false;
					break;
				}
			}

			//만약 차있다면
			if (isFilled) {
				score++;
				for (int r = 0; r < 4; r++) {
					Blue[r][c] = 0;
				}
				updateBoard(1, c);
				isUpdated = true;
				break;
			}
		}

		if (!isUpdated) break;
	}


	//초록색 보드의 연한 칸 (행) 확인 -> 만약 있다면 행의 수만큼 가장 아래 행 삭제
	int GreenEraseCnt = 0;
	int BlueEraseCnt = 0;

	for (int r = 0; r <= 1; r++) {
		for (int c = 0; c < 4; c++) {
			if (Green[r][c] != 0) {
				GreenEraseCnt++;
				break;
			}
		}
	}

	for (int c = 0; c <= 1; c++) {
		for (int r = 0; r < 4; r++) {
			if (Blue[r][c] != 0) {
				BlueEraseCnt++;
				break;
			}
		}
	}

	for (int r = 5; r > 5 - GreenEraseCnt; r--) {
		for (int c = 0; c < 4; c++) {
			Green[r][c] = 0;
		}
	}

	for (int c = 5; c > 5 - BlueEraseCnt; c--) {
		for (int r = 0; r < 4; r++) {
			Blue[r][c] = 0;
		}
	}

	if (GreenEraseCnt != 0) {
		for (int r = 5-GreenEraseCnt; r >= 2-GreenEraseCnt; r--) {
			for (int c = 0; c < 4; c++) {
				Green[r + GreenEraseCnt][c] = Green[r][c];
				Green[r][c] = 0;
			}
		}
	}
	if (BlueEraseCnt != 0) {
		for (int c = 5 - BlueEraseCnt; c >= 2 - BlueEraseCnt; c--) {
			for (int r = 0; r < 4; r++) {
				Blue[r][c + BlueEraseCnt] = Blue[r][c];
				Blue[r][c] = 0;
			}
		}
	}
	



	//파란색 보드의 연한 칸 (열) 확인 -> 만약 있다면 열의 수만큼 가장 오른쪽 열 삭제


	//목표: 얻은점수와 타일이 있는 칸의 개수

	blockID++;

}

int main() {

	ios::sync_with_stdio(false); 
	cin.tie(NULL); cout.tie(NULL);


	cin >> N;
	for (int i = 0; i < N; i++) {
		solution();
		int debugging = -1;
	}

	//남아있는 타일 개수 세기
	int cnt = 0;
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 4; c++) {
			if (Green[r][c] != 0) cnt++;
			if (Blue[c][r] != 0) cnt++;
		}
	}

	cout << score << "\n" << cnt;
	

	//점수, 타일 개수 출력

	return 0;
}

/*
문제 분석

(x, y) : (행, 열)
칸 색깔 : 빨 파 초

1. 블록 놓을 위치 선택 후 이동

1) 빨간색에 놓을 경우 : 그위치에서 초록색, 파란색으로 이동
(경계 만날 때까지)


2) 하나의 행이 가득 차면 타일 모두 사라짐 (안사라질때까지)
3) 빈 행(빨강)/열(파랑) 채워서 이동
4) +1점 획득


2. 특별한 칸 

1) 초록색 : 0~1번 행
블록이 있는 행의 수 만큼 아래 사라짐 + 이동

2) 파란색 0~1번 열
블록이 있는 열의 수 만큼 오른쪽 사라짐 + 이동


3. 우선순위 : 행/열 칸 완성 다 완료 후에 점수획득 후 연한칸 처리


4. 블록이 나눠져서 떨어지는 일은 없고 사라졌을 때만 가능



목표 : 얻은점수와 타일이 있는 칸의 개수
입력)
N : 블록 놓는 횟수
t x y : type, (x,y)

*/

/*

while (greenFilled) {

		for (int r = nowRow; r > 1; r--) {
			bool isFilled = true;
			for (int c = 0; c < 4; c++) {
				if (Green[r][c] != 0) {
					isFilled = false;
					break;
				}
			}

			//만약 차있다면
			if (isFilled) {
				for (int c = 0; c < 4; c++) {
					Green[r][c] = 0;
				}
				//updateBoard(0);
			}
		}
	}

*/


/*
로직 수정

내려갈 수 있는 길인지 찾아나가야함
*/