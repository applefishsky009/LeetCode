#include <map>
#include <cmath>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 暴力解法
class Solution1 {
  public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int i = 0, j = 0;
        vector<int> ans(T.size(), INT_MAX);
        unordered_map<int, int> t_map;
        for (i = T.size() - 1; i >= 0; i--) { 
            for (j = T[i] + 1; j < 101; j++)
                if (t_map[j] && ans[i] > t_map[j] - i)
                    ans[i] = t_map[j] - i;
            ans[i] = (ans[i] == INT_MAX ? 0 : ans[i]);
            t_map[T[i]] = i;
        }
        return ans;
    }
};

// 单调递减栈
class Solution2 {
  public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int i = 0;
        vector<int> ans(T.size(), 0);
        stack<int> s;
        for(i = 0; i < T.size(); i++) {
            while (!s.empty() && T[i] > T[s.top()]) {  // 出栈,更新
                ans[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);  // 入栈
        }
        return ans;
    }
};

// jump-DP
class Solution {
  public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int i = 0, j = 0;
        vector<int> ans(T.size(), 0);
        for(i = T.size() - 1; i >= 0; i--) {
            j = i + 1;
            while(j < T.size()) {
                if (T[j] > T[i]) {
                    ans[i] = j - i;
                    break;
                }
                else if (ans[j] == 0) {
                    break;
                }
                else {
                    j += ans[j];
                }
            }
        }
        return ans;
    }
};


int main() {
    Solution s;
    vector<int> T = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> ans = s.dailyTemperatures(T);
    show1DVector(ans);
    return 1;
}
