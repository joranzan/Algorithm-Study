#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int N;
int cnt = -1;
bool found = false;

void DFS(vector<int> num,int last_num, int depth, int length) {
		 
	if (depth == length) { //만약 length길이만큼 숫자 만들었으면 감소하는 숫자 완성이므로 개수++
		cnt++;
		if (cnt == N) { //만약 N과 같으면 정답
			for (int i = 1; i <= length;i++) {
				cout << num[i];
			}
		}
		return;
	}


	for (int i = 0; i < last_num; i++) {  //이전 숫자보다 작을때까지
		
		num.push_back(i);  //하나 넣음
		DFS(num, i, depth + 1, length);  //그다음 숫자 넣으라 가라
		if (found) break;
		num.pop_back();  // (i) 넣었을 때 감소하는 숫자 다 찾고 돌아왔으면 i 다시 뺌

	}
	
}


int main(){

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	//N이 0이면 계산할 필요없음
	if (N == 0) {
		cout << "0";
		return 0;
	}



	//길이가 1자리인 숫자부터 10자리인 숫자까지 찾기
	for (int i = 1; i <=10; i++) { 
		if (found) break;   //만약 정답 찾았으면 for문 나감
		vector<int> temp;
		temp.push_back(10);  //한자리일때 0~9까지 와야하므로 맨앞에 디폴트로 10 넣어줌
							 //그래야 앞자리보다 작은 애들 넣을 때 0~9까지 다 넣을 수 있으니까 
		
		DFS(temp, 10, 0, i); // i자리 숫자 중 감소하는 숫자의 수 찾으러 가라
	}
	if (cnt < N) cout << "-1";


	return 0;
}