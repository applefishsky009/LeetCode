#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int maxProduct(vector<int> &nums)
    {
        assert(!nums.empty());
        const int n = nums.size();
        int posMax = nums[0];
        int negMin = nums[0];
        int result = nums[0];
        for (int i = 1; i < n; i++)
        {
            int a = posMax * nums[i];
            int b = negMin * nums[i];
            //these two sentences let posMax and negMin different
            //if nums[i] = 0, posMax and negMin will set to zeros.
            posMax = max(nums[i], max(a, b));
            negMin = min(nums[i], min(a, b));
            result = max(result, posMax);
        }
        return result;
    }
};

int main()
{
    vector<int> nums = {-2, 3, 4};
    Solution s1;
    cout << s1.maxProduct(nums) << endl;
    return 0;
}