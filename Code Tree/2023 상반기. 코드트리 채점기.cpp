#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<queue>
#include<unordered_set>
#include<map>
#include<sstream>


using namespace std;

struct URL {   //URL 구성 요소
	string domain;
	int id;
};

struct wait {  //WaitingQ에 필요한 정보
	int time;
	int p;
	string url;  //여기서는 아에 url이 필요하므로

	bool operator<(wait next) const {
		if (p < next.p) return false;
		else if (p > next.p) return true;
		else {
			if (time < next.time) return false;
			else if (time > next.time) return true;
			else return false;
		}
	}
};

struct judge {
	int start;
	URL url;
};

struct allDone {
	int start;
	int end;
};

int N;
bool WaitingJudger[500001] = { false, };
priority_queue<int, vector<int>, greater<int>> WJ;
unordered_set<string> checkWQ;  //url 존재하는지 확인하는 자료구조
priority_queue<wait> WaitingQ;  //채점요청 우선순위로 정렬
unordered_set<string> checkJV;  //채점중인 domain있는지 확인
judge JudgingVector[50001];     //채점기가 채점중인 task정보
map<string, vector<allDone>> History;//domain gap 분석(부정채점 확인)

//url split 함수
URL splitURL(string url) {

	int i = url.find('/');
	return { url.substr(0,i),stoi(url.substr(i + 1)) };
}


void Request(int t, int p, string u) {
	//"대기 큐" 내에 정확히 일치하는 url 있으면 무시
	if (checkWQ.find(u) != checkWQ.end()) return;
	//대기 큐에 들어감 
	checkWQ.insert(u);
	
	WaitingQ.push({ t,p,u });

}

void tryGrading(int t) {
	//가능한 채점 존재하면 "가장 작은 채점기"가 진행
	if (WJ.empty()) return;
	int availJudger = WJ.top();
	
	unordered_set<string> checkedDomain;
	//어떤 task를 수행할지 선택과정
	vector<wait> temp;
	wait Next;
	URL NextURL;
	bool myflag = false;  //가능한 task가 존재하는지
	while (!WaitingQ.empty()) {
		bool possible = true; //현재 task가 가능한지
		wait Now = WaitingQ.top();
		URL NowURL = splitURL(Now.url);
		//이미 검사한 domain이면 넘김
		if (checkedDomain.find(NowURL.domain) != checkedDomain.end()) {
			possible = false;
			temp.push_back(Now);
			WaitingQ.pop();
			continue;
		}
		// 1) 채점 진행중인 "Domain"이 정확히 일치하는 경우 무시
		else if (checkJV.find(NowURL.domain) != checkJV.end()) {
			checkedDomain.insert(NowURL.domain);
			possible = false;
			temp.push_back(Now);
			WaitingQ.pop();
			continue;
		}
		// 2) 일치하는 모든 domain에 대해 start+3xgap보다 t가 작은 경우 무시
		else if (History.find(NowURL.domain) != History.end()) {
			bool flag = true;
			auto it = History.find(NowURL.domain);

			if (it != History.end()) {
				int index = (*it).second.size() - 1;
				int s = (*it).second[index].start;
				int e = (*it).second[index].end;
				int g = e - s;
				if (t < s + 3 * g) {
					flag = false;
				}
			}

			if (!flag) {
				possible = false;
				temp.push_back(Now);
				checkedDomain.insert(NowURL.domain);
				WaitingQ.pop();
				continue;
			}
		}

		if (possible) {
			WaitingQ.pop();
			Next = Now;
			NextURL = NowURL;
			myflag = true;
			break;
		}
	}

	for (int i = 0; i < temp.size(); i++) {
		WaitingQ.push(temp[i]);
	}
	//temp.clear();

	if (myflag) {
		JudgingVector[availJudger] = { t,NextURL };  //채점중 배열로 들어감
		checkJV.insert(NextURL.domain);      //JV에 도메인 넣어줌
		WaitingJudger[availJudger] = true;
		WJ.pop();
		checkWQ.erase(Next.url);
	}
}

void exitGrading(int t, int graderID) {

	//J번 채점 중 아니면 무시
	if (!WaitingJudger[graderID]) return;

	//t초에 J번의 채점기 종료 
	judge Exit = JudgingVector[graderID];
	WJ.push(graderID);
	WaitingJudger[graderID] = false;
	checkJV.erase(Exit.url.domain);
	vector<allDone> temp;
	temp.push_back({ Exit.start, t });
	History.insert({ Exit.url.domain, temp });
}

void checkReadyQ(int t) {
	//4. 대기 큐 조회
	//ready Q에 있는 task수 출력
	cout << WaitingQ.size() << "\n";
}

void input() {
	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {

		int cmd;
		cin >> cmd;
		if (cmd == 100) {  //채점기 준비

			cin >> N;
			for (int j = 1; j <= N; j++) {
				WJ.push(j);
			}
			string u;
			cin >> u; //u0
			WaitingQ.push({ 0,1,u });

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

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cin.tie(NULL);
	input();

	return 0;
}



//문제분석

//1. 코드트리 채점기 준비
//N개의 채점기 (1~N)
// 우선순위 : 1 
// url (domain/문제ID)
// 바로 WaitingQ에 들어감(채점요청)
//

//2. 채점 요청
//우선순위 : p , url : u
//대기 큐에 들어감 
// **조건 : "대기 큐" 내에 정확히 일치하는 url 있으면 무시 (unordered_set 사용)

//3. 채점 시도
//**채점 조건 아닌 경우 무시
// 1) 채점 진행중인 "Domain"이 정확히 일치하는 경우 무시 (unordered_set 사용)
// 2) 일치하는 모든 domain에 대해 start+3xgap보다 t가 작은 경우 무시  //history
//  (???뭐 사용할까?)
//
//채점 시도 우선순위(우선순위 큐 사용)
//1) 우선순위 p 작을 수록
//2) "대기 큐에 들어온 순서 (t로 체크하자)
//
//가능한 채점 존재하면 "가장 작은 채점기"가 진행 
//없으면 무시


//4. 채점 종료
//t, J
//t초에 J번의 채점기 종료 
//종료한 시간 필요함(gap때문에)

//채점 대기 큐 조회
//시간 t에 채점 대기 큐에 있는 채점 task의 수
//그냥 WaitingQ의 사이즈 출력하면 됨