#include <stack>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// stack
// time: O(n)
// space: O(n)
class Solution {
  public:
    int calPoints(vector<string> &ops) {
        int ans = 0;
        stack<int> istk;
        for (auto &op : ops) {
            if (op == "C") {
                istk.pop();
            } else if (op == "D") {
                istk.push(istk.top() * 2);
            } else if (op == "+") {
                int pre1 = istk.top();
                istk.pop();
                int pre2 = istk.top();
                istk.push(pre1);
                istk.push(pre1 + pre2);
            } else {
                int tmp = stoi(op);
                istk.push(tmp);
            }
        }
        while (!istk.empty()) {
            ans += istk.top();
            istk.pop();
        }
        return ans;
    }
};

int main() {
    Solution s;
    // vector<string> ops = {"5", "2", "C", "D", "+"};
    vector<string> ops = {"5", "-2", "4", "C", "D", "9", "+", "+"};
    cout << s.calPoints(ops) << endl;
    return 0;
}