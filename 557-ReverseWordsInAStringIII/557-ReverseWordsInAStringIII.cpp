#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// time: O(n)
// space: O(n)
class Solution0 {
  public:
    string reverseWords(string s) {
        string ans;
        stack<char> istk;
        for (auto &c : s) {
            if (c != ' ') {
                istk.push(c);
            }
            else {
                while (!istk.empty()) {
                    ans.push_back(istk.top());
                    istk.pop();
                }
                ans += " ";
            }
        }
        while (!istk.empty()) {
            ans.push_back(istk.top());
            istk.pop();
        }
        return ans;
    }
};

// inplace
// time: O(n)
// space: O(1)
class Solution {
  public:
    string reverseWords(string s) {
        int len = s.size(), i = 0;
        while (i < len) {
            int start = i;
            while (i < len && s[i] != ' ')  // 找当前右边界
                ++i;
            int left = start, right = i - 1;
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
            while (i < len && s[i] == ' ')  // 跳过空格
                ++i;
        }
        return s;
    }
};

int main() {
    Solution s;
    string str = "Let's take LeetCode contest";
    cout << s.reverseWords(str) << endl;
    return 0;
};
