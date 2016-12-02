#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

//注意是水的容积，即计算矩形的面积，而不是梯形面积
//矩形面积取决于最短的木板
class Solution
{
  public:
    int maxArea(vector<int> &height)
    {
		int start = 0;
		int end = height.size() - 1;
		int result = INT_MIN;
		while (start < end)
		{
			int area = min(height[end], height[start]) * (end - start);
			result = max(result, area);
			//更新最短的木板，如[1,2,4,3]
			if (height[start] <= height[end])
				start++;
			else
				end--;
		}
		return result;
    }
};

int main()
{
    Solution s1;
    vector<int> height = {1, 6, 7, 8, 1};
    cout << s1.maxArea(height) << endl;
    return 0;
}