#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int N;
int cnt = -1;
bool found = false;
//0번째는 10값이므로 출력 NO
//
void DFS(vector<int> num,int last_num, int depth, int length) {
		 
	if (depth == length) {
		cnt++;
		if (cnt == N) {
			for (int i = 1; i <= length;i++) {
				cout << num[i];
			}
		}
		return;
	}


	for (int i = 0; i < last_num; i++) {
		
		num.push_back(i);
		DFS(num, i, depth + 1, length);
		if (found) break;
		num.pop_back();
	}
	
}


int main(){

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	if (N == 0) {
		cout << "0";
		return 0;
	}

	for (int i = 1; i <=10; i++) { //length 자리수 찾기
		if (found) break;
		vector<int> temp;
		temp.push_back(10);
		DFS(temp, 10, 0, i);
	}
	if (cnt < N) cout << "-1";


	return 0;
}