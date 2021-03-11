#include <stack>
#include <cctype>
#include <string>
#include <vector>
#include <numeric>
#include <iostream>
using namespace std;

// string stack
// time: O(n)
// space: O(n)
class Solution {
  public:
    int calculate(string s) {
        int inum = 0;
        char preSign = '+'; // 初始化计算符号
        vector<int> istk;   // 使用vector来模拟栈
        for (int i = 0; i < s.size(); ++i) {
            if (isdigit(s[i]))
                inum = inum * 10 + int(s[i] - '0');
            if ((!isdigit(s[i]) && s[i] != ' ') || (i == s.size() - 1)) { // || 最后一次计算
                switch (preSign)    // 根据上一次计算符号更新栈
                {
                case '+':
                    istk.push_back(inum);
                    break;
                case '-':
                    istk.push_back(-inum);
                    break;
                case '*':
                    istk.back() *= inum;
                    break;
                default:
                    istk.back() /= inum;
                    break;
                }
                preSign = s[i]; // 存储上一次计算符号
                inum = 0;
            }
        }
        return accumulate(istk.begin(), istk.end(), 0); // init = 0;
    }
};

int main() {
    Solution s;
    cout << s.calculate("3 + 2 * 2") << endl;
    cout << s.calculate("3 + 5 / 2") << endl;
    return 0;
}