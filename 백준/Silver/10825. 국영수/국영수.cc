#include<iostream>
#include<algorithm>

using namespace std;

struct score {
	string name;
	int la;
	int en;
	int ma;

	bool operator<(score next) {
		if (la < next.la) return false;
		else if (la > next.la) return true;
		else {
			if (en < next.en) return true;
			else if (en > next.en) return false;
			else {
				if (ma < next.ma) return false;
				else if (ma > next.ma) return true;
				else {
					if (name < next.name) return true;
					else if (name > next.name) return false;
					else return false;
				}
			}
		}
	}
};

score student[100000];

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		string s;
		int s1, s2, s3;
		cin >> s >> s1 >> s2 >> s3;
		student[i] = { s, s1,s2,s3 };
	}

	sort(student, student + N);

	for (int i = 0; i < N; i++) {
		cout << student[i].name << "\n";
	}
	
	return 0;
}