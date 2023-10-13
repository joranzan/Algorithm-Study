#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<queue>
#include<unordered_set>
#include<unordered_map>

using namespace std;

struct URL {
	string domain;
	int id;
};



//url split 함수
URL splitURL(string url) {

	string d;
	int index;
	for (int i = 0; i < url.size(); i++) {
		if (url[i] == '/') {
			index = i;
			break;
		}
		d.push_back(url[i]);
	}

	string id_temp;
	for (int i = index + 1; i < url.size(); i++) {
		id_temp.push_back(url[i]);
	}
	int integer_id = stoi(id_temp);

	URL t;
	t.domain = d;
	t.id = integer_id;

	return t;

}

void Request(int t, int p, string u) {
	
}

void tryGrading(int t) {
	
	
}

void exitGrading(int t, int graderID) {


}
void checkReadyQ(int t) {
	//4. 대기 큐 조회
	//ready Q에 있는 task수 출력
}

void input() {
	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {

		int cmd;
		cin >> cmd;
		if (cmd == 100) {  //채점기 준비

			cin >> N;
			string u;
			cin >> u; //u0


		}
		else if (cmd == 200) { //채점 요청
			int t, p;  //t: 시간   p : 우선순위  
			string u;  //u : url
			cin >> t >> p >> u;
			Request(t, p, u);
		}
		else if (cmd == 300) { //채점 시도
			int t;
			cin >> t;
			tryGrading(t);
		}
		else if (cmd == 400) { //채점 종료
			int t, J; 
			cin >> t >> J;   //t초에 J번째 채점기의 채점 종료
			exitGrading(t, J);
		}
		else if (cmd == 500) { //대기 큐 조회
			//t초에 대기 큐 상태 조회
			int t;
			cin >> t;  
			checkReadyQ(t);
		}

	}

}

void solution() {

}

int main() {

	input();
	solution();

	return 0;
}

