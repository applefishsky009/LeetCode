#include <stack>
#include <string>
#include <iostream>
using namespace std;

// stack
// time: O(n + m)
// space: O(n + m)
class Solution1 {
  public:
    bool backspaceCompare(string s, string t) {
        stack<int> istks, istkt;
        for (auto &s_t : s) {
            if (s_t == '#' && !istks.empty()) {
                istks.pop();
            } else if (s_t != '#') {
                istks.push(s_t);
            }
        }
        for (auto t_t : t) {
            if (t_t == '#' && !istkt.empty()) {
                istkt.pop();
            } else if (t_t != '#') {
                istkt.push(t_t);
            }
        }
        while (!istks.empty() && !istkt.empty() && istks.top() == istkt.top()) {
            istks.pop();
            istkt.pop();
        }
        return (istks.empty() && istkt.empty()) ? true : false;
    }
};

// TP
// time: O(n + m)
// space: O(1)
class Solution {
  public:
    bool backspaceCompare(string s, string t) {
        int ip = s.size() - 1, iq = t.size() - 1;   // 从后往前遍历
        int skips = 0, skipt = 0;   // 记录销字符次数
        for (; ip >= 0 || iq >= 0; ip--, iq--) {
            while (ip >= 0) {
                if (s[ip] == '#') {
                    skips++; ip--;
                } else if (skips > 0) {
                    skips--; ip--;
                } else {
                    break;
                }
            }
            while (iq >= 0) {
                if (t[iq] == '#') {
                    skipt++; iq--;
                } else if (skipt > 0) {
                    skipt--; iq--;
                } else {
                    break;
                }
            }
            if (ip >= 0 && iq >= 0) {
                if (s[ip] != t[iq]) {
                    return false;
                }
            } else {
                if (ip >= 0 || iq >= 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution s1;
    // string s = "ab#c";
    // string t = "ad#c";   // 1
    // string s = "ab##";
    // string t = "c#d#";  // 1
    string s = "a#c";
    string t = "b";     // 0
    // string s = "y#fo##f";
    // string t = "y#f#o##f";  // 1
    cout << s1.backspaceCompare(s, t) << endl;
    return 0;
}