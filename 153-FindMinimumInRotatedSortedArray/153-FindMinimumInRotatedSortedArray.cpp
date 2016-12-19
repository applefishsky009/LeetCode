#include <vector>
#include <iostream>
using namespace std;

//Squeeze
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
        int mid = low + (high - low) / 2;
        if (nums[mid] > nums[high]) //nums[mid] definitely is not the min
            return findMin(nums, mid + 1, high);
        else if (nums[mid] < nums[low]) //nums[low] definitely is not the min
            return findMin(nums, low + 1, mid);
        else //convergence
            return nums[low];
    }
};

//Iteration
class Soluiton1
{
  public:
    int findMin(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            if (nums[left] < nums[right])
                return nums[left];
            int mid = (left + right) / 2;
            if (nums[mid] > nums[right])
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    cout << s1.findMin(nums) << endl;
    return 0;
}