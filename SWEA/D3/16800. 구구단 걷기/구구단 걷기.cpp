#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int test_case;
    int T;
   // freopen("input.txt", "r", stdin);
    cin >> T;
   
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for (test_case = 1; test_case <= T; ++test_case)
    {
        vector<long long int> divider_pair;
        long long int N;
        cin >> N; 

        for (long long int i = 1; i <= sqrt(N); i++)
        {
            if (N % i == 0)
            {
                long long int candidate = (i-1)+((N/i)-1);
                divider_pair.push_back(candidate);
            }
        }
        sort(divider_pair.begin(), divider_pair.end());
        cout << "#" << test_case << " " << divider_pair[0] << "\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}