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



//url split �Լ�
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
	//4. ��� ť ��ȸ
	//ready Q�� �ִ� task�� ���
}

void input() {
	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {

		int cmd;
		cin >> cmd;
		if (cmd == 100) {  //ä���� �غ�

			cin >> N;
			string u;
			cin >> u; //u0


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

void solution() {

}

int main() {

	input();
	solution();

	return 0;
}

