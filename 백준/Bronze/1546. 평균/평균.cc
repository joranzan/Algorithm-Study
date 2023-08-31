#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int N; //과목의 수
	cin >> N;
	vector<float> Grade;
	Grade.resize(N);
	float max_grade;
	float sum = 0;
	float avg;


	for (int i = 0; i < N; i++)
	{
		cin >> Grade[i];
	}
	sort(Grade.begin(), Grade.end());
	max_grade = Grade.back();

	for (int i = 0; i < N; i++)
	{
		sum += (Grade[i] / max_grade) * 100;
	}
	avg = sum / N;
	cout << avg << "\n";

	return 0;
}