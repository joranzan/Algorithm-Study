#include<iostream>
#include<algorithm>

using namespace std;

//문제분석

//폴리오미노
//정사각형 서로 겹치면 안됨
//도형은 모두 연결되어있어야함(반드시 변끼리)
//회전 / 대칭 가능


int N, M;
int Map[500][500] = { 0, };
int Ans = 0;


//대칭 같음   (1자)
void shape1() {   

		// 1 1 1 1

		for (int i = 0; i < N; i++) {
			int left = 0;
			int right = 3;
			int sum = 0;
			for (int j = left; j <= right; j++) {
				sum += Map[i][j];
			}

			while (right < M) {
				
				Ans = max(Ans, sum);

				sum -= Map[i][left];
				left++;
				right++;
				if (right >= M) break;
				sum += Map[i][right];
			}
		}

		//1
		//1
		//1
		//1
		for (int i = 0; i < M; i++) {
			int left = 0;
			int right = 3;
			int sum = 0;
			for (int j = left; j <= right; j++) {
				sum += Map[j][i];
			}

			while (right < N) {

				Ans = max(Ans, sum);

				sum -= Map[left][i];
				left++;
				right++;
				if (right >= N) break;
				sum += Map[right][i];
			}
		}
}

//대칭 같음, 회전 같음  (정사각형)
void shape2() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i + 1 >= N) continue;
			if (j + 1 >= M) continue;
			int sum = Map[i][j] + Map[i + 1][j] + Map[i][j + 1] + Map[i + 1][j + 1];
			Ans = max(Ans, sum);
		}
	}
}

//ㄴ자 + 빠큐 모양
//대칭 다름, 회전 다름
void shape3() {
	// 1
	// 1
	// 1
	for (int i = 0; i <= N-3; i++) {
		for (int j = 0; j < M; j++) {
			int sum = Map[i][j] + Map[i + 1][j] + Map[i + 2][j];	
			//1 3 5
			if (j - 1 >= 0) {
				int add1 = sum + Map[i][j - 1];
				int add2 = sum + Map[i + 1][j - 1];
				int add3 = sum + Map[i + 2][j - 1];
				Ans = max(Ans, add1);
				Ans = max(Ans, add2);
				Ans = max(Ans, add3);
			}
			//2 4 6
			if (j + 1 < M) {
				int add1 = sum + Map[i][j + 1];
				int add2 = sum + Map[i + 1][j + 1];
				int add3 = sum + Map[i + 2][j + 1];
				Ans = max(Ans, add1);
				Ans = max(Ans, add2);
				Ans = max(Ans, add3);
			}
		}
	}
	
	//1 1 1
	for (int c = 0; c <= M - 3; c++) {
		for (int r = 0; r < N; r++) {
			int sum = Map[r][c] + Map[r][c + 1] + Map[r][c + 2];
			//1 3 5
			if (r - 1 >= 0) {
				int add1 = sum + Map[r - 1][c];
				int add2 = sum + Map[r - 1][c + 1];
				int add3 = sum + Map[r - 1][c + 2];
				Ans = max(Ans, add1);
				Ans = max(Ans, add2);
				Ans = max(Ans, add3);
			}
			//2 4 6
			if (r + 1 < N) {
				int add1 = sum + Map[r + 1][c];
				int add2 = sum + Map[r + 1][c + 1];
				int add3 = sum + Map[r + 1][c + 2];
				Ans = max(Ans, add1);
				Ans = max(Ans, add2);
				Ans = max(Ans, add3);
			}
		}
	}


}

void shape4() {

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (r + 1 >= N) continue;
			if (r + 2 >= N) continue;
			if (c + 1 >= M) continue;
			int sum = Map[r][c] + Map[r + 1][c] + Map[r + 1][c + 1] + Map[r + 2][c + 1];
			Ans = max(Ans, sum);
		}
	}

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (c - 1 < 0) continue;
			if (c + 1 >= M) continue;
			if (r + 1 >= N) continue;
			int sum = Map[r][c] + Map[r + 1][c - 1] + Map[r][c + 1] + Map[r + 1][c];
			Ans = max(Ans, sum);
		}
	}

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (r - 1 < 0) continue;
			if (r + 1 >= N) continue;
			if (c + 1 >= M) continue;
			int sum = Map[r][c] + Map[r - 1][c + 1] + Map[r][c + 1] + Map[r + 1][c];
			Ans = max(Ans, sum);
		}
	}

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (r + 1 >= N) continue;
			if (c + 1 >= M) continue;
			if (c + 2 >= M) continue;
			int sum = Map[r][c] + Map[r][c + 1] + Map[r + 1][c + 1] + Map[r + 1][c + 2];
			Ans = max(Ans, sum);
		}
	}

}



void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
		}
	}
}

void solution() {
	shape1();
	shape2();
	shape3();
	shape4();

	cout << Ans << "\n";
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();



	return 0;
}