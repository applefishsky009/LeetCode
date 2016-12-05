#include <vector>
#include <iostream>
using namespace std;

//注意递推关系式
//nStart[i] = max(nStart[i-1]+A[i],nAll[i-1]);
//nAll[i] = max(nStart[i],nAll[i-1])
class Solution
{
  public:
    int maxSubArray(vector<int> &nums)
    {
		int nStart = nums[0];
		int nAll = nums[0];
		for (int i = 1; i < nums.size(); ++i)
		{
			nStart = nStart + nums[i] > nums[i] ? nStart + nums[i] : nums[i];
			nAll = nStart > nAll ? nStart : nAll;
		}
		return nAll;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {10, -2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << s1.maxSubArray(nums) << endl;
    return 0;
}