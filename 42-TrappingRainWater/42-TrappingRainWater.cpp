#include <vector>
#include <iostream>
using namespace std;

//对于每个柱子，找到其左右两边最高的柱子，该柱子能容纳的面积就是min(max_left,max_right) - height'，所以
//1. 从左向右扫描一遍，对于每个柱子，求取左边的最大值；
//2. 从右向左扫描一遍，对于每个柱子，求最大右值；
//3. 再扫描一遍，把每个柱子的面积累加。
class Solution
{
  public:
    int trap(vector<int> &height)
    {
        vector<int> leftMax(height.size(), 0);
        vector<int> rightMax(height.size(), 0);

        for (int i = 1; i < height.size(); i++)
            leftMax[i] = max(leftMax[i - 1], height[i - 1]);

        for (int i = height.size() - 2; i >= 0; i--)
            rightMax[i] = max(rightMax[i + 1], height[i + 1]);

        int rainWater = 0;
        for (int i = 0; i < height.size(); i++)
        {
            int lowerBuck = min(leftMax[i], rightMax[i]);
            if (height[i] < lowerBuck)
                rainWater += lowerBuck - height[i];
        }
        return rainWater;
    }
};

int main()
{
    vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    Solution s1;
    cout << s1.trap(height) << endl;
    return 0;
}