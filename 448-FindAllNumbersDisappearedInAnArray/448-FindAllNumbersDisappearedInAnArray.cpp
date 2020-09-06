#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 桶排序
// time: O(n)
// space: O(1)
class Solution {
  public:
    vector<int> findDisappearedNumbers(vector<int> &nums) {
        vector<int> ans;
        for (int i = 0; i < nums.size(); ++i)
            while (nums[i] != i + 1 && nums[i] != nums[nums[i] - 1])    // 注意值和下标的映射即可
                swap(nums[i], nums[nums[i] - 1]);
        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] != i + 1)
                ans.push_back(i + 1);
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {4, 3, 2, 7, 8, 2, 3, 1};
    show1DVector(s.findDisappearedNumbers(nums0));
    return 0;
}