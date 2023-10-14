#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<queue>
#include<unordered_set>
#include<map>
#include<sstream>


using namespace std;

struct URL {   //URL ���� ���
	string domain;
	int id;
};

struct wait {  //WaitingQ�� �ʿ��� ����
	int time;
	int p;
	string url;  //���⼭�� �ƿ� url�� �ʿ��ϹǷ�

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
unordered_set<string> checkWQ;  //url �����ϴ��� Ȯ���ϴ� �ڷᱸ��
priority_queue<wait> WaitingQ;  //ä����û �켱������ ����
unordered_set<string> checkJV;  //ä������ domain�ִ��� Ȯ��
judge JudgingVector[50001];     //ä���Ⱑ ä������ task����
map<string, vector<allDone>> History;//domain gap �м�(����ä�� Ȯ��)

//url split �Լ�
URL splitURL(string url) {

	int i = url.find('/');
	return { url.substr(0,i),stoi(url.substr(i + 1)) };
}


void Request(int t, int p, string u) {
	//"��� ť" ���� ��Ȯ�� ��ġ�ϴ� url ������ ����
	if (checkWQ.find(u) != checkWQ.end()) return;
	//��� ť�� �� 
	checkWQ.insert(u);
	
	WaitingQ.push({ t,p,u });

}

void tryGrading(int t) {
	//������ ä�� �����ϸ� "���� ���� ä����"�� ����
	if (WJ.empty()) return;
	int availJudger = WJ.top();
	
	unordered_set<string> checkedDomain;
	//� task�� �������� ���ð���
	vector<wait> temp;
	wait Next;
	URL NextURL;
	bool myflag = false;  //������ task�� �����ϴ���
	while (!WaitingQ.empty()) {
		bool possible = true; //���� task�� ��������
		wait Now = WaitingQ.top();
		URL NowURL = splitURL(Now.url);
		//�̹� �˻��� domain�̸� �ѱ�
		if (checkedDomain.find(NowURL.domain) != checkedDomain.end()) {
			possible = false;
			temp.push_back(Now);
			WaitingQ.pop();
			continue;
		}
		// 1) ä�� �������� "Domain"�� ��Ȯ�� ��ġ�ϴ� ��� ����
		else if (checkJV.find(NowURL.domain) != checkJV.end()) {
			checkedDomain.insert(NowURL.domain);
			possible = false;
			temp.push_back(Now);
			WaitingQ.pop();
			continue;
		}
		// 2) ��ġ�ϴ� ��� domain�� ���� start+3xgap���� t�� ���� ��� ����
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
		JudgingVector[availJudger] = { t,NextURL };  //ä���� �迭�� ��
		checkJV.insert(NextURL.domain);      //JV�� ������ �־���
		WaitingJudger[availJudger] = true;
		WJ.pop();
		checkWQ.erase(Next.url);
	}
}

void exitGrading(int t, int graderID) {

	//J�� ä�� �� �ƴϸ� ����
	if (!WaitingJudger[graderID]) return;

	//t�ʿ� J���� ä���� ���� 
	judge Exit = JudgingVector[graderID];
	WJ.push(graderID);
	WaitingJudger[graderID] = false;
	checkJV.erase(Exit.url.domain);
	vector<allDone> temp;
	temp.push_back({ Exit.start, t });
	History.insert({ Exit.url.domain, temp });
}

void checkReadyQ(int t) {
	//4. ��� ť ��ȸ
	//ready Q�� �ִ� task�� ���
	cout << WaitingQ.size() << "\n";
}

void input() {
	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {

		int cmd;
		cin >> cmd;
		if (cmd == 100) {  //ä���� �غ�

			cin >> N;
			for (int j = 1; j <= N; j++) {
				WJ.push(j);
			}
			string u;
			cin >> u; //u0
			WaitingQ.push({ 0,1,u });

		}
		else if (cmd == 200) { //ä�� ��û
			int t, p;  //t: �ð�   p : �켱����  
			string u;  //u : url
			cin >> t >> p >> u;
			Request(t, p, u);
		}
		else if (cmd == 300) { //ä�� �õ�
			int t;
			cin >> t;
			tryGrading(t);
		}
		else if (cmd == 400) { //ä�� ����
			int t, J; 
			cin >> t >> J;   //t�ʿ� J��° ä������ ä�� ����
			exitGrading(t, J);
		}
		else if (cmd == 500) { //��� ť ��ȸ
			//t�ʿ� ��� ť ���� ��ȸ
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



//�����м�

//1. �ڵ�Ʈ�� ä���� �غ�
//N���� ä���� (1~N)
// �켱���� : 1 
// url (domain/����ID)
// �ٷ� WaitingQ�� ��(ä����û)
//

//2. ä�� ��û
//�켱���� : p , url : u
//��� ť�� �� 
// **���� : "��� ť" ���� ��Ȯ�� ��ġ�ϴ� url ������ ���� (unordered_set ���)

//3. ä�� �õ�
//**ä�� ���� �ƴ� ��� ����
// 1) ä�� �������� "Domain"�� ��Ȯ�� ��ġ�ϴ� ��� ���� (unordered_set ���)
// 2) ��ġ�ϴ� ��� domain�� ���� start+3xgap���� t�� ���� ��� ����  //history
//  (???�� ����ұ�?)
//
//ä�� �õ� �켱����(�켱���� ť ���)
//1) �켱���� p ���� ����
//2) "��� ť�� ���� ���� (t�� üũ����)
//
//������ ä�� �����ϸ� "���� ���� ä����"�� ���� 
//������ ����


//4. ä�� ����
//t, J
//t�ʿ� J���� ä���� ���� 
//������ �ð� �ʿ���(gap������)

//ä�� ��� ť ��ȸ
//�ð� t�� ä�� ��� ť�� �ִ� ä�� task�� ��
//�׳� WaitingQ�� ������ ����ϸ� ��