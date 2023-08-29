#include<iostream>
#include<vector>
#include<set>
#include<cmath>

using namespace std;

//시계방향
//K번째 큰 수를 10진수로 만든 수

//같은 수 -> set

int toDecimal(string s);
int solution(string s);
vector<string> DivSet(string s);
string Rotate(string s);


int N, K;
set<int> mySet;


//T진수에서 T를 곱해주는 것: 1자리 올린수 -> 일의 자리를 확보
//곱하기(*) 진수 + 일의자리 수
int Hex2Dec(string number) {
	
	int ret = 0;

	for (char ch : number) { // <- number에 있는 data들을 하나씩 ch라는 이름으로 복사
		
		int num = 0;
		
		if ('0' <= ch && ch <= '9') {
			num = ch - '0';
		}
		else if ('A' <= ch && ch <= 'Z') {
			num = ch - 'A'; 
		}
		ret *= 16;
		ret += num;
	}

	return ret;
}



int toDecimal(string s) {

	int num = 0;
	for (int i = 0; i < s.size(); i++) {  //A:10

		if (s[i] >= 'A' && s[i] <= 'F') {
			num = num + (int(s[i] - 'A') + 10) * pow(16, s.size() - i - 1);
		}
		else {
			num = num + (int(s[i] - '0')) * pow(16, s.size() - i - 1);
		}

	}

	return num;

}

int solution(string s) {

	string s_temp = s;
	
	for (int i = 0; i < s.size(); i++) {
		s_temp = Rotate(s_temp);
		vector<string> v = DivSet(s_temp);

		for (int j = 0; j < 4; j++) {
			mySet.insert(toDecimal(v[j]));
		}
	}

	int Answer = 0;

	auto it = mySet.end();
	
	for (int i = 0; i < K; i++) {
		it--;
	}

	Answer = *it;

	return Answer;
}

vector<string> DivSet(string s) {

	int line_N = N / 4;

	vector<string> v(4);
	for (int i = 0; i < 4; i++) {
		for (int j = i * line_N; j < i * line_N + line_N; j++) {

			v[i].push_back(s[j]);
		}
	}

	return v;
}

string Rotate(string s) {
	char temp = s[s.size() - 1];
	
	for (int i = s.size() - 1; i >= 1; i--) {
		s[i] = s[i - 1];
	}
	s[0] = temp;

	return s;
}



int main() {

	int T;
	cin >> T;

	for (int test = 1; test <= T; test++) {
		cin >> N >> K;

		string s;
		cin >> s;
		mySet.clear();
		cout << "#" << test << " " << solution(s) << "\n";

	}




	return 0;
}


//진수 변환 방법
//int num = stoi(~~~);