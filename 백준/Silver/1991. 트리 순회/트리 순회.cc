#include<iostream>
#include<vector>

using namespace std;


struct Child {
	int left;
	int right;
};

int V;
vector<Child> Adj;

vector<char> Ans1;
vector<char> Ans2;
vector<char> Ans3;

void DFS(int nowNode) {

	if (nowNode == -1) return;
	Ans1.push_back(nowNode);
	DFS(Adj[nowNode].left);
	Ans2.push_back(nowNode);
	DFS(Adj[nowNode].right);
	Ans3.push_back(nowNode);

}

void input() {

	cin >> V;
	Adj.resize(V);

	for (int i = 0; i < V; i++) {
		char parent, child1, child2;
		cin >> parent >> child1 >> child2;

		if (child1 != '.') {
			Adj[int(parent - 'A')].left = int(child1 - 'A');
		}
		else Adj[int(parent - 'A')].left = -1;

		if (child2 != '.') {
			Adj[int(parent - 'A')].right = int(child2 - 'A');
		}
		else Adj[int(parent - 'A')].right = -1;
	}
}

void print() {


	for (int i = 0; i < V; i++) {
		cout << char(Ans1[i] + 'A');
	}
	cout << "\n";

	for (int i = 0; i < V; i++) {
		cout << char(Ans2[i] + 'A');
	}
	cout << "\n";

	for (int i = 0; i < V; i++) {
		cout << char(Ans3[i] + 'A');
	}
	cout << "\n";
}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	DFS(0);
	print();

	return 0;
}