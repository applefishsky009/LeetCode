#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// stack
// time: O(n)
// space: O(n)
class Solution {
  public:
    string removeDuplicates(string s) {
        string istk;
        for (auto &ch : s) {
            if (!istk.empty() && istk.back() == ch) {
                istk.pop_back();
            } else {
                istk.push_back(ch);
            }
        }
        return istk;
    }
};

int main() {
    Solution s1;
    string s = "abbaca"; // ca
    cout << s1.removeDuplicates(s) << endl;
    return 0;
}