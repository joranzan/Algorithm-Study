#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;


int N, M;
vector<int> Input;
int Total[10000] = { 0, };
int Cnt[10000] = { 0, };
vector<int> Num;


void DFS(int depth) {
	if (depth >= M) {
		for (int i = 0; i < Num.size(); i++) {
			cout << Num[i] << " ";
		}
		cout << "\n";
		return;
	}
	int lastNum = 0;

	for (int i = 0; i < N; i++) {
		if (lastNum == Input[i]) continue;
		if (Cnt[Input[i]] + 1 > Total[Input[i]]) continue;
		lastNum = Input[i];
		Cnt[Input[i]]++;
		Num.push_back(Input[i]);
		DFS(depth + 1);
		Num.pop_back();
		Cnt[Input[i]]--;
	}

}


int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		
		int temp;
		cin >> temp;
		Input.push_back(temp);
		Total[temp]++;
	}

	sort(Input.begin(), Input.end());

	DFS(0);

	return 0;
}
