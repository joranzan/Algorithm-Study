#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Present {

	int price;
	long long value;

	bool operator<(Present next) const {
		if (price < next.price) return true;
		if (price > next.price) return false;
		return false;
	}
};

int N, D;
vector<Present> List;
long long Answer = 0;

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	//친구: N명
	//가격: P,  기쁨 수치 : V
	//받는 선물의 가격차이 D미만    //10억 이하
	//기쁨수치는 최대

	cin >> N >> D;
	List.resize(N);

	for (int i = 0; i < N; i++)
	{
		cin >> List[i].price >> List[i].value;
		Answer = max(Answer, List[i].value);
	}

	sort(List.begin(), List.end());

	if (N == 1)
	{
		cout << Answer;
		return 0;
	}

	int left = 0;
	int right = 1;
	long long temp = List[0].value;
	while (right<N)
	{
		if (List[right].price - List[left].price < D)
		{
			temp += List[right].value;
			right++;
		}
		else {
			temp -= List[left].value;
			left++;
		}
		Answer = max(Answer, temp);
	}
	
	cout << Answer;


	return 0;
}