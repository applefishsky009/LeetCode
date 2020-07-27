#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Greedy
// time: O(n + m)
// space: O(1)
class Solution1 {
  public:
    bool isSubsequence(string s, string t) {
        int t_idx = 0, s_idx = 0;
        while (t_idx < t.size())
            if (t[t_idx++] == s[s_idx])
                s_idx++;
        return s_idx == s.size();
    }
};

// Greedy
// 下标代表从当前位(占据)往后看的第一个字符的位置, 这必然不包括当前位, 是当前位的开区间, 这样第一个字符就不被包括了. 所以需要一个哨兵.
// time: O(n + m)
// space: O(n)
class Solution2 {
  public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0, len = t.size();   // t需要一个哨兵
        vector<vector<int>> imap(len + 1, vector<int>(26, -1));
        for (i = len - 1; i >= 0; --i)  // 记录站在idx = i之前看到的各个字符位置, 因此需要多一位i = 0. 和排列组合中找空位比较像
            for (j = 'a'; j <= 'z'; ++j)
                imap[i][j - 'a'] = (t[i] == j ? i + 1: imap[i + 1][j - 'a']);
        i = 0, j = 0;
        while (j != -1 && i < s.size()) // jump
            j = imap[j][s[i++] - 'a'];  // 跳转到当前位, 向后看
        return j != -1;
    }
};

// DP - 占据当前位置并跳过
// f[i][j] = i if t[i] == j else f[i + 1][j] if t[i] != j;
// time: O(n + m)
// space: O(n)
class Solution {
  public:
    bool isSubsequence(string s, string t) {
        int n = t.size(), m = s.size();
        vector<vector<int>> idp(n + 1, vector<int>(26, 0));
        for (int i = 0; i < 26; i++)
            idp[n][i] = n;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < 26; ++j) {
                if (t[i] == j + 'a')
                    idp[i][j] = i;
                else
                    idp[i][j] = idp[i + 1][j];
            }
        }
        int add = 0;
        for (int i = 0; i < m; ++i) {
            if (idp[add][s[i] - 'a'] == n)
                return false;
            add = idp[add][s[i] - 'a'] + 1; // 跳转到当前位, 向后看
        }
        return true;
    }
};

int main() {
    Solution s;
    string sin0 = "abc";
    string tin0 = "ahbgdc";  // 1
    string sin1 = "axc";
    string tin1 = "bahbgdcb"; //0
    string sin2 = "axc";
    string tin2 = ""; // 0
    string sin3 = "aaaaaa";
    string tin3 = "bbaaaa";   // 0
    string sin4 = "a";
    string tin4 = "abc";  //1
    // cout << s.isSubsequence(sin0, tin0) << endl;
    // cout << s.isSubsequence(sin1, tin1) << endl;
    // cout << s.isSubsequence(sin2, tin2) << endl;
    cout << s.isSubsequence(sin3, tin3) << endl;
    // cout << s.isSubsequence(sin4, tin4) << endl;
    return 1;
}