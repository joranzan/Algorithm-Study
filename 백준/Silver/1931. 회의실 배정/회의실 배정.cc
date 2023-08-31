#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

bool sorting(pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2)
{
	if (p1.first.first == p2.first.first)
	{
		//************************************소요시간으로 왜 정렬 안됨??
		//종료시간이 같을 경우 소요시간이 긴 회의부터 정렬
		//예를 들어 (1시작 3끝) (2시작 3끝) (3시작 3끝) 이면 첫 회의 먼저 한 후 마지막 회의 진행
		//0시간인 회의가 있다는 반례 때문.
		return p1.second > p2.second;
	}
	else return p1.first.first < p2.first.first;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;
	vector<pair<pair<int, int>, int>> Meeting; //(종료시간,시작시간), 회의 소요시간
	cin >> N;
	Meeting.resize(N);
	for (int i = 0; i < N; i++)
	{
		cin >> Meeting[i].first.second;
		cin >> Meeting[i].first.first;
		Meeting[i].second = Meeting[i].first.first - Meeting[i].first.second;
	}
	sort(Meeting.begin(), Meeting.end(), sorting);
	
	int last_endtime = -1;
	int count = 0;

	for (int i = 0; i < N; i++)
	{
		//시작시간이 마지막 회의 종료시간보다 앞이면 제외
		if (Meeting[i].first.second < last_endtime) continue;
		last_endtime = Meeting[i].first.first;
		count++;
	}
	cout << count << "\n";
	return 0;
}