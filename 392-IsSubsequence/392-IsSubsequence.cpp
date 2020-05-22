#include <string>
#include <vector>
#include <iostream>
using namespace std;

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

class Solution {
  public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0, len = t.size();
        vector<vector<int>> s_map(len + 1, vector<int>(26, -1)); // 当前map表示下一个字符出现的位置，和本位置没有关系。因此需要在第i位置更新i-1的map
        for (i = len - 1; i >= 0; i--) // pre-work, -1代表没有找到
            for (j = 'a'; j <= 'z'; j++)
                s_map[i][j - 'a'] = (t[i] == j ? i + 1 : s_map[i + 1][j - 'a']);    // s_map[i]和t[i]错一位，赋值 + 1
        i = 0; j = 0;
        while (j != -1 && i < s.size())    //  jump
            j = s_map[j][s[i++] - 'a'];
        return j != -1;
    }
};


int main() {
    Solution s;
    string sin = "abc";
    string tin = "ahbgdc";
    // string sin = "axc";
    // string tin = "bahbgdcb";
    // string sin = "axc";
    // string tin = "";
    // string sin = "aaaaaa";
    // string tin = "bbaaaa";
    // string sin = "a";
    // string tin = "abc";
    cout << s.isSubsequence(sin, tin) << endl;
    return 1;
}