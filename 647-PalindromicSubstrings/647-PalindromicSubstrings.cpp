#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// 中心扩展法
// time: O(n^2)
// space: O(n)
class Solution0 {
  public:
    int countSubstrings(string s) {
        int ans = s.size(); // 单个字符是回文串
        string news = "&$";
        for (auto c : s) news += (string(1, c) + "$");
        news += '^';    // 构造分析字符
        for (int i = 1; i < news.size() - 1; ++i) {
            int l = i - 1, r = i + 1;
            while (l >= 0 && r <= news.size() - 1 && news[l--] == news[r++])
                if (news[l + 1] != '$') // 半径上的$不参与计算, 但起始位置的需要参与
                    ans++;
        }
        return ans;
    }
};

// 中心扩展法 回文中心左起, 右起位置对0-(0, 0), 1-(0, 1), 2-(1, 1), 3-(1, 2), 4-(2, 2), 5-(2, 3), 6-(3, 3), 7-(3, 4)
// 那么l = i / 2, r = l + i mod 2; i的截止长度为2 * len
// time: O(n^2)
// space: O(1)
class Solution1 {
  public:
    int countSubstrings(string s) {
        int len = s.size(), ans = 0;
        for (int i = 0; i < 2 * len - 1; ++i) {
            int l = i / 2, r = i / 2 + i % 2;
            while (l >= 0 && r < len && s[l--] == s[r++])
                ++ans;
        }
        return ans;
    }
};

// Manacher算法
// time: O(n)
// space: O(1)
class Solution {
  public:
    int countSubstrings(string s) {
        string news = "$#";
        for (auto c : s) news += (string(1, c) + "#");
        news += "!";    // 字符串经处理后用f[i]表示以s位为回文中心, 可以扩展出的最大回文半径, 那么f[i] - 1就是以i为中心的最大回文串长度
        int len = news.size(), ans = 0, iMax = 0, rMax = 0; // 最大回文右端点对应的回文中心和最大回文右端点
        vector<int> idp(len, 0); 
        for (int i = 1; i < len - 1; ++i) { // rMax - i + 1表示半径截断在rMax, 注意头尾不用判断
            idp[i] = (i <= rMax) ? min(rMax - i + 1, idp[2 * iMax - i]) : 1;    // 初始化f[i], 判断i是否在最大回文右端点内, 在内则是对称位置的半径和最大半径到i的距离小值(因为左侧的回文半径可能越过rMax)
            while(news[i + idp[i]] == news[i - idp[i]]) ++idp[i];   // 中心扩展
            if (i + idp[i] - 1 > rMax) { // 动态维护iMax和rMax  // 右端点为i + f[i] - 1, 表示需要更新右端点以及回文中心
                iMax = i;
                rMax = i + idp[i] - 1;
            }
            ans += (idp[i] / 2);    // 统计答案, 当前贡献为(f[i] - 1) / 2[上]取整 /2是因为加入了字符串 1-0 2-1 3-1 4-2 5-2...
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.countSubstrings("abc") << endl;    // 3
    cout << s.countSubstrings("aaa") << endl;   // 6
    // cout << s.countSubstrings("&$a$b$c$^") << endl;
    // cout << s.countSubstrings("&$a$a$a$^") << endl;
    return 0;
}