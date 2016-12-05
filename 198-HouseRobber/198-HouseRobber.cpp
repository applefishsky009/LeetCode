#include <vector>
#include <iostream>
using namespace std;

//http://blog.csdn.net/guoziqing506/article/details/51690021
//record[i] = max(record[i - 1], record[i - 2] + A[i])
class Solution
{
  public:
    int rob(const vector<int> &nums)
    {
        return rob(nums, 0, nums.size());
    }

  private:
    int rob(const vector<int> &nums, int start, int end)
    { //start是起始index，end是超尾
        if (end <= start)
            return 0;
        if (end == start + 1)
            return nums[start];
        if (end == start + 2)
            return max(nums[start], nums[start + 1]);
        vector<int> valRob(end - start, 0); //start在nums中作为偏移量才能对应valRob
        valRob[0] = nums[start];
        valRob[1] = nums[start + 1] > nums[start] ? nums[start + 1] : nums[start];
        for (int i = 2; i < end - start; ++i)
            valRob[i] = valRob[i - 2] + nums[start + i] > valRob[i - 1] ? valRob[i - 2] + nums[start + i] : valRob[i - 1];
        return valRob[end - start - 1];
    }
};

int main()
{
    Solution s1;
    vector<int> nums{3, 6, 4, 8};
    cout << s1.rob(nums) << endl;
    return 0;
}