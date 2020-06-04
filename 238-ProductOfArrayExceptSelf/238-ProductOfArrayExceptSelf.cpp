#include <vector>
#include <numeric>
#include <iterator>
#include <iostream>
#include <D:\Github\RylModule\vector.h>
using namespace std;

class Solution1 {
  public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int i = 0, sum = 1, len = nums.size();
        // vector<int> ans(len + 1, 1);
        vector<int> ans(len, nums[len - 1]);
        // for (i = len - 1; i >= 0; i--)
        for (i = len - 2; i >= 0; i--)
            ans[i] = nums[i] * ans[i + 1];
        for (i = 0; i < len - 1; i++) {
            ans[i] = sum * ans[i + 1];
            sum *= nums[i];
        }
        ans[len - 1] = sum;
        // ans.pop_back();
        return ans;
    }
};

// 容器改变大小可能会有耗时风险
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(1, 1), suffix(1, 1);
        auto cal = [&](const int& a, const int& b) -> int{ return a * b; };
        partial_sum(nums.cbegin(), nums.cend(), back_inserter(prefix), cal);
        partial_sum(nums.crbegin(), nums.crend(), back_inserter(suffix), cal);
        for (int i = 0; i < n; ++ i)
            nums[i] = prefix[i] * suffix[n - i - 1];
        return nums;
    }
};

int main() {
    Solution s;
    vector<int> input = {1, 2, 3, 4};
    show1DVector(s.productExceptSelf(input));
    return 1;
}