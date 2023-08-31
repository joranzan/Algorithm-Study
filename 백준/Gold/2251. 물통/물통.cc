#include<iostream>
#include<queue>

using namespace std;

static const int Sender[6] = {0,0,1,1,2,2};
static const int Reciever[6] = { 1,2,0,2,0,1 };
//두개의 물 양을 알면 하나는 정해져 있으므로 두개로만 체크
static bool Visited[201][201] = { false, };
static bool Answer[201] = { false };
static int Capacity[3];

void BFS();

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> Capacity[0] >> Capacity[1] >> Capacity[2];

	BFS();
	for (int i = 0; i <= Capacity[2]; i++)
	{
		if (Answer[i])
		{
			cout << i << " ";
		}
	}
	

	return 0;
}

void BFS()
{
	queue<pair<int, int>> myQueue;
	myQueue.push(make_pair(0, 0));
	Visited[0][0] = true;
	Answer[Capacity[2]] = true;

	while (!myQueue.empty())
	{
		pair<int, int> current_node = myQueue.front();
		myQueue.pop();
		int A = current_node.first;
		int B = current_node.second;
		int C = Capacity[2] - A - B;

		for (int dir = 0; dir < 6; dir++)
		{
			int next[] = { A,B,C };
			next[Reciever[dir]] += next[Sender[dir]];  //일단 보내는 물통에서 전부 받는 물통으로 옮김
			next[Sender[dir]] = 0;

			if (next[Reciever[dir]] > Capacity[Reciever[dir]])
			{
				next[Sender[dir]] = next[Reciever[dir]] - Capacity[Reciever[dir]];  //초과한 만큼 다시 돌려줌
				next[Reciever[dir]] = Capacity[Reciever[dir]];  //용량만큼 저장				
			}
			if (Visited[next[0]][next[1]]) continue;
			Visited[next[0]][next[1]] = true;
			myQueue.push(make_pair(next[0], next[1]));
			if (next[0] == 0)
			{
				Answer[next[2]] = true;
			}
			
		}
	}
}