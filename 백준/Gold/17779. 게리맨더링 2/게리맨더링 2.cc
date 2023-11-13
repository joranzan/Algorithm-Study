#include<iostream>
#include<algorithm>

using namespace std;

//문제 분석
//NxN 격자 (1,1)
//각 구역 : 5개의 선거구 중 하나
//각 선거구 : 최소 1개 구역 포함, 연결되어있어야함(인접)
//중간에 통하는 인접한 구역 : 0개 이상

//선거구 나누기
//1. 기준점 : x,y (d1,d2)
//2. 경계선 (5번선거구)
	//1) 

int N;
int A[21][21] = { 0, };
int minValue = 2112345678;



//최대 구하는 함수

//기준점 (r : 1) (c: 2 ~ N-1)

//왼쪽 꼭지점 (r: 2 ~ N-1) (c: 1)
//오른쪽 꼭지점 (r : N - 1 ~ 2) c: N
//아래 꼭지점 (r: N) (c: N-1~ 2)

//(N-r+1)


void Division(int x, int y) {
	// d1, d2 ≥ 1
	// 1 ≤ x < x + d1 + d2 ≤ N
	// 1 ≤ y - d1 < y < y + d2 ≤ N
	
	int debugging = -1;

	for (int d1 = 1; d1 <= y-1; d1++) {
		for (int d2 = 1; d2 <= N - y; d2++) {

			if (x + d1 + d2 > N) continue;


			int Map[21][21] = { 0, };
			Map[x][y] = 5;

			int nowRow = x;
			int left_offset = -1;
			int right_offset = 1;
			int leftCol = y;
			int rightCol = y;

			for (int i = 1; i <= d1 + d2; i++) {
				leftCol += left_offset;
				rightCol += right_offset;
				if (leftCol == y - d1) left_offset = 1;
				if (rightCol == y + d2) right_offset = -1;

				for (int j = leftCol; j <= rightCol; j++) {
					Map[nowRow + i][j] = 5;
				}
				
			}


			for (int r = 1; r <= N; r++) {
				for (int c = 1; c <= N; c++) {

					if (Map[r][c] == 5) continue;
					else if (1 <= r && r < x + d1 && 1 <= c && c <= y) Map[r][c] = 1;
					else if (1 <= r && r <= x + d2 && y < c && c <= N) Map[r][c] = 2;
					else if (x + d1 <= r && r <= N && 1 <= c && c < y - d1 + d2) Map[r][c] = 3;
					else if (x + d2 < r && r <= N && y - d1 + d2 <= c && c <= N) Map[r][c] = 4;
				}
			}

			int sum[6] = { 0, };
			
			for (int r = 1; r <= N; r++) {
				for (int c = 1; c <= N; c++) {

					sum[Map[r][c]] += A[r][c];
				}
			}
			sort(sum + 1, sum + 6);
			int min__ = sum[1];
			int max__ = sum[5];
			if (max__ - min__ == 158) {
				int debugging = -1;
			}
			minValue = min(minValue, max__ - min__);

		}
	}
}

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
}

void solution() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Division(i, j);
		}
	}
	cout << minValue;
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();

	return 0;
}

//
//int minValue = 2112345678;
//
//
//void findMin() {   //1200
//
//
//
//	for (int i = 1; i <= N; i++) {
//		for (int j = 1; j <= N; j++) {
//
//			if (i - 1 <= 0 || i + 1 > N || j - 1 <= 0 || j + 1 > N) continue;
//			int sum = A[i][j] + A[i - 1][j] + A[i + 1][j] + A[i][j - 1] + A[i][j + 1];
//			minValue = min(minValue, sum);
//		}
//	}
//
//}