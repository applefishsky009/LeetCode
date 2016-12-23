#include <vector>
#include <iostream>
using namespace std;

//ith element is ralated to previous tew elements.
class Solution
{
  public:
    int findPeakElement(vector<int> &nums)
    {
        bool preLow = true; //flag
        const int n = nums.size();
        for (int i = 0; i < n - 1; i++)
        {
            if (nums[i + 1] < nums[i])
            {
                if (preLow)
                    return i;
                preLow = false;
            }
            else
                preLow = true;
        }
        return n - 1;
    }
};

//Binary Search
class Solution1
{
  public:
    int findPeakElement(vector<int> &nums)
    {
        int low = 0;
        int high = nums.size();
        //[) have a convergence problem, the value will converge to high when low = high - 1 no matter the target is low or high.
        while (low < high)
        {
            int mid = low + (high - low) / 2;
            if ((mid == 0 || nums[mid - 1] < nums[mid]) && (nums[mid] > nums[mid + 1] || mid == nums.size() - 1))
                return mid;
            else if (nums[mid - 1] > nums[mid])
                high = mid;
            else
                low = mid + 1;
        }
        return low;
    }
};

class Solution2
{
  public:
    int findPeakElement(const vector<int> &num)
    {
        int low = 0, high = num.size() - 1;
        //[] prevent the convergence problem. but you should justify which one is your target, low or high ?
        while (low < high - 1)
        {
            int mid = (low + high) / 2;
            if (num[mid] > num[mid - 1] && num[mid] > num[mid + 1])
                return mid;
            else if (num[mid] > num[mid + 1])
                high = mid - 1;
            else
                low = mid + 1;
        }
        return num[low] > num[high] ? low : high;
    }
};

int main()
{
    vector<int> nums = {1};
    Solution1 s1;
    cout << s1.findPeakElement(nums) << endl;
    return 0;
}