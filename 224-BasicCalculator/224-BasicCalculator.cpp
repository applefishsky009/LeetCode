#include <stack>
#include <string>
#include <iostream>
using namespace std;

// 括号展开+栈 记录括号的符号
// time: O(n)
// space: O(n)
class Solution{
  public:
    int calculate(string s) {
        stack<int> ops;
        ops.push(1);
        int sign = 1, ret = 0, i = 0;
        while (i < s.size()) {
            if (s[i] == ' ') {
                ++i;
            } else if (s[i] == '+') {
                sign = ops.top();   // ops.top()始终是当前括号的整体符号
                ++i;
            } else if (s[i] == '-') {
                sign = -ops.top();
                ++i;
            } else if (s[i] == '(') {
                ops.push(sign);
                ++i;
            } else if (s[i] == ')') {
                ops.pop();
                ++i;
            } else {
                long num = 0;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9') {    // 得到数字
                    num = num * 10 + s[i] - '0';
                    ++i;
                }
                ret += sign * num;
            }
        }
        return ret;
    }
};

int main() {
    Solution s;
    // cout << s.calculate("1 + 1") << endl;
    // cout << s.calculate("2-1 + 2") << endl;
    cout << s.calculate("(1+(4+5+2)-3)+(6+8)") << endl;
    return 0;
}