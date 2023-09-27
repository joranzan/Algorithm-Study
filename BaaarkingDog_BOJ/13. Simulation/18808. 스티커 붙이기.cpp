#include<iostream>
#include<vector>

using namespace std;


//문제 분석
//먼저 받은 것부터 차례대로 격자에 맞춰서 붙임

//붙이는 방법
//1. 스티커를 회전 시키지 않음
//2. 다른 스티커와 겹침 X , 노트북 벗어남 X
//3. 우선순위 : 위, 왼쪽
//4. 선택한 위치에 스티커 붙임 (만약 위치 없다면 90도 돌려서 다시 확인)
//5. 0, 90, 180, 270 다 없으면 그냥 버려


//몇개의 칸이 채워졌는가?


//N, M 40이하
//K : 스티커 개수
//스티커 정보

struct pos {
	int row;
	int col;
};

int N, M;
int Map[40][40] = { 0, };
int K;
vector<vector<pos>> Sticker;  //스티커 정보
pos StickerSize[101] = { 0, };


bool checkValid(int stickerNum) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			bool flag = true;
			for (auto &point : Sticker[stickerNum]) {
				int nowRow = point.row + i;
				int nowCol = point.col + j;

				if (nowRow < 0 || nowCol < 0 || nowRow >= N || nowCol >= M || Map[nowRow][nowCol] == 1) {
					flag = false;
					break;
				}
			}

			if (flag) {
				for (auto& point : Sticker[stickerNum]) {
					int nowRow = point.row + i;
					int nowCol = point.col + j;
					Map[nowRow][nowCol] = 1;
					
				}
			return true;
			}
		}
	}
	return false;
}

//90도 돌리는 함수
void Rotation(int stickerNum) {

	int debugging[11][11] = { 0, };

	int height = StickerSize[stickerNum].row;
	int width = StickerSize[stickerNum].col;

	int arr[11][11] = { 0, };
	int temp[11][11] = { 0, };
	for (auto& point : Sticker[stickerNum]) {
		int nowRow = point.row;
		int nowCol = point.col;
		point.row = nowCol;
		point.col = (height-1) - nowRow;

		debugging[point.row][point.col] = 1;

	}
	
	StickerSize[stickerNum].row = width;
	StickerSize[stickerNum].col = height;

	int ret = -1;

}


int solution() {

	for (int i = 0; i < K; i++) {
		if (checkValid(i)) continue;
		else {
			for (int dir = 1; dir <= 3; dir++) {
				Rotation(i);
				if (checkValid(i)) break;
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] == 1) cnt++;
		}
	}

	return cnt;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;
	Sticker.resize(K);

	for (int i = 0; i < K; i++) {   //입력 받기
		int h, w;
		cin >> h >> w;
		StickerSize[i] = { h,w };
		for (int r = 0; r < h; r++) {
			for (int c = 0; c < w; c++) {
				int temp;
				cin >> temp;
				if (temp == 1) {
					Sticker[i].push_back({ r,c });
				}
			}
		}
	}
	

	cout << solution();

	return 0;
}