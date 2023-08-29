#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Present {

	int price;
	long long satisfied;

	bool operator<(Present next) const {
		if (price < next.price) return true;
		if (price > next.price) return false;
		return false;
	}
};

int N, D;
vector<Present> List;
long long Answer = -1;

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
		cin >> List[i].price >> List[i].satisfied;
		Answer = max(Answer, List[i].satisfied);
	}

	sort(List.begin(), List.end());

	if (N == 1) {
		cout << List[0].satisfied;
		return 0;
	}
	else if (N == 2) {
		if (List[1].price - List[0].price >= D) {
			cout << max(List[0].satisfied, List[1].satisfied);
		}
		else {
			cout << List[0].satisfied + List[1].satisfied;
		}
		return 0;
	}
	int start_index = 0;
	int end_index = 1;
	long long sum = List[start_index].satisfied;
	Answer = sum;

	while (start_index < end_index && end_index < N)
	{

		int start_price = List[start_index].price;
		int end_price = List[end_index].price;

		long long start_sat = List[start_index].satisfied;
		long long end_sat = List[end_index].satisfied;

		if (abs(end_price - start_price) < D) {

			//받아도 괜찮다면

			sum += end_sat;    //만족도 증가  
			Answer = max(Answer, sum);  //받고나서 만족도 업데이트
			end_index++;  // end 하나 증가

		}
		else
		{
			//만약 end 선물이랑 start 선물의 차이가 D 이상이면

			sum -= start_sat;  //기존에 sum에있던 start_sat값 빼고
			Answer = max(Answer, start_sat);
			start_index++;     //start 하나 증가
		}

		if (start_index == end_index) {
			//Answer = max(Answer, List[start_index].satisfied);
			end_index++;
		}
		Answer = max(Answer, sum);
	}
	cout << Answer;


	return 0;
}