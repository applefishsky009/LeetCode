#include <stack>
#include <vector>
#include <iostream>
using namespace std;

// 单调栈
class Solution {
  public:
    int largestRectangleArea(vector<int> &height) {
        int i = 0, ans = 0, tmp = 0, len = height.size();
        stack<int> height_idx;
        height.push_back(0);
        for (i = 0; i < len + 1;) {
            if (height_idx.empty() || height[i] >= height[height_idx.top()])    // 递增序列入栈
                height_idx.push(i++);
            else {  // 出栈并计算面积
                tmp = height_idx.top();
                height_idx.pop();
                // 宽度 = 右边界(i) - 左边界(当前栈顶而非tmp下标), 左右均为开集, 额外减1
                ans = max(ans,  height[tmp] * (height_idx.empty() ? i : (i - height_idx.top() - 1))); 
            }
        }
        height.pop_back();
        return ans;
    }
};

int main() {
    Solution s;
    // vector<int> height = {2, 1, 5, 6, 2, 3};
    vector<int> height = {4, 2, 0, 3, 2, 5};
    // vector<int> height = {2, 1, 2};
    cout << s.largestRectangleArea(height) << endl;
    return 1;
}