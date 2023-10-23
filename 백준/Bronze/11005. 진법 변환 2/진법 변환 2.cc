#include<iostream>
#include<vector>

using namespace std;





int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, digit;
	cin >> N >> digit;
	vector<int> temp;

	while (N / digit != 0) {
		temp.push_back(N % digit);
		N /= digit;
	}

	temp.push_back(N);

	for (int i = temp.size() - 1; i >= 0; i--) {
		if (temp[i] < 10) cout << temp[i];
		else {
			cout << char(temp[i] - 10 + 'A');
		}
	}
	


	return 0;
}

//8
//2  4 ...0
//2  2 ...0
//2  1 ...0
//2  0 ...1