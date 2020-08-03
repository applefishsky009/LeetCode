#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// 按位模拟 - 自己实现的, 计算过程过于冗余
// time: O(max(len1, len2))
// space: O(1)
class Solution1 {
  public:
    string addStrings(string num1, string num2) {
        int n = num1.size(), m = num2.size();
        if (n < m) return addStrings(num2, num1);
        int carry = 0, i = 0, j = 0, k = 0;
        string s = "0" + num1;
        for (i = m - 1, j = n - 1; i >= 0; --i, --j) {
            char tmp = (num1[j] - '0') + (num2[i] - '0') + carry + '0';
            if (tmp > '9') {
                carry = 1;
                tmp -= 10;
            } else {
                carry = 0;
            }
            s[k++] = tmp;
        }
        for (int i = n - m - 1; i >= 0; --i) {
            char tmp = (num1[i] - '0') + carry + '0';
            if (tmp > '9') {
                carry = 1;
                tmp -= 10;
            } else {
                carry = 0;
            }
            s[k++] = tmp;
        }
        s[k] = carry ? '1' : '0';
        reverse(s.begin(), s.end());
        return s[0] == '0' ? s.substr(1) : s;
    }
};

// 按位模拟
// time: O(max(len1, len2))
// space: O(1)
class Solution {
  public:
    string addStrings(string num1, string num2) {
        int i = num1.length() - 1, j = num2.length() - 1, add = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0 ? num1[i] - '0' : 0;
            int y = j >= 0 ? num2[j] - '0' : 0;
            int result = x + y + add;
            ans.push_back('0' + result % 10);
            add = result / 10;
            --i;
            --j;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    Solution s;
    string num10 = "12378";
    string num20 = "456";    // 12834
    string num11 = "999";
    string num21 = "999";    // 1998
    string num12 = "0";
    string num22 = "999";    // 999
    string num13 = "999999";
    string num23 = "999";    // 1998
    cout << s.addStrings(num10, num20) << endl;
    cout << s.addStrings(num11, num21) << endl;
    cout << s.addStrings(num12, num22) << endl;
    cout << s.addStrings(num13, num23) << endl;
    return 0;
}