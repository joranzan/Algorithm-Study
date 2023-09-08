#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

char map[10][11] = {};    //판때기 ㅋㅋ

class Info
{
public:
	int rx, ry, bx, by, count = 0;
};


int BFS(Info start)
{
	const int dx[4] = { -1,1,0,0 };
	const int dy[4] = { 0,0,-1,1 };

	bool visited[11][11][11][11] = { false, };
	queue<Info>  q;
	q.push(start);
	visited[start.rx][start.ry][start.bx][start.by] = true;

	int result = -1;
	while (!q.empty())
	{
		Info current = q.front();
		q.pop();
		//10 넘어가면 안됨
		if (current.count > 10) break;
		if (map[current.ry][current.rx] == 'O' && map[current.by][current.bx] != 'O')
		{
			result = current.count;
			break;
		}
		Info next;
		for (int dir = 0; dir < 4; dir++)
		{
			
			next = current;

			while (1)    //빨간공(한 칸씩 이동하는게 아니라 벽이나 구멍을 만났을 때 까지 이동)
			{
				if (map[next.ry][next.rx] != '#' && map[next.ry][next.rx] != 'O')
				{
					next.ry += dy[dir];
					next.rx += dx[dir];
				}
				else
				{
					if (map[next.ry][next.rx] == '#')  //벽 만났을 때
					{
						next.ry -= dy[dir];
						next.rx -= dx[dir];
					}
					break;
				}

			}
			while (1)    //파란공(한 칸씩 이동하는게 아니라 벽이나 구멍을 만났을 때 까지 이동)
			{
				if (map[next.by][next.bx] != '#' && map[next.by][next.bx] != 'O')
				{
					next.by += dy[dir];
					next.bx += dx[dir];
				}
				else
				{
					if (map[next.by][next.bx] == '#')  //벽 만났을 때
					{
						next.by -= dy[dir];
						next.bx -= dx[dir];
					}
					break;
				}
			}
			//5번문제 시읻이이이이발
			if (map[next.by][next.bx] == 'O')
			{
				if (map[next.ry][next.rx] == 'O')
				{
					int red_distance = abs(next.ry - current.ry) + abs(next.rx - current.rx); //어차피 x,y 둘중 하나는 0
					int blue_distance = abs(next.by - current.by) + abs(next.bx - current.bx); //어차피 x,y 둘중 하나는 0

					if (blue_distance < red_distance) {
						continue;
					}
				}
				else continue;
			}

			if (next.ry == next.by && next.rx == next.bx)     //둘다 벽을 만나서 back했는데 구멍이 아닌 경우 예외처리 **
			{
				if (map[next.ry][next.rx] != 'O')   //어차피 둘다 빠진 경우에는 return -1 할거니까
				{
					//더 멀리 온 애는 냅두고 나머지 새끼는 한칸 back
					int red_distance = abs(next.ry - current.ry) + abs(next.rx - current.rx); //어차피 x,y 둘중 하나는 0
					int blue_distance = abs(next.by - current.by) + abs(next.bx - current.bx); //어차피 x,y 둘중 하나는 0
					if (red_distance < blue_distance)
					{
						next.by -= dy[dir];
						next.bx -= dx[dir];
					}
					else
					{
						next.ry -= dy[dir];
						next.rx -= dx[dir];
					}
				}
			}
			if (!visited[next.rx][next.ry][next.bx][next.by])
			{
				visited[next.rx][next.ry][next.bx][next.by] = true;
				next.count = current.count + 1;
				q.push(next);
			}
		}
	}
	//순회하면서 queue가 비어있는 상태인데 못나온 경우는 같이 나온 경우
	return result;
}
void init()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
}

int main(void)
{
	init();
	Info Start;
	int N, M;
	cin >> N >> M;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			cin >> map[y][x];
			if (map[y][x] == 'R')
			{
				Start.rx = x; Start.ry = y;
			}
			if (map[y][x] == 'B')
			{
				Start.bx = x; Start.by = y;
			}
		}
	}

	cout << BFS(Start) << "\n";

	return 0;
}