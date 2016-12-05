#include <vector>
#include <iostream>
using namespace std;
//
//动态规划:
//子问题的状态转移方程
//如何保存解
class Solution
{
  public:
    int minimumTotal(vector<vector<int>> &triangle)
    {						       //从(i,j)开始
		for (int i = triangle.size() - 2; i >= 0; --i) //行遍历
			for (int j = 0; j <= i; ++j)	       //列遍历
				triangle[i][j] += triangle[i + 1][j] < triangle[i + 1][j + 1] ? triangle[i + 1][j] : triangle[i + 1][j + 1];
		return triangle[0][0];
    }
};

int main()
{
    vector<vector<int>> vectorIn =
		{{2, 0, 0, 0},
		{3, 4, 0, 0},
		{6, 5, 7, 0},
		{4, 1, 8, 3}};
    Solution s1;
    cout << s1.minimumTotal(vectorIn) << endl;
    return 0;
}