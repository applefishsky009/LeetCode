#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 等价转化 - 所有数相等, 相对值为0, 假设一次移动使最大值和其他所有数的相对值缩小1, 等价于将最大值减1而其他值不变
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    int minMoves(vector<int> &nums) {
        int imin = INT_MAX, ans = 0;
        for (auto &x : nums) imin = min(imin, x);
        for (auto &x : nums) ans += (x - imin);
        return ans;
    }
};

// dp
// 考虑有序数组a的第i位元素, 将差值diff=a[i]-a[i-1]加到总移动次数上, 使得第i为也相等, moves = moves + diff
// 在实现的时候不需要将diff加在i之后的元素上, 关注i之后的相对大小, 相当于将diff加在a[i]上.
// time: O(nlgn)
// space: O(1)
class Solution {
  public:
    int minMoves(vector<int> &nums) {
        int imoves = 0;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++i) {
            int diff = (imoves + nums[i]) - nums[i - 1];
            nums[i] += imoves;
            imoves += diff;
        }
        return imoves;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 2, 3};
    cout << s.minMoves(nums) << endl;
    return 0;
}