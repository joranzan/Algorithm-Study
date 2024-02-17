#include<iostream>
#include<string>


using namespace std;

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int staticN;
	
	cin >> staticN;


	int Answer = staticN + 1;

	for (int i = staticN; i >= 0; i--) {
		string nowN = to_string(i);
		int sum = 0;
		for (int j = 0; j < nowN.size(); j++) {
			sum += int(nowN[j] - '0');
		}
		if (i + sum == staticN) {
			Answer = min(Answer, i);
		}
	}

	if (Answer == (staticN + 1)) cout << "0";
	else cout << Answer;
	


	return 0;
}