#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        // 문자열 길이가 1이면 반드시 팰린드롬이다.
        if (n <= 1) return s;

        // is_pal[i][j] == 1 -> i 부터 j까지 팰린드롬이다.
        vector<vector<bool>> is_pal(n, vector<bool>(n, 0));
        int b = 0;
        int max_len = 1;
        // 길이 1은 모두 팰린드롬이다.
        for (int i=0; i<n; i++) is_pal[i][i] = 1;

        // 연속된 두 글자가 같으면 팰린드롬이다.
        for (int i=0; i<n-1; i++) {
            if (s[i] == s[i+1]) {
                is_pal[i][i+1] = 1;
                max_len = 2;
                b = i;
            }
        }

        // 점화식
        // is_pal[i][j] = (s[i] == s[j]) and (is_pal[i+1][j-1])
        for (int len=3; len<=n; len++) {
            for (int i=0; i<=n-len; i++) {
                int j = i + len - 1;
                is_pal[i][j] = (s[i] == s[j]) && (is_pal[i+1][j-1]);
                if (len > max_len && is_pal[i][j]) {
                    max_len = len;
                    b = i;
                }
            }
        }

        return s.substr(b, max_len);
    }
};
