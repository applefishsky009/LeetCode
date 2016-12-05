#include <vector>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//二进制加法原理
class Solution
{
  public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
			sort(nums.begin(), nums.end());
			vector<vector<int>> result;
			vector<int> v;
			for (int i = 0; i < 1 << nums.size(); i++) //子数组一共 1<<nums.size()个，采用二进制逐个选择
			{
				for (int j = 0; j < nums.size(); j++) //判断每一位要不要选择
				if (i & 1 << j)
					v.push_back(nums[j]); //i&1<<j 可以判断二进制中j位到底有没有
				result.push_back(v);
				v.clear();
			}
			return result;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = s1.subsets(nums); //结果按照二进制排序
    show2DVector(result);
    return 0;
}