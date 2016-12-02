#include <vector>
#include <iostream>
using namespace std;

//二分查找注意区间的开闭
class Solution
{
  public:
    int search(const vector<int> &nums, int target)
    {
		return biSearch(nums, target, 0, nums.size() - 1);
    }

  private:
    int biSearch(const vector<int> &nums, int target, int low, int high)
    {
		if (low > high)
			return -1;
		int mid = low + (high - low) / 2;
		if (nums[mid] == target)
			return mid;
		if (nums[low] == target)
			return low;
		if (nums[high] == target)
			return high;
		if ((nums[mid] < nums[low] && (nums[mid] < target && target < nums[high]))   //4 5 1 2 3		找2
			|| (nums[mid] > nums[low] && (nums[mid] < target || target < nums[low])) // 4 5 6 1 2	找1
			|| (nums[mid] < target && target < nums[high]))			     //4 5 6	找5
		{
			return biSearch(nums, target, mid + 1, high - 1);
		}
		else
			return biSearch(nums, target, low + 1, mid - 1);
    }
};

class Solution1
{
  public:
    int search(const vector<int> &nums, int target)
    {
		return biSearch(nums, target, 0, nums.size() - 1);
    }

  private:
    int biSearch(const vector<int> &nums, int target, int low, int high)
    {
		if (low > high)
			return -1;
		int mid = low + (high - low) / 2;
		if (nums[mid] == target)
			return mid;
		//前两个条件左侧判断pivkey的位置不要进行区间划分 && 右侧划区间，左闭右开
		if ((nums[mid] < nums[low] && (nums[mid] < target && target <= nums[high]))   //4 5 1 2 3		找2		pivkey右侧
			|| (nums[mid] >= nums[low] && (nums[mid] < target || target < nums[low])) // 4 5 6 1 2	找1		pivkey左侧
			|| (nums[mid] < target && target <= nums[high]))			      //4 5 6	找5		没有pivkey
		{
			return biSearch(nums, target, mid + 1, high);
		}
		else
			return biSearch(nums, target, low, mid - 1);
    }
};

int main()
{
    vector<int> nums = {10, 5, 1, 2, 3, 4};
    int target = 1;
    Solution1 s1;
    cout << s1.search(nums, target) << endl;
    return 0;
}