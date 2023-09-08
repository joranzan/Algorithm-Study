#include<iostream>
#include<cstring>

using namespace std;

int cnt = 0;

int Recursion(const char* s, int l, int r)
{
    cnt+=1;
    if (s[l] != s[r])
    {
        return 0;
    }
    else if (l >= r)
    {
        return 1;
    }
    else
    {
        return Recursion(s, l + 1, r - 1);
    }
}
int isPalindrome(const char* s)
{
    return Recursion(s, 0, strlen(s) - 1);
}


int main(void)
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cnt = 0;
        char s[1001];
        cin >> s;
        cout << isPalindrome(s) << " ";
        cout<< cnt << endl;
    }
    return 0;
}