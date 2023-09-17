#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int main() {


	string s[5];
	int maxLen = 0;

	for (int i = 0; i < 5; i++) {
		cin >> s[i];
		maxLen = max(maxLen, int(s[i].length()));
	}

	for (int i = 0; i < maxLen; i++) {
		for (int j = 0; j < 5; j++) {
			if (s[j].length() <= i) continue;
			cout << s[j][i];
		}
	}


	return 0;
}