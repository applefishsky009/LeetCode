#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<int> result;
        const int n = matrix.size(); //行
        if (n == 0)
            return result;
        const int m = matrix[0].size(); //列
        printMatrix(result, matrix, 0, 0, m, n);
        return result;
    }

  private:
    void printMatrix(vector<int> &result, const vector<vector<int>> matrix, int startX, int startY, int m, int n)
    {
        if (m <= 0 || n <= 0)
            return;         //递归出口
        if (n > 0 && m > 0) //向右打印
            for (int i = startY; i < startY + m; ++i)
                result.push_back(matrix[startX][i]);
        if (n > 1) //向下打印
            for (int i = startX + 1; i < startX + n; ++i)
                result.push_back(matrix[i][startY + m - 1]);
        if (n > 1 && m > 1) //向左打印，保证不和向右重复
            for (int i = startY + m - 2; i >= startY; --i)
                result.push_back(matrix[startX + n - 1][i]);
        if (n > 2 && m > 1) //向上打印，保证不和向下重复
            for (int i = startX + n - 2; i > startX; --i)
                result.push_back(matrix[i][startY]);
        printMatrix(result, matrix, startX + 1, startY + 1, m - 2, n - 2);
    }
};

int main()
{
    // vector<vector<int>> matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // vector<vector<int>> matrix{{7}, {9}, {6}};
    // vector<vector<int>> matrix{{1, 3, 4}};
    // vector<vector<int>> matrix{{1, 2, 3}, {4, 5, 6}};
    // vector<vector<int>> matrix{{2, 3}, {5, 6}};
    vector<vector<int>> matrix{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}};
    Solution s1;
    vector<int> result = s1.spiralOrder(matrix);
    show1DVector(result);
    return 0;
}
