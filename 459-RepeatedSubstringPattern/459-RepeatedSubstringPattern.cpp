#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 枚举
// time: O(n^2)
// space: O(n) - 这里利用取余运算和math可以达到O(1)
// 长度为n'的子串s', n一定是n'的倍数, s一定是s'的前缀 对于i在[n',n)有s[i] = s[i - n']
class Solution0 {
  public:
    bool repeatedSubstringPattern(string s) {
        int ilen = s.size();
        int ihalf = (ilen >> 1) + 1;
        for (int i = 1; i <= ihalf; ++i) {
            if (ilen % i != 0 || ilen / i == 1) continue;   // 不能整除 或 重复一次则继续搜索
            string str_tmp;
            string tmp = s.substr(0, i);
            for (int j = 0; j < ilen / i; ++j)
                str_tmp += tmp;
            if (str_tmp == s) return true;
        }
        return false;
    }
};

// 字符串匹配
class Solution1 {
  public:
    bool repeatedSubstringPattern(string s) {
        return (s + s).find(s, 1) != s.size();
    }
};

// KMP算法
// time: O(n)
// space: O(n)
class Solution2 {
  public:
    bool repeatedSubstringPattern(string s) {
        return kmp(s + s, s);
    }
  private:
    bool kmp(const string &query, const string &pattern) {
        const int n = query.size();
        const int m = pattern.size();
        vector<int> fail(m, -1);
        for (int i = 1; i < m; ++i) {
            int j = fail[i - 1];
            while (j != -1 && pattern[j + 1] != pattern[i])
                j = fail[j];
            if (pattern[j + 1] == pattern[i])
                fail[i] = j + 1;
        }
        int match = -1;
        for (int i = 1; i < n - 1; ++i) {
            while (match != -1 && pattern[match + 1] != query[i])
                match = fail[match];
            if (pattern[match + 1] == query[i]) {
                ++match;
                if (match == m - 1)
                    return true;
            }
        }
        return false;
    }
};

// 优化的KMP算法
// 若字符串是长度为i的字符串重复n/i次组成m, 那么fail[n - 1] = n - i - 1, n一定是i = n - fail[n - 1] - 1的倍数
// time: O(n)
// space: O(n)
class Solution {
  public:
    bool repeatedSubstringPattern(string s) {
        return kmp(s);
    }
  private:
    bool kmp(const string &pattern) {
        const int n = pattern.size();
        vector<int> fail(n, -1);
        for (int i = 1; i < n; ++i) {
            int j = fail[i - 1];
            while (j != -1 && pattern[j + 1] != pattern[i])
                j = fail[j];
            if (pattern[j + 1] == pattern[i])
                fail[i] = j + 1;
        }
        return fail[n - 1] != -1 && n % (n - fail[n - 1] - 1) == 0;
    }
};

int main() {
    Solution s;
    string str3 = "ab";
    string str0 = "aba";
    string str1 = "abab";
    string str2 = "abcabcabcabc";
    cout << s.repeatedSubstringPattern(str3) << endl;   // 0
    cout << s.repeatedSubstringPattern(str0) << endl;   // 0
    cout << s.repeatedSubstringPattern(str1) << endl;   // 1
    cout << s.repeatedSubstringPattern(str2) << endl;   // 1
    return 0;
}