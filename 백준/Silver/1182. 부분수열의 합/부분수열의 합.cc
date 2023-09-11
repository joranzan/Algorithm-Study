#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, S;
vector<int> Num;
vector<int> Path;
int cnt = 0;

void DFS(int index, int sum, int depth) {


	if (sum == S&&depth!=0) {

		cnt++;
	}
	if (index >= N) return;
	
	for (int i = index; i < N; i++) {
		sum += Num[i];
		DFS(i + 1, sum, depth+1);
		sum -= Num[i];
	}

}



int main() {

	
	cin >> N >> S;
	Num.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> Num[i];
	}
	sort(Num.begin(), Num.end());

	DFS(0, 0 ,0);
	cout << cnt;

	return 0;
}