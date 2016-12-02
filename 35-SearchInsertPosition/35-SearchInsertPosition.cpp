#include <vector>
#include <iostream>
using namespace std;

//排好序的用二分查找
class Solution
{
  public:
    int searchInsert(vector<int> &nums, int target)
    {
		if (target < nums[0])
			return 0;
		if (target > nums[nums.size() - 1])
			return nums.size();				     //检查是否在序列内
		return biSearchInsert(nums, target, 0, nums.size()); //序列内二分查找
    }

  private:
    int biSearchInsert(vector<int> &nums, int target, int low, int high)
    {
		if (low > high) //二分查找越界了
			return -1;
		int mid = low + (high - low) / 2; //防止溢出
		if (nums[mid] == target)	  //找到目标
			return mid;
		else if (nums[mid] < target && nums[mid + 1] > target) //没有目标，这是插入位置，若没有这一句就是标准二分查找
			return mid + 1;
		else if (nums[mid] < target)
			return biSearchInsert(nums, target, mid + 1, high);
		else
			return biSearchInsert(nums, target, low, mid - 1);
    }
};

//顺序遍历
class Solution1
{
  public:
    int searchInsert(vector<int> &nums, int target)
    {
		for (int i = 0; i < nums.size(); i++)
			if (nums[i] >= target)
				return i;
		return nums.size();
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {1, 3, 5, 6};
    int target = 7;
    cout << s1.searchInsert(nums, target) << endl;
    return 0;
}