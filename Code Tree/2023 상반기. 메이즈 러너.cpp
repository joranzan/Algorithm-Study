//https://www.codetree.ai/training-field/frequent-problems/problems/maze-runner/description?page=1&pageSize=20

#include<iostream>
#include<vector>

using namespace std;

struct pos {
	int row;
	int col;
};

//문제 분석
//참가자 : M명   N x N 격자 (1,1)

//미로 상태
//1. 빈칸 : 참가자 이동 가능
//2. 벽 : 참가자 이동 불가 (1~9)
//   - 회전 시 내구도 1 깎임 (0되면 빈칸으로 변경)
//3. 출구 : 참가자 도달 시 탈출!


// 1초에 참가자 한칸 씩 움직임
// 움직이는 조건
// 1) 최단 거리 : abs(x1-x2) + abs(y1-y2)
// 2) 참가자 동시에 움직임 -> 다 움직이고 처리할거 처리해야함
// 3) 상하좌우 (빈칸만)  우선순위: 상하
// 4) 출구까지 최단거리 더 가까워지게만 움직임 가능
// 5) 움직일 곳 없으면 Stay
// 6) 한칸에 여러명 있어도 됨 (참가자 현재 위치 배열 만들기)


//미로 회전
//1명 이상의 참가자와 출구 포함한 가장 작은 정사각형
//우선 순위 : 좌상단 Row좌표 작은 애 -> 좌상단 Col 좌표 작은애
//시계방향 90 회전 (사람, 출구, 내구도 다 같이 돌아감)
//내구도 1 깎임

//모두 탈출 시 종료 -> 참가자의 이동거리 합 + 출구 좌표
int N, M;
pos Escape;  //출구 좌표


void rotation(int start_r, int start_c, int squareSize) {
	//시계방향 90 회전 (사람, 출구, 내구도 다 같이 돌아감)
	//내구도 1 깎임
}

void findSquare() {

	int squareSize = 2;
	while (squareSize <= N) {
		int e_r = Escape.row;
		int e_c = Escape.col;

		vector<pos> squareCandi;

		int min_r = e_r - (squareSize - 1);    //탐색 시작 좌측 상단 좌표 r
		int min_c = e_c - (squareSize - 1);    //탐색 시작 좌측 상단 좌표 c
		if (min_r <= 0) min_r = 1;
		if (min_c <= 0) min_c = 1;

		for (int left_r = min_r; left_r <= e_r; left_r++) {
			if (left_r <= 0 || left_r > N) continue;
			for (int left_c = min_c; left_c <= e_c; left_c++) {
				if (left_c <= 0 || left_c > N) continue;
				squareCandi.push_back({ left_r, left_c });
			}
		}
		bool found = false;
		pos Result;
		for (int i = 0; i < squareCandi.size(); i++) {
			int start_r = squareCandi[i].row;
			int start_c = squareCandi[i].col;

			int personCnt = 0;
			//1명 이상의 참가자와 출구 포함한 가장 작은 정사각형
			//우선 순위 : 좌상단 Row좌표 작은 애 -> 좌상단 Col 좌표 작은애
			for (int r = 0; r < squareSize; r++) {
				for (int c = 0; c < squareSize; c++) {
					int now_r = start_r + r;
					int now_c = start_c + c;

					//참가자 좌표 탐색하는 코드
					//참가자 존재하면 personCnt++
					if (personCnt >= 1) {
						found = true;
						Result = { start_r, start_c };
						break;
					}
					
					//break
				}
				if (found) break;
			}
			if (found) break;
		}
		if (found) {
			rotation(Result.row, Result.col, squareSize);
			break;
		}
	}
}



int main() {






	return 0;
}