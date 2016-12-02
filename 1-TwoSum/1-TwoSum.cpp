#include <vector>
#include <unordered_map>
#include <E:\RylModule\vector.h>
using namespace std;

//考虑使用unordered_map，常数级查找
class Solution
{
  public:
    vector<int> twoSum(vector<int> &nums, int target)
	{
		vector<int> result;
		unordered_map<int, int> numMap;
		for (int i = 0; i < nums.size(); ++i)
	    	numMap[nums[i]] = i;
		for (int i = 0; i < nums.size(); ++i)
		{ //考虑{3,2,4,(3)},6；因此不能对半筛选
		    if (numMap.find(target - nums[i]) != numMap.end())
		    {
				if (i == numMap[target - nums[i]])
		    		continue; //考虑{0，1，3，0}，0
				result.push_back(i);
				result.push_back(numMap[target - nums[i]]);
				break;
	    	}
		}
		return result;
	}
};

int main()
{
    Solution s1;
    vector<int> nums{3, 2, 4};
    int target = 6;
    vector<int> result = s1.twoSum(nums, target);
    show1DVector(result);
    return 0;
}