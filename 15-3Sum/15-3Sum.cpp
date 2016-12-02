#include <vector>
#include <iterator>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//自己写的，先排序，注意两点，1. 双指针跳过重复值；2. 第三个指针遍历也要跳过重复值
class Solution
{
  public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
		vector<vector<int>> result;
		if (nums.size() < 3)
			return result;
		vector<int> path;
		sort(nums.begin(), nums.end());
		int low = 0;
		int high = nums.size() - 1;
		for (; low < high - 1; ++low)
		{
			for (; high > low + 1; --high)
			{
				int sum = nums[low] + nums[high];
				for (int i = low + 1; i < high; ++i)
				{
					if (nums[i] + sum == 0)
					{
						path.push_back(nums[low]);
						path.push_back(nums[i]);
						path.push_back(nums[high]);
						result.push_back(path);
						path.clear();
					}
					while (nums[i + 1] == nums[i])
						++i;
				}
				while (nums[high - 1] == nums[high])
					--high;
			}
			high = nums.size() - 1;
			while (nums[low + 1] == nums[low])
				++low;
		}
		return result;
    }
};

// LeetCode, 3Sum
// 先排序，然后左右夹逼，注意跳过重复的数，时间复杂度 O(n^2) 空间复杂度 O(1)
//	比上面的代码有两处优化：
// 1. 既然排过序，第三个指针可以提前减枝(不管是找到了还是没找到)
// 2. path变量是不需要的，result.push_back({ *i, *j, *k });
class Solution1
{
  public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
		vector<vector<int>> result;
		if (nums.size() < 3)
			return result;
		sort(nums.begin(), nums.end());
		const int target = 0;
		auto last = nums.end();
		for (auto i = nums.begin(); i < last - 2; ++i)
		{
			auto j = i + 1;
			if (i > nums.begin() && *i == *(i - 1))
				continue;
			auto k = last - 1;
			while (j < k)
			{
				if (*i + *j + *k < target)
				{
					++j;
					while (*j == *(j - 1) && j < k)
						++j;
				}
				else if (*i + *j + *k > target)
				{
					--k;
					while (*k == *(k + 1) && j < k)
						--k;
				}
				else
				{
					result.push_back({*i, *j, *k});
					++j;
					--k;
					while (*j == *(j - 1) && *k == *(k + 1) && j < k)
						++j;
				}
			}
		}
		return result;
    }
};

int main()
{
    Solution1 s1;
    vector<int> nums{-1, 0, 1, 2, -1, -4};
    vector<vector<int>> result = s1.threeSum(nums);
    show2DVector(result);
    return 0;
}