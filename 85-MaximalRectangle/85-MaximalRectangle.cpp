#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//核心思想:计算有效直方图的面积，以本题为例
//	1 0 1 0
//	1 0 1 1
//	1 0 1 1
//L	0 0 2 0	->	0 0 2 2	->	0 0 2 2	->	0 0 2 2
//R 1 4 3 4 ->	1 4 3 4	->	1 4 3 4	->	1 4 3 4
//H	1 0 1 0	->	2 0 2 1	->	3 0 3 2	->	4 1 4 3
class Solution
{
  public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
		if (matrix.empty())
			return 0;
		const int m = matrix.size();
		const int n = matrix[0].size();
		vector<int> H(n, 0);
		vector<int> L(n, 0);
		vector<int> R(n, n);
		int ret = 0;
		for (int i = 0; i < m; ++i)
		{
			int left = 0, right = n; //Two Pointers
			// calculate L(i, j) from left to right
			for (int j = 0; j < n; ++j)
			{
				if (matrix[i][j] == '1')
				{
					++H[j];		    //直方图高度
					L[j] = max(L[j], left); //更新左边界到该行连续1的起始位置,直方图有效宽度的控制在这里
				}
				else
				{
					left = j + 1; //遇到0更新可能的头指针(j+1)
					H[j] = 0;
					L[j] = 0;
					R[j] = n; //遇到0，直方图高度0，面积为0。
				}
			}
			// calculate R(i, j) from right to left
			for (int j = n - 1; j >= 0; --j)
			{
				if (matrix[i][j] == '1')
				{
					R[j] = min(R[j], right);		  //连续1的超尾
					ret = max(ret, H[j] * (R[j] - L[j])); //遇到1计算一次面积
				}
				else
					right = j; //遇到0更新超尾
			}
		}
		return ret;
    }
};

int main()
{
    Solution s1;
    vector<vector<char>> matrix =
		{{'1', '0', '1', '0'}, 
		 {'1', '0', '1', '1'}, 
		 {'1', '0', '1', '1'}, 
		 {'1', '1', '1', '1'}};
    cout << s1.maximalRectangle(matrix) << endl;
    return 0;
}