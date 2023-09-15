#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {

	//L개의 알파벳 (최소한개의 모음, 최소 두개의 자음)
	//사전 순
	//문자 C가지
	int L, C;
	cin >> L >> C;

	vector<char> Input;

	for (int i = 0; i < C; i++) {
		char c;
		cin >> c;
		Input.push_back(c);
		
	}

	sort(Input.begin(), Input.end());

	int arr[15] = { 0 };

	for (int i = L; i < C; i++) {
		arr[i] = 1;
	}

	vector<vector<char>> ans;

	do {
		vector<char> temp;
		for (int i = 0; i < C; i++) {
			if (arr[i] == 0) temp.push_back(Input[i]);
		}
		
		int aeiou = 0;
		int other = 0;

		for (int i = 0; i < temp.size(); i++) {
			char cur = temp[i];
			if (cur == 'a' || cur == 'e' || cur == 'i' || cur == 'o' || cur == 'u') aeiou++;
			else other++;
		}

		if (aeiou>=1 && other>=2) {
			ans.push_back(temp);
		}
	} while (next_permutation(arr, arr + C));

	for (int i = 0; i < ans.size(); i++) {
		for (int j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j];
		}
		cout << "\n";
	}



	return 0;
}