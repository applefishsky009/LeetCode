#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution
{
  public:
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_set<int> cache;
        for (int i = 0; i < nums.size(); i++)
            if (cache.find(nums[i]) != cache.end())
                return true;
            else
                cache.insert(nums[i]);
        return false;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {1, 2, 3, 4, 5, 67, 8, 54, 5};
    cout << s1.containsDuplicate(nums) << endl;
    return 0;
}