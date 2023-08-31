#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;
	vector<int> Length(N,0);
	int start = 0;
	int end = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> Length[i];

		if (start < Length[i])
		{
			start = Length[i];   //시작 인덱스
		}
		end += Length[i];
		
	}
	//sort(Length.begin(),Length.end());
	//start = Length.back(); end = sum;
	
	while (start <= end)
	{
		int middle = (start + end) / 2;
		int sum = 0;
		int count = 0;

		for (int i = 0; i < N; i++)
		{
			if (count >= M) break;
			//이전 합과 길이를 더했을 때 중앙값보다 크면 다음 블루레이에 넣어야함
			if (sum + Length[i] > middle)
			{
				count++;  //블루레이 개수 추가
				sum = 0;  //이전 합은 다시 0으로
			}
			sum += Length[i]; //현재 길이 더해줌
		}
		if (sum != 0)
		{
			count++;
		}
		if (count > M)
		{
			//M개에 모두 저장 불가능하므로 블루레이 크기 중앙값보다 큰 데이터에서 찾기
			 start = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	cout << start << "\n";
	return 0;
}