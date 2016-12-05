#include <vector>
#include <iostream>
using namespace std;

class Solution
{
  public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
		if (matrix.size() == 0)
			return false;
		const int m = matrix.size();	 //行
		const int n = matrix.front().size(); //列
		int left = 0;
		int right = m * n - 1;
		int mid = 0;
		while (left <= right)
		{
			int row = right / n;
			int col = right % n;
			if (matrix[row][col] > target)
				right = row * n + col - 1;
			else if (matrix[row][col] < target)
				left = row * n + col + 1;
			else if (matrix[row][col] == target)
				return true;
		}
		return false;
    }
};

int main()
{
    const int target = 3;
    vector<vector<int>> matrix = 
		{{1, 3, 5, 7}, 
		 {10, 11, 16, 20}, 
		 {23, 30, 34, 50}};
    Solution s1;
    cout << s1.searchMatrix(matrix, target) << endl;
    return 0;
}