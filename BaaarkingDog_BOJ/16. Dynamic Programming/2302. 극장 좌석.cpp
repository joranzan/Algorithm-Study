#include<iostream>

using namespace std;

int N;
int Fixed[41] = { 0, };
int DP[41] = { 0, };


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		Fixed[temp] = 1;
	}

	DP[0] = 1;
	DP[1] = 1;

	for (int i = 2; i <= N; i++) {
		if (Fixed[i] == 1) {

		}
	}



	return 0;
}

/*
ÀÚ±â ¼ýÀÚ + ¿ÞÂÊ ¿À¸¥ÂÊ ¾ÉÀ» ¼ö ÀÖÀ½

VIP : ¿·ÁÂ¼® ¾ÉÀ»¼ö¾øÀ½

»ç¶÷µéÀÌ ÁÂ¼®¿¡ Ø´Â °¡Áþ¼ö

//N : 40°³
//°íÁ¤¼® M °³

1 2 3 4 5 6 7 8 9 


¾È¹Ù²Þ 



4 5 
5 4 





*/