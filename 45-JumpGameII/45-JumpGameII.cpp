#include <vector>
#include <iostream>
using namespace std;

//每一步骤选择当前最优解
class Solution
{
  public:
    int jump(vector<int> &nums)
    {
		int step = 0;
		int left = 0;
		int right = 0;
		if (nums.size() == 1)
			return 0;
		while (left <= right) //向下走一步
		{
			step++;
			const int old_right = right; //保存上一步
			for (int i = left; i <= old_right; ++i)
			{
				int new_right = i + nums[i]; //用一个变量优化代码，否则后边计算两次
				if (new_right >= nums.size() - 1)
					return step;
				if (new_right > right)
					right = i + nums[i]; //找当前步的最优解
			}
			left = old_right + 1; //下一个left不必从最优解对应的i找起来，因为找最优解的时候[i,old_right]之间已经遍历过
		}
		return -1;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << s1.jump(nums) << endl;
    return 0;
}