#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int singleNumber(vector<int> &nums)
    {
        assert(nums.size() != 0);
        int single = 0;
        for (auto x : nums)
            single ^= x;
        return single;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 123};
    cout << s1.singleNumber(nums) << endl;
    return 0;
}