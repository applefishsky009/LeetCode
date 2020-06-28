#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// O(n) Solution 参考第一次的解法,更简洁一些,类似于单调栈的实现细节
class Solution1 {
  public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int len = nums.size();
        if (len == 0) return 0;
        int l = 0, r = 1, sum = nums[0], ans = INT_MAX; // 头和超尾
        // while (!(r >= len && sum < s)) {
        while (r < len || sum >= s) {
            if (sum >= s)
                ans = min(ans, r - l);
            if (sum < s)
                sum += nums[r++];
            else
                sum -= nums[l++];
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

// O(nlgn) Solution
class Solution {
  public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int len = nums.size();
        vector<int> sums(len + 1, 0);   // 初始状态, 让upper_bound可以搜索到第一个sums[i] + s - 1
        int ans = INT_MAX;
        for (int i = 1; i < len + 1; i++)
            sums[i] = sums[i - 1] + nums[i - 1];
        for (int i = 0; i < len; i++) {
            // auto p = upper_bound(sums.begin(), sums.end(), s + sums[i] - 1);
            // if (p != sums.end())
            //     ans = min(ans, (int)(p - sums.begin()) - i);    // sums.begin()多一个, 因此不用+1
            auto p = my_upper_bound(sums, 0, len + 1, s + sums[i] - 1);
            if (p != len + 1)
                ans = min(ans, p - i);    // sums.begin()多一个, 因此不用+1
        }
        return ans == INT_MAX ? 0 : ans;
    }
  private:
    int my_upper_bound(vector<int> &nums, int start, int end, int target) { // end为超尾, 模仿STL的实现
        int mid = 0, l = start, r = end;
        while (l < r) {
            mid = (l + r) >> 1;
            if (nums[mid] <= target)    // 因为需要找到大于target的第一个,因此小于等于需要更新
                l = mid + 1;    // 二分必须向上收缩, 否则死循环
            else
                r = mid;
        }
        return l == end ? end : l;  // 搜索到返回下标, 否则返回超尾
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {2, 3, 1, 2, 4, 3};
    vector<int> nums1 = {10, 2, 3};
    vector<int> nums2 = {1, 1};
    vector<int> nums3 = {};
    cout << s.minSubArrayLen(7, nums0) << endl;
    cout << s.minSubArrayLen(6, nums1) << endl;
    cout << s.minSubArrayLen(3, nums2) << endl;
    cout << s.minSubArrayLen(100, nums3) << endl;
    return 1;
}