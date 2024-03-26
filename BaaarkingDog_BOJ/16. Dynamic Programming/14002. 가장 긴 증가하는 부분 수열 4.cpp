#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int Number[1001] = { 0, };
pair<int, int> DP[1001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Number[i];
	}

	int Answer = 0;
	int maxIndex = 0;
	for (int i = 0; i < N; i++) {
		DP[i] = { 1,i };
		for (int j = 0; j < i; j++) {
			if (Number[i] <= Number[j]) continue;
			if (DP[i].first < DP[j].first + 1) {
				DP[i] = { DP[j].first + 1, j };
			}
		}
		if (Answer < DP[i].first) {
			Answer = DP[i].first;
			maxIndex = i;
		}
	}

	int nowIndex = DP[maxIndex].second;


	//길이가 1인 경우
	if (nowIndex == maxIndex) {
		cout << "1" << "\n" << Number[maxIndex];
	}
	else {
		vector<int> AnswerArr;  //숫자 담을 배열
		AnswerArr.push_back(Number[maxIndex]);
		nowIndex = maxIndex;
		while (nowIndex != DP[nowIndex].second) {
			nowIndex = DP[nowIndex].second;
			AnswerArr.push_back(Number[nowIndex]);
		}

		cout << AnswerArr.size() << "\n";

		for (int i = AnswerArr.size() - 1; i >= 0; i--) {
			cout << AnswerArr[i] << " ";
		}
	}

	

	return 0;
}

