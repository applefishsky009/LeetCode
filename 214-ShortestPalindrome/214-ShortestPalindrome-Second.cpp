#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// RKHash
// 将s分为两部分, 回文串s1和后缀s2, 要添加的最小前缀s'一定是s2的逆序, 那么s1本身是回文串且要求最长的s1
// 使用RKHash判断是否回文串即 正序反序的hash相等
// time: O(|s|)
// space: O(1)
class Solution0 {
  public:
    string shortestPalindrome(string s) {
        int n = s.size();
        int base = 131, mod = 1000000007;
        int left = 0, right = 0, mul = 1, best = -1;
        for (int i = 0; i < n; ++i) {   // i表示回文串s1的截止点, 0一定是回文
            left = ((long long)left * base + s[i]) % mod;   // 加在左边
            right = (right + (long long)mul * s[i]) % mod;  // 加在右边
            if (left == right)  // 回文
                best = i;
            mul = (long long) mul * base % mod;  // 进制
        }
        string add = (best == n - 1 ? "" : s.substr(best + 1, n));  // 计算s2, 第二个参数如果超过了s的长度, 尽可能取最大值
        reverse(add.begin(), add.end());    // 计算s'
        return add + s;
    }
};

// KMP
// 记s^为s的反序, s1是s的前缀, s1^是s^的后缀, s1是回文串, s1=s1^, 那么将s作为模式串, s^作为查询串进行匹配, 当遍历到s^末尾时
// 如果匹配到s中的第i个字符, 那么说明s中的前i个字符和s^中的后i个字符相匹配, 对应s1和s1^
// time: O(|s|)
// space: O(|s|)
class Solution {
  public:
    string shortestPalindrome(string s) {
        int n = s.size();
        vector<int> fail(n, -1);
        for (int i = 1; i < n; ++i) {   // 计算模式字符串的fail数组
            int j = fail[i - 1];    // 前一状态, 取和真后缀匹配的真前缀的idx
            while (j != -1 && s[j + 1] != s[i]) // 失配则回溯, 回溯到底或者(前缀和后缀)完全匹配则停止
                j = fail[j];    // 失配一次表示可匹配长度要缩减, 看真前缀的子串能不能抢救一下, 而不是失配就从头开始
            if (s[j + 1] == s[i])   // 如果前缀和后缀可以匹配到, 更新, 表明下一个的idx真前缀匹配到了
                fail[i] = j + 1;
        }
        int best = -1;
        for (int i = n - 1; i >= 0; --i) {
            while (best != -1 && s[best + 1] != s[i])
                best = fail[best];
            if (s[best + 1] == s[i])
                ++best;
        }
        string add = (best == n - 1 ? "" : s.substr(best + 1, n));
        reverse(add.begin(), add.end());
        return add + s;
    }
};

int main() {
    Solution s1;
    // string s = "ba";
    string s = "aacecaaa";
    cout << s1.shortestPalindrome(s) << endl;
    return 0;
}