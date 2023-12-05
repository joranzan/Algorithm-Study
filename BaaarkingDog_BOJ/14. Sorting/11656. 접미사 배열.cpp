#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string sarr[1000];

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	string s;
	cin >> s;

	for (int i = 0; i < s.size(); i++) {
		string temp;
		for (int j = i; j < s.size(); j++) {
			temp.push_back(s[j]);
		}
		sarr[i] = temp;
	}

	sort(sarr, sarr + s.size());
	for (int i = 0; i < s.size(); i++) {
		cout << sarr[i] << "\n";
	}

	return 0;
}