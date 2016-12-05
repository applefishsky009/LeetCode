#include <vector>
#include <E:\RylModule\vector.h>
using namespace std;

//左上与右上元素和
//也可以每次给path最后加一个1，更新两个1中间的数字，省略一些clear()和push()方法。
class Solution
{
  public:
    vector<vector<int>> generate(int numRows)
    {
		vector<vector<int>> result;
		if (numRows == 0)
			return result;
		vector<int> path(1, 1); //fill constructor
		result.push_back(path);
		for (int i = 2; i <= numRows; ++i)
		{
			path.clear();
			path.push_back(1);
			for (int j = 1; j < i - 1; ++j)
				path.push_back(result.back()[j - 1] + result.back()[j]);
			path.push_back(1);
			result.push_back(path);
		}
		return result;
    }
};

int main()
{
    Solution s1;
    int numRows = 5;
    vector<vector<int>> result = s1.generate(numRows);
	show2DVector(result);
    return 0;
}