#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int R, C, m, sum;
int dx[] = { -1, 1,0, 0 };
int dy[] = { 0, 0, 1,-1 };

struct fish
{
	int r, c, s, d, z;
	bool dead;

	void init()
	{
		if (d <= 2) s %= (2 * R - 2);
		else	    s %= (2 * C - 2);
		dead = false, --d;
	}

	void move()
	{
		for (int i = 0; i < s; ++i)
		{
			if      (d == 0 && r == 1) d = 1;
			else if (d == 1 && r == R) d = 0;
			else if (d == 2 && c == C) d = 3;
			else if (d == 3 && c == 1) d = 2;

			r += dx[d];
			c += dy[d];
		}
	}
} s;

vector<fish> shark_info;
int shark_pos[101][101];

int main()
{
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> R >> C >> m;
	shark_info.resize(m);
	memset(shark_pos, -1, sizeof(shark_pos));

	register int i, j, k;
	for (i = 0; i < m; ++i)
	{
		cin >> s.r >> s.c >> s.s >> s.d >> s.z;
		s.init();
		shark_info[i] = s;
		shark_pos[s.r][s.c] = i;
	}
	if (m == 0)
	{
		cout << 0;
		return 0;
	}
	// 1. 낚시왕 이동
	for (i = 1; i <= C; ++i)
	{
		// 2. 가장 가까운 상어 잡기
		for (j = 1; j <= R; ++j)
		{
			const int &idx = shark_pos[j][i];
			if (idx != -1 && shark_info[idx].dead == false)
			{
				sum += shark_info[idx].z;
				shark_info[idx].dead = true;
				break;
			}
		}
        
		// 위치 테이블은 낚시왕이 잡을 때만 사용함 ( 초기화 )
		memset(shark_pos, -1, sizeof(shark_pos));

		// 3. 상어 이동
		for (k = 0; k < m; ++k)
		{
			fish &s = shark_info[k];
			if (s.dead) continue;

			s.move();
            
			// cur_idx 가 -1이면 빈 곳
			int &cur_idx = shark_pos[s.r][s.c];
			if (cur_idx == -1) cur_idx = k;
			else
			{
				// 4. 같은 칸에 두 상어 처리
				if (shark_info[cur_idx].z < s.z)
				{
					shark_info[cur_idx].dead = true;
					cur_idx = k;
				}
				else shark_info[k].dead = true;
			}
		}
	}
	cout << sum;
	return 0;
}