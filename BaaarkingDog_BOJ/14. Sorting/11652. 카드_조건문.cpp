#include<iostream>
#include<algorithm>

using namespace std;

long long arr[100000];

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);

	long long nowNum = arr[0];
	long long maxNum = arr[0];
	int nowCnt = 1;
	int maxCnt = 1;
	
	for (int i = 1; i < N; i++) {
		if (nowNum == arr[i]) {
			nowCnt++;
		}
		else {
			if (maxCnt < nowCnt) {
				maxCnt = nowCnt;
				maxNum = nowNum;
			}
			nowNum = arr[i];
			nowCnt = 1;
		}
	}

	if (maxCnt < nowCnt) {
		maxCnt = nowCnt;
		maxNum = nowNum;
	}
	

	cout << maxNum;

	return 0;
}