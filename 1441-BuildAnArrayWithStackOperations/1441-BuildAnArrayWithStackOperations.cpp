#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// stack
// time: O(n)
// space: O(n)
class Solution {
  public:
    vector<string> buildArray(vector<int> &target, int n) {
        int i = 0, j = 0;
        stack<int> istk;
        vector<string> ans;
        for (i = 1, j = 0; i <= n, j < target.size(); ++i) {
            ans.push_back("Push");
            istk.push(i);
            if (istk.top() != target[j]) {  // 非目标数组元素
                istk.pop(); // 构建目标数组
                ans.push_back("Pop");
            } else {
                ++j;
            }
        }
        return ans;
    }
};

int main() {
    Solution s1;
    // vector<int> target = {1, 3};
    // vector<int> target = {1, 2, 3};
    vector<int> target = {1, 2};
    show1DVector(s1.buildArray(target, 4));
    return 0;
}