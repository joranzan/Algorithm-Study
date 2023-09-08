#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

int n, answer;
char Equation[20]; //연산자와 피연산자 저장

//연산해주는 함수
int Calculate(int i) {

	int a, b, c;
	//문자의 아스키 코드 값에서 0의 아스키 코드 값인 48을 빼서 문자를 정수형으로 바꿔줌
	a = Equation[i - 1] - '0';           
	b = Equation[i + 1] - '0';
	if (Equation[i] == '+') {
		c = a + b;
	}
	else if (Equation[i] == '-') {
		c = a - b;
	}
	else if (Equation[i] == '*') {
		c = a * b;
	}
	return c;
}

//DFS함수
void DFS(int pointer, vector<bool>& check) {
	//만약 현재 위치가 n이상이라면 check대로 계산하여 answer갱신
	if (pointer >= n) {   //check에서 연산자 인덱스가 true이면 앞뒤로 괄호 묶고 done을 true로 해주기
		queue<int> q;
		vector<bool> done(20, false);
		//괄호 먼저 연산
		for (int i = 1; i < n; i += 2) {  //연산자 인덱스: 1 3 5 7 9 11 .....
			if (check[i] == true) {
				done[i - 1] = true; done[i] = true; done[i + 1] = true;
				int x = Calculate(i); //i-1과 i+1번째를 i연산자로 계산한 결과
				q.push(x);
			}
		}   

		//연산자 다시 만들기
		vector<int> Num;
		vector<char> Calculator; //+,-,*
		for (int i = 0; i < n; i++) {
			//0이상 9이하이며 아직 계산을 하지 않은 경우
			if (done[i] == false && Equation[i] >= '0' && Equation[i] <= '9') {
				Num.push_back(Equation[i] - '0');
			}
			//0이상 9이하가 아니고 아직 계산 안한 경우: 연산자
			else if (done[i] == false) {
				Calculator.push_back(Equation[i]); //연산자 넣기
			}
			//계산 다 했을 때: 계산한 값 넣었던 queue에서 얻어오고 pop!
			else {
				i += 2;
				Num.push_back(q.front());
				q.pop();
			}
		}

		//연산하기
		int ans_candi = Num[0];
		for (int i = 0; i < Calculator.size(); i++) {
			if (Calculator[i] == '+') {
				ans_candi += Num[i + 1];
			}
			else if (Calculator[i] == '-') {
				ans_candi -= Num[i + 1];
			}
			else {
				ans_candi *= Num[i + 1];
			}
		}
		/*for (int ch = 0; ch < check.size(); ch++)
			cout << check[ch] << " ";
		cout << "\n";
		for (int don = 0; don < done.size(); don++)
			cout << done[don] << " ";
		cout << "\n" << pointer << " " << ans_candi << "\n";*/

		//연산한 값이랑 이전에 구한 최댓값 비교
		if (answer < ans_candi) {
			answer = ans_candi;
		}

		return;
	}

	//for문을 돌며 현재 연산자를 괄호로 묶는경우와 아닌경우 두개로 나눠 
	//check표시(연산자와 양옆 피연산자까지 같이표시)후 DFS
	check[pointer] = true; check[pointer - 1] = true; check[pointer + 1] = true;  //그 연산자 묶을거면 check을 true로 해줘야함
	DFS(pointer + 4, check); //괄호 묶는 경우
	check[pointer] = false;
	DFS(pointer + 2, check); //괄호 안 묶는 경우

	//DFS끝내기
	return;
}


int main() {
	//iostream과 stdio 버퍼 동기화시켜서 입력 빨리받아오자
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	//==============================================
	//n과 n개 연산자를 char형 전역 변수 배열 calcul에 받아온다
	cin >> n;
	string s;
	cin >> s;
	for (int i = 0; i < n; i++) {
		Equation[i] = s[i];
	}

	//괄호로 묶을 bool형 벡터 check와 현재 위치 pointer를 만들자
	vector<bool> check(n, false);
	int pointer = 1;

	//DFS함수를 실행
	answer = -2000000000;
	DFS(pointer, check);

	//answer 출력
	cout << answer;

	return 0;
}