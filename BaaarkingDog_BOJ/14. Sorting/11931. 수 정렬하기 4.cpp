#include<bits/stdc++.h>

using namespace std;


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	vector<int> v{ 0, 1, 2, 3, 4 };

	for (size_t i = 0; i < v.size(); i++) {
		cout << v.begin()[i] << " " << v.end()[~i]<<"\n";
	}


	return 0;
}