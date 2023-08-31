#include<iostream>
#include<vector>

using namespace std;

struct Node {
	char data;
	int prev;
	int next;
};

int main() {

	string s;   //길이 10만 이하
	cin >> s;
	int length = s.size();  //시작 커서는 length +1 부터 시작

	int Q;  //명령어 개수 50만이하
	cin >> Q;

	

	vector<Node> node(length);

	//인접리스트 정보 배열 만들기
	for (int i = 0; i < length; i++) {
		node[i].data = s[i];
		node[i].prev = i - 1;
		node[i].next = i + 1;

		if (i <= 0) {
			node[i].prev = -1;
		}
	}
	//명령어마다 실행
	int cursor = length ;  //end()
	node.push_back({ NULL, length-1,-1 });
 

	for (int i = 0; i < Q; i++) {
		char Query;
		cin >> Query;
		//L 왼쪽 한칸 이동  (맨앞 무시)
		if (Query == 'L') {
			if (node[cursor].prev ==-1) continue;
			cursor = node[cursor].prev;
		}
		//D 오른쪽 한칸 이동 (맨뒤 무시)
		else if (Query == 'D') {
			if (node[cursor].next == -1) continue;  //맨뒤
			cursor = node[cursor].next;
		}
		//B (현재위치 - 1) 위치 문자 삭제 (맨앞 무시) 
		else if (Query == 'B') {
			//****커서 그대로 -> 연결리스트로 제거
			
			Node current = node[cursor];

			if (current.prev == -1) continue;

			Node remove = node[current.prev];

			//왼쪽에 하나만 존재
			if (remove.prev == -1) {
				node[cursor].prev = -1;
				node[current.prev].next = -2;
				node[current.prev].prev = -2;
			}
			//왼쪽에 여러개 존재
			else {
				node[cursor].prev = remove.prev;
				node[node[current.prev].prev].next = remove.next;

				//삭제되는 노드의 양쪽 끊어주기
				node[current.prev].next = -2;
				node[current.prev].prev = -2;
			}	
		}
		// P $ : $문자 왼쪽에 추가
		else if (Query == 'P') {
			char add; //추가할 문자
			cin >> add;

			//현재 cursor가 제일 왼쪽일 때
			if (node[cursor].prev == -1) {
				node.push_back({ add,-1,cursor });
				node[cursor].prev = node.size() - 1;
			}
			//현재 cursor가 제일 마지막일 때
			else if (node[cursor].next == -1) {
				node.push_back({ add,node[cursor].prev ,cursor });
				node[node[cursor].prev].next = node.size() - 1;
				node[cursor].prev = node.size() - 1;
			}
			//현재 cursor가 중간일 때
			else {
				node.push_back({ add,node[cursor].prev, node[node[cursor].prev].next });
				node[node[cursor].prev].next = node.size() - 1;
				node[cursor].prev = node.size() - 1;
			}
		}
	}
	int start = 0;

	for (int i = 0; i < node.size(); i++) {
		if (node[i].prev == -1) {
			start = i;
			break;
		}
	}


	while (node[start].next != -1) {
		cout << node[start].data;
		start = node[start].next;
	}

	int debugging = -1;


	return 0;
}


//문제분석
//시간: 0.3초  -> 3000만번

//영어소문자, 최대 60만글자

//L+1가지 커서 (iterator느낌)


//명령어
//L 왼쪽 한칸 이동  (맨앞 무시)
//D 오른쪽 한칸 이동 (맨뒤 무시)
//B (현재위치 - 1) 위치 문자 삭제 (맨앞 무시) 

//****커서 그대로 -> 연결리스트로 제거

// P $ : $문자 왼쪽에 추가


//명령어 수행 전 초기 -> end()

