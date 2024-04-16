#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int Map[10][10] = { 0, };
int Answer = 2112345678;
int PaperCnt[6] = { 0, };

void Recursion(int cnt) {

	//기저 조건
	if (cnt >= Answer) return;

	bool allDone = true;

	int nowCnt = 0;

	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (Map[r][c] == 1) {
				allDone = false;
				break;
			}
		}
		if (!allDone) break;
	}

	if (allDone) {
		Answer = min(Answer, cnt);
	}
	


	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (Map[r][c] == 0) continue;

			for (int PaperSize = 5; PaperSize >= 1; PaperSize--) {

				//만약 격자 밖 벗어난다면 무시
				if (r + PaperSize > 10 || c + PaperSize > 10) continue;
				if (PaperCnt[PaperSize] >= 5) continue;
				//붙일 수 있는지 체크
				bool isValid = true;
				for (int i = r; i < r + PaperSize; i++) {
					for (int j = c; j < c + PaperSize; j++) {
						if (Map[i][j]==0) {
							isValid = false;
							break;
						}
					}
					if (!isValid) break;
				}

				//붙일 수 있다면
				if (isValid) {
					
					//붙이고

					PaperCnt[PaperSize]++;

					for (int i = r; i < r + PaperSize; i++) {
						for (int j = c; j < c + PaperSize; j++) {
							Map[i][j] = 0;
						}
					}

					//다음 찾으러 감
					Recursion(cnt + 1);

					PaperCnt[PaperSize]--;

					for (int i = r; i < r + PaperSize; i++) {
						for (int j = c; j < c + PaperSize; j++) {
							Map[i][j] = 1;
						}
					}
				}
			}
			return;
		}
	}
	
}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			cin >> Map[r][c];
		}
	}

	Recursion(0);

	if (Answer == 2112345678) cout << "-1";
	else cout << Answer;


	return 0;
}

/*
문제 분석

색종이(5종류) : 1×1, 2×2, 3×3, 4×4, 5×5

1. 10x10 색종이 덮기
2. 0과 1중 1은 모두 색종이로 덮어야함
3. 색종이 덮는 조건
	1) 겹치면 안됨
	2) 격자 밖 안됨
	3) 칸의 경계와 일치 
	4) 0이 적힌 칸은 색종이 있으면 안됨


1. 5x5부터 가능한 곳 찾기
	1) cnt <=5 : 넘어감
	2) cnt > 5 : Combination(C,5)

	2. 4x4부터 가능한 곳 찾기 
		1) cnt <=5 : 넘어감
		2) cnt > 5 : Combination(C,5)

		3. 3x3부터 가능한 곳 찾기
			1) cnt <=5 : 넘어감
			2) cnt > 5 : Combination(C,5)

			4. 2x2부터 가능한 곳 찾기
				1) cnt <=5 : 넘어감
				2) cnt > 5 : Combination(C,5)

				5. 1x1부터 가능한 곳 찾기
					1) cnt <=5 : Answer값 갱신
					2) cnt > 5 : 그냥 Return



*/

/*
TC 5)

(1,1), (1,2), (2,1), (2,2), (2,3), 
(3,2), (3,3), (3,4), (3,5), (3,6),
(4,3), (4,4), (4,5), (4,6)
(5,4), (5,5), (5,6)
(6,2)


*/