#include<iostream>
#include<vector>

using namespace std;

//점화식
//K세대 드래곤 커브 : K-1 드래곤 커브 끝점 기준 90도 시계방향 회전


//드래곤 커브 : 3가지 속성
//시작점, 시작 방향, 세대
struct Info {
	int row;
	int col;
	int dir;
	int level;
};
//0,0 ~ 100,100
int Map[101][101]={0,};
int N;  //드래곤 커브 개수
Info Curve[20];
int Answer = 0;
//0 1 2 3  우 상 좌 하
const int dr[4] = { 0,-1,0,1 };
const int dc[4] = { 1,0,-1,0 };

//시계반대 상 좌 하 우  //1 2 3 0
int clockwise(int dir) {
	if (dir == 0) {
		return 1;
	}
	else if (dir == 1) {
		return 2;
	}
	else if (dir == 2) {
		return 3;
	}
	else if (dir == 3) {
		return 0;
	}
}

void Move(Info now) {
	//방향으로 담고
	//배열 뒤에서부터 방향 시계방향 기록
	//기존 배열에 추가
	vector<int> acc;
	int start_r = now.row;
	int start_c = now.col;
	acc.push_back(now.dir);
	for (int i = 0; i < now.level; i++) {
		vector<int> temp;
		for (int j = acc.size()-1; j >= 0; j--) {
			int nowDir = acc[j];
			temp.push_back(clockwise(nowDir));
		}
		for (int j = 0; j < temp.size(); j++) {
			acc.push_back(temp[j]);
		}
	}

	Map[start_r][start_c] = 1;
	for (int i = 0; i < acc.size(); i++) {
		start_r += dr[acc[i]];
		start_c += dc[acc[i]];
		Map[start_r][start_c] = 1;
	}
}

//목표: 4꼭지점이 모두 드래곤 커브에 포함인 1x1 정사각형 개수
void checkSquare() {

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int p1 = Map[i][j];
			int p2 = Map[i + 1][j];
			int p3 = Map[i][j + 1];
			int p4 = Map[i + 1][j + 1];
			if (p1 == 1 && p2 == 1 && p3 == 1 && p4 == 1) {
				Answer++;
			}
				
		}
	}

}

void input() {
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		Curve[i] = { y, x, d, g };
	}

}
void solution() {
	for (int i = 0; i < N; i++) {
		Move(Curve[i]);
	}

	checkSquare();
	cout << Answer << "\n";

}
//101 * 102 * 203 /3

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	input();
	solution();

	return 0;
}

//(3,3) 우 1세대
//(2,4) 상 3세대
//(2,4) 좌 1세대

//넣을때 끝점 빼고 회전 시킴

//하 우 상 우 상 좌 상 우 | 상 좌 하 좌 상 좌 상 우