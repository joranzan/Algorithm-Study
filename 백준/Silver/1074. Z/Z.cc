#include<iostream>
#include<cmath>

using namespace std;

//시간복잡도 5000만 이하

struct pos {
	int row;
	int col;
};

int N, R, C;
int rowLength, colLength;

void Z_Search(pos start, pos end, int n, int cnt) {

	//cout << n << "\n";
	//탈출 조건
	

	//if (end.row == R && end.col == C) {
	//	cout << cnt + 3 * NumofPrev;
	//	return;
	//}
	//else if (start.row == R && start.col == C) {
	//	cout << cnt;
	//	return;
	//}


	//조건 설정하기
	if (n == 0) {
		cout << cnt << "\n";
		return;
	}
	

	int NumofPrev = int(pow(2, n - 1)) * int((pow(2, n - 1)));
	int mid_row = (start.row + end.row) / 2;
	int mid_col = (start.col + end.col) / 2;

	if (0 <= R && R <= mid_row) {
		if (0 <= C && C <= mid_col) {  //1번째 사분면
			pos temp_start = { start.row, start.col };
			pos temp_end = { mid_row, mid_col };

			Z_Search(temp_start, temp_end, n - 1, cnt);
		}
		else {   //2번째 사분면
			pos temp_start = { start.row, mid_col + 1 };
			pos temp_end = { mid_row, end.col };

			Z_Search(temp_start, temp_end, n - 1, cnt + NumofPrev);
		}
	}
	else if (mid_row < R) {
		if (0 <= C && C <= mid_col) {  //3번째 사분면
			pos temp_start = { mid_row + 1, start.col };
			pos temp_end = { end.row, mid_col };

			Z_Search(temp_start, temp_end, n - 1, cnt + (NumofPrev * 2));
		}
		else {   //4번째 사분면
			pos temp_start = { mid_row + 1, mid_col + 1 };
			pos temp_end = { end.row, end.col };

			Z_Search(temp_start, temp_end, n - 1, cnt + (NumofPrev * 3));
		}
	}

}


int main() {

	cin >> N;
	cin >> R >> C;

	rowLength = int(pow(2, N));
	colLength = rowLength;
	Z_Search({ 0,0 }, { rowLength - 1,colLength - 1 }, N, 0);

	return 0;
}

//N=1일 때 그냥 Z 방문

//N=2일 때 결국 N이 1일때로 돌아가서 Z방문

//N=3일때 결국 N이 1일때로 돌아가서 다하고 N이 2일 때 다 하고 돌아와서 Z

//basic condition : start=end일때 그냥 그대로 cnt++ 하고 return

//0 ~ 2^(N-1)-1   승


//이분 탐색 해야하네..


//start<=row보다 클때
//