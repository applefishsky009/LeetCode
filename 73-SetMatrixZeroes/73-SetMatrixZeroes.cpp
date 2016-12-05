#include <vector>
#include <iostream>
#include "E:/RylModule/vector.h"
using namespace std;

class Solution
{
  public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0)
            return;
        vector<vector<int>> zerosRowAndCol = findZeros(matrix); //存储行列
        const int row = matrix.size();
        const int col = matrix[0].size();
        const int rowToZeros = zerosRowAndCol[0].size();
        const int colToZeros = zerosRowAndCol[1].size();
        //重置行
        for (int i = 1; i < rowToZeros; i++)
            for (int j = 0; j < col; j++)
                matrix[zerosRowAndCol[0][i]][j] = 0;
        //重置列
        for (int i = 0; i < row; i++)
            for (int j = 1; j < colToZeros; j++)
                matrix[i][zerosRowAndCol[1][j]] = 0;
    }

  private:
    vector<vector<int>> findZeros(const vector<vector<int>> &matrix)
    {
        const int row = matrix.size();
        const int col = matrix[0].size();
        vector<vector<int>> zerosRowAndCol(2, vector<int>(1, 0));
        zerosRowAndCol[0][0] = -1;
        zerosRowAndCol[1][0] = -1;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                if (matrix[i][j] == 0)
                {
                    if (i != zerosRowAndCol[0].back())
                        zerosRowAndCol[0].push_back(i);
                    if (j != zerosRowAndCol[1].back())
                        zerosRowAndCol[1].push_back(j);
                }
        return zerosRowAndCol;
    }
};

class Solution1
{
  public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        const size_t m = matrix.size();
        const size_t n = matrix[0].size();
        //首行首列需要单独重置，因为首行首列是其他行列的flag
        bool row_has_zero = false; //首行是否有0，
        bool col_has_zero = false; //首列是否有0，
        for (size_t i = 0; i < n; i++)
            if (matrix[0][i] == 0)
            {
                row_has_zero = true;
                break;
            }
        for (size_t i = 0; i < m; i++)
            if (matrix[i][0] == 0)
            {
                col_has_zero = true;
                break;
            }
        for (size_t i = 1; i < m; i++)
            for (size_t j = 1; j < n; j++)
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
        for (size_t i = 1; i < m; i++)
            for (size_t j = 1; j < n; j++)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;

        if (row_has_zero)
            for (size_t i = 0; i < n; i++)
                matrix[0][i] = 0;
        if (col_has_zero)
            for (size_t i = 0; i < m; i++)
                matrix[i][0] = 0;
    }
};

int main()
{
    Solution s1;
    vector<vector<int>> matrix = {{1, 2, 3, 0, 5},
                                  {0, 2, 3, 4, 5},
                                  {1, 2, 3, 4, 5},
                                  {1, 2, 3, 4, 5}};
    show2DVector(matrix);
    s1.setZeroes(matrix);
    show2DVector(matrix);
    return 0;
}