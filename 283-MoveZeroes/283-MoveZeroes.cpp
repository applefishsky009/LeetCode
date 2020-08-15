#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 一次遍历
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    void moveZeroes(vector<int> &nums) {
        int i = 0, j = 0, len = nums.size();
        while (i < len) {
            while (i < len && nums[i] == 0) ++i;    // 指向第一个非零值
            while (j < len && nums[j] != 0) ++j;    // 指向第一个零
            if (i >= len || j >= len) return;
            if (j < i) swap(nums[i], nums[j]);
            ++i;    // 指向第一个非零值
        }
    }
};

// 空间局部优化
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    void moveZeroes(vector<int> &nums) {
        int n = nums.size();
        int numZeros = 0;   // 计算0的数量
        for (int i = 0; i < n; ++i) numZeros += (nums[i] == 0);
        vector<int> ans;
        for (int i = 0; i < n; ++i) 
            if (nums[i] != 0)
                ans.push_back(nums[i]);
        while (numZeros--)
            ans.push_back(0);
        for (int i = 0; i < n; ++i)
            nums[i] = ans[i];
    }
};

// 双指针 - 空间最优,操作局部优化 - 桶排序
// time: O(n)
// space: O(1)
class Solution2 {
  public:
    void moveZeroes(vector<int> &nums) {
        int lastNonZeroFoundAt = 0;
        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] != 0)   // 类似于桶排序, 将非零值放在他该放的位置上
                nums[lastNonZeroFoundAt++] = nums[i];
        for (int i = lastNonZeroFoundAt; i < nums.size(); ++i)
            nums[i] = 0;
    }
};

// 最优解 - 快慢指针 - 桶排序
// time: O(n)
// space: O(1)
class Solution {
  public:
    void moveZeroes(vector<int> &nums) {
        for (int cur = 0, lastNonZeroFoundAt = 0; cur < nums.size(); ++cur)
            if (nums[cur] != 0)   // 类似于桶排序, 将非零值放在他该放的位置上
                swap(nums[lastNonZeroFoundAt++], nums[cur]);
    }
};

int main() {
    Solution s;
    // vector<int> nums0 = {0, 1, 0, 3, 12};
    // vector<int> nums0 = {1, 3, 12, 0, 0};
    // vector<int> nums0 = {0, 0, 1, 3, 12, 0, 0};
    // vector<int> nums0 = {0, 0, 0, 0};
    // vector<int> nums0 = {1, 3, 12};
    // vector<int> nums0 = {1, 0};
    vector<int> nums0 = {1, 0, 1};
    show1DVector(nums0);
    s.moveZeroes(nums0);
    show1DVector(nums0);
    return 0;
}

