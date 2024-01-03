#include<iostream>
#include<string>
using namespace std;

/*
문제 분석

1010

1개 1개 바꾸기







*/

string s;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> s;

	int zeroCnt = 0;
	int oneCnt = 0;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '1') oneCnt++;
		else if (s[i] == '0') zeroCnt++;
	}

	oneCnt /= 2;
	zeroCnt /= 2;

	string temp1;
	int cnt1 = 0;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0') {
			temp1.push_back(s[i]);
		}
		else {
			if (cnt1 >= oneCnt) temp1.push_back(s[i]);
			else cnt1++;
		}
	}

	string temp2;
	int cnt2 = 0;

	for (int i = temp1.size() - 1; i >= 0; i--) {
		if (temp1[i] == '1') temp2.push_back(temp1[i]);
		else {
			if (cnt2 >= zeroCnt) temp2.push_back(temp1[i]);
			else cnt2++;
		}
	}

	for (int i = temp2.size() - 1; i >= 0; i--) {
		cout << temp2[i];
	}

	return 0;
}