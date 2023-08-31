#include<iostream>
#include<vector>
#include<algorithm>  //max, min 함수 존재
#include<cstring>

using namespace std;

// D: 두께  <- rowSize
// W: 가로크기 <- colSize
// K: 합격기준

int D, W, K;
int Film[15][25];
int Answer = 15;
int cnt = 0;
vector<int> path;  //-1 0 1


void input() //초기화 잘하기
{
    Answer=210000000;
    cnt=0;
	cin >> D >> W >> K;
	for (int row = 0; row < D; row++)
	{
		for (int col = 0; col < W; col++)
		{
			cin >> Film[row][col];
		}
	}
}


bool isValid()
{
	for (int col = 0; col < W; col++)
	{
		int cont = 1;
		int prev = Film[0][col];
		if (path[0] != -1) prev = path[0];
		int contMax = 1;

		for (int row = 1; row < D; row++)
		{
			int nowValue = Film[row][col];
			if (path[row] != -1)
			{
				nowValue = path[row];
			}
			if (prev == nowValue) cont++;

			else 
				cont = 1;

			prev = nowValue;
			contMax = max(contMax, cont);
		}
		if (contMax < K) return false;  //합격기준 미달
	}
	return true; //합격!
}

void DFS(int now)	
{
	// now층에서 어떻게 할 것인가?

	//기저 조건
	if (now >= D)   //끝났으면 멈춰!
	{
		// 0~ D-1층까지 뽑기 완료(D개의 층의 뽑기 완료)

		// 이번에 뽑은(약품을 처리하는) 방식으로 합격 기준에 부합하는가?
		
		if (isValid())
		{
			Answer = min(Answer, cnt);
		}
		return;
	}

	// 약품을 어떻게 할 것인가?
	// i ==-1일때: 약품사용 x
	// i == 0일때: 약품 A
	// i == 1일때: 약품 B
	for (int i = -1; i <= 1; i++)
	{
		// K개 붙여서 같게 만들면 끝이라 더 필요 X
		if (i != -1 && cnt + 1 > K) continue;
		// 이미 구한 답보다 더 많이 필요?
		if (i != -1 && cnt + 1 >= Answer) continue;

		if (i != -1) cnt++;
		path.push_back(i);

		DFS(now + 1);

		if (i != -1) cnt--;
		path.pop_back();
	}
	
}

void solution()
{
	//다양한 경로를 모두 해보기
	DFS(0);
}



int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++)
	{
		input();
		solution();
		cout << "#" << test << " " << Answer << "\n";
	}
	return 0;
}
