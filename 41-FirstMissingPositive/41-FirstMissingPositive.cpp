#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//O(n)时间复杂度，首先想到Hash Table，但是必然会有O(n)的空间复杂度，也不能用两个指针来简化
//考虑到原地交换，将所有的元素放在他应该在的位置，再遍历一次就得到异常元素
class Solution
{
  public:
    int firstMissingPositive(vector<int> &nums)
    {
		//桶排序
		const int n = nums.size();
		for (int i = 0; i < n; ++i)
		{
			while (nums[i] != i + 1)
			{									//判断是否需要交换
				if (nums[i] < 1 || nums[i] > n || nums[i] == nums[nums[i] - 1]) //越界以及无限交换陷阱
					break;							//注意避免无限交换陷阱[1,1]
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
		for (int i = 0; i < n; ++i)
			if (nums[i] != i + 1)
				return i + 1;
		return n + 1;
    }
};

int main()
{
    vector<int> nums{3, 4, -1, 1};
    Solution s1;
    cout << s1.firstMissingPositive(nums) << endl;
    return 0;
}