#include <vector>
#include <iostream>
using namespace std;

//Recursion
class Solution
{
  public:
    int findMin(const vector<int> &nums)
    {
        return findMin(nums, 0, nums.size() - 1);
    }

  private:
    int findMin(const vector<int> &nums, int low, int high)
    {
        while (low < high && nums[low + 1] == nums[low]) //exclude duplicated nums
            low++;
        while (high > low && nums[high - 1] == nums[high]) //exclude duplicated nums
            high--;
        int mid = low + (high - low) / 2;
        if (nums[mid] > nums[high]) //nums[mid] definitely is not the min
            return findMin(nums, mid + 1, high);
        else if (nums[mid] < nums[low]) //nums[low] definitely is not the min
            return findMin(nums, low + 1, mid);
        else //convergence
            return nums[low];
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    cout << s1.findMin(nums) << endl;
    return 0;
}