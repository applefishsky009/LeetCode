#include <vector>
#include <iostream>
using namespace std;

//重点在确定递增区间
//如果A[m] >= A[l]不能确定递增，那就把它拆分成两个条件
// 若 A[m] > A[l]则区间[l, m]一定递增
// 若 A[m] == A[l]确定不了，那就l++往下看
class Solution
{
  public:
    bool search(vector<int> &nums, int target)
    {
		if (nums.size() == 0)
			return false;
		int low = 0;
		int high = nums.size() - 1;
		while (low <= high)
		{
			int mid = low + (high - low) / 2;
			if (nums[mid] == target)
				return true;
			if (nums[low] == nums[mid])
			{ //跳过重复项
				low++;
				continue;
			}
			else if (nums[low] < nums[mid])
			{ //13111找3
				if (target > nums[mid] || target < nums[low])
				{ //出现问题
					low = mid + 1;
					continue;
				}
				if (nums[mid] < target && nums[high] >= target)
				{
					low = mid + 1;
					continue;
				}
			}
			else if (nums[low] > nums[mid])
			{
				if (target > nums[mid] && target <= nums[high])
				{
					low = mid + 1;
					continue;
				}
			}
			high = mid - 1;
		}
		return false;
    }
};

int main()
{
    vector<int> nums = {1, 3, 1, 1, 1};
    int target = 1;
    Solution s1;
    cout << s1.search(nums, target) << endl;
    return 0;
}
