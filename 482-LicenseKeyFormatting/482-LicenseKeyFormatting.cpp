#include <stack>
#include <string>
#include <iostream>
using namespace std;

// stack
// time: O(n)
// space: O(n)
class Solution {
  public:
    string licenseKeyFormatting(string S, int K) {
        int cnt = 0;
        string istr;
        stack<char> istk;
        for (int i = S.size() - 1; i >= 0; --i) {
            if (S[i] == '-')
                continue;
            if (islower(S[i]))
                istk.push(toupper(S[i]));
            else
                istk.push(S[i]);
            if (++cnt == K) {   // 可能会多一个-
                cnt = 0;
                istk.push('-');
            }
        }
        if (!istk.empty() && istk.top() == '-')
            istk.pop();
        while (!istk.empty()) {
            istr += istk.top();
            istk.pop();
        }
        return istr;
    }
};

int main() {
    Solution s;
    // cout << s.licenseKeyFormatting("5F3Z-2e-9-w", 4) << endl;
    // cout << s.licenseKeyFormatting("2-5g-3-J", 2) << endl;
    // cout << s.licenseKeyFormatting("--a-a-a-a--", 2) << endl;
    cout << s.licenseKeyFormatting("----", 2) << endl;
    return 0;
}