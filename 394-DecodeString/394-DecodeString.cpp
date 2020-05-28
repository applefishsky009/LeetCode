#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <iostream>
using namespace std;

// 左右匹配，栈
class Solution1 {
  public:
    string decodeString(string s) {
        string ans, dup_int;
        stack<char> sck;
        int dup = 0, i = 0, j = 0, len = 0;
        for (auto &x : s) {
            if (x == ']') {
                ans = "";
                while (sck.top() != '[') {
                    ans = sck.top() + ans;
                    sck.pop();
                }
                sck.pop();
                dup_int = "";
                while (!sck.empty() && isdigit(sck.top())) {
                    dup_int = sck.top() + dup_int;
                    sck.pop();
                }
                dup = atoi(dup_int.c_str());
                len = ans.size();
                for (i = 0; i < dup; i++)
                    for (j = 0; j < len; j++)
                        sck.push(ans[j]);
            } else {
                sck.push(x);
            }
        }
        ans = "";
        while (!sck.empty()) {
            ans = sck.top() + ans;
            sck.pop();
        }
        return ans;
    }  
};

// 递归
class Solution {
  public:
    string decodeString(string s) {
        src = s;
        ptr = 0;
        return getString();
    }
  private:
    string src; 
    size_t ptr;
    int getDigits() {
        int ret = 0;
        while (ptr < src.size() && isdigit(src[ptr]))
            ret = ret * 10 + src[ptr++] - '0';
        return ret;
    }
    string getString() {
        if (ptr == src.size() || src[ptr] == ']')
            return "";  // String -> EPS
        char cur = src[ptr]; 
        int repTime = 1;
        string ret;
        if (isdigit(cur)) {
            repTime = getDigits(); // 解析 Digits // String -> Digits [ String ] String
            ++ptr; // 过滤左括号
            string str = getString(); // 递归解析 String
            ++ptr; // 过滤右括号
            while (repTime--) 
                ret += str; // 构造字符串
        } else if (isalpha(cur))
            ret = string(1, src[ptr++]);    // 解析 Char    // String -> Char String
        return ret + getString();   //  继续解析
    }
};

int main() {
    Solution s;
    string str = "3[a]2[bc]";    // aaabcbc
    // string str = "3[a2[c]]";     // accaccacc
    // string str = "2[abc]3[cd]ef";   // abcabc3cd3cd3cdef
    cout << s.decodeString(str) << endl;
    return 1;
}