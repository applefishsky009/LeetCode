#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 其他排序算法和哈希表就不实现了

// 桶排序, 缺点是改变了原先的数组
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    int missingNumber(vector<int> &nums) {
        nums.push_back(-1);
        for (int i = 0; i < nums.size(); ++i)
            while (nums[i] != -1 && i != nums[i])
                swap(nums[i], nums[nums[i]]);
        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] == -1)
                return i;
        return nums.size();
    }
};

// 桶排序的等效写法
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    int missingNumber(vector<int> &nums) {
        int ans = nums.size();
        nums.push_back(-1);
        for (int i = 0; i < nums.size(); ++i) {
            while (nums[i] != -1 && i != nums[i]) {
                swap(nums[i], nums[nums[i]]);
                if (nums[i] == -1)
                    ans = i;
            }
        }
        return ans;
    }
};

// 位运算 - 异或
// time: O(n)
// space: O(1)
class Solution1 {
  public:
    int missingNumber(vector<int> &nums) {
        int missing = nums.size();  // 下标异或多一个数字
        for (int i = 0; i < nums.size(); ++i)
            missing ^= i ^ nums[i];
        return missing;
    }
};

// 数学 - 高斯求和
// time: O(n)
// space: O(1)
class Solution {
  public:
    int missingNumber(vector<int> &nums) {
        int expecteedSum = ((nums.size() * (nums.size() + 1)) >> 1);  // 下标异或多一个数字
        int actualSum = 0;
        for (auto &x : nums) actualSum += x;
        return expecteedSum - actualSum;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {3, 0, 1};
    vector<int> nums1 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
    vector<int> nums2 = {1, 2};
    vector<int> nums3 = {1, 0};
    cout << s.missingNumber(nums0) << endl; // 2
    cout << s.missingNumber(nums1) << endl; // 8
    cout << s.missingNumber(nums2) << endl; // 0
    cout << s.missingNumber(nums3) << endl; // 2
    return 0;
}