#include <vector>
#include <iostream>
using namespace std;

//http://blog.csdn.net/guoziqing506/article/details/51692043
//分情况断开圆环(哪一个确定不打劫就从哪里断开)的HouseRobber:record[i] = max(record[i - 1], record[i - 2] + A[i])
class Solution
{
  public:
    int rob(const vector<int> &nums)
    {
        if (0 == nums.size())
            return 0;                                             //因为会用到nums[0]，所以需要先判断一次边界条件
        int notRob1 = rob(nums, 1, nums.size());                  //不抢劫第一个，断开环
        int notRobLast = nums[0] + rob(nums, 2, nums.size() - 1); //抢劫第一个，断开环
        return max(notRob1, notRobLast);
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