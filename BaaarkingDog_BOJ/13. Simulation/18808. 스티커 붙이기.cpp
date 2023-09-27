#include<iostream>
#include<vector>

using namespace std;


//���� �м�
//���� ���� �ͺ��� ���ʴ�� ���ڿ� ���缭 ����

//���̴� ���
//1. ��ƼĿ�� ȸ�� ��Ű�� ����
//2. �ٸ� ��ƼĿ�� ��ħ X , ��Ʈ�� ��� X
//3. �켱���� : ��, ����
//4. ������ ��ġ�� ��ƼĿ ���� (���� ��ġ ���ٸ� 90�� ������ �ٽ� Ȯ��)
//5. 0, 90, 180, 270 �� ������ �׳� ����


//��� ĭ�� ä�����°�?


//N, M 40����
//K : ��ƼĿ ����
//��ƼĿ ����

struct pos {
	int row;
	int col;
};

int N, M;
int Map[40][40] = { 0, };
int K;
vector<vector<pos>> Sticker;  //��ƼĿ ����
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

//90�� ������ �Լ�
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

	for (int i = 0; i < K; i++) {   //�Է� �ޱ�
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