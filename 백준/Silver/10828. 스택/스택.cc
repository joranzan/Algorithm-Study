#include<iostream>
#include<string>
#include<vector>

using namespace std;


int main() {


	int N;
	cin >> N;
	vector<int> v;
	for (int i = 0; i < N; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "push") {
			int num;
			cin >> num;
			v.push_back(num);
		}
		else if (cmd == "pop") {
			if (v.size() == 0) cout << "-1\n";
			else {
				cout << v[v.size() - 1] << "\n";
				v.pop_back();
			}
		}
		else if (cmd == "size") {
			cout << v.size() << "\n";
		}
		else if (cmd == "empty") {
			if (v.size() == 0) cout << "1\n";
			else {
				cout << "0\n";
				
			}
		}
		else if (cmd == "top") {
			if (v.size() == 0) cout << "-1\n";
			else {
				cout << v[v.size() - 1] << "\n";
			}
		}
	}


	return 0;
}