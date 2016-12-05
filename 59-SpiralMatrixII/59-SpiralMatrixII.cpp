#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

//自己的代码，递归，缩窄矩阵
class Solution
{
  public:
    vector<vector<int>> generateMatrix(int n)
    {
        vector<vector<int>> result(n, vector<int>(n, 0));
        spiralMatrix(result, 0, 0, n);
        return result;
    }

  private:
    void spiralMatrix(vector<vector<int>> &result, int pre, int start, int n)
    {
        if (n <= 0)
            return;
        for (int i = start; i < start + n; ++i)
            result[start][i] = ++pre;
        for (int i = start + 1; i < start + n; ++i)
            result[i][start + n - 1] = ++pre;
        for (int i = start + n - 2; i >= start; --i)
            result[start + n - 1][i] = ++pre;
        for (int i = start + n - 2; i > start; --i)
            result[i][start] = ++pre;
        spiralMatrix(result, pre, start + 1, n - 2);
    }
};

//非递归版本
class Solution1
{
  public:
    vector<vector<int>> generateMatrix(int n)
    {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int begin = 0, end = n - 1;
        int num = 1;
        while (begin < end)
        {
            for (int j = begin; j < end; ++j)
                matrix[begin][j] = num++;
            for (int i = begin; i < end; ++i)
                matrix[i][end] = num++;
            for (int j = end; j > begin; --j)
                matrix[end][j] = num++;
            for (int i = end; i > begin; --i)
                matrix[i][begin] = num++;
            ++begin;
            --end;
        }
        if (begin == end)
            matrix[begin][begin] = num;
        return matrix;
    }
};

//行列分离的非递归版本
class Solution2
{
  public:
    vector<vector<int>> generateMatrix(int n)
    {
        vector<vector<int>> matrix(n, vector<int>(n));
        if (n == 0)
            return matrix;
        int beginX = 0, endX = n - 1;
        int beginY = 0, endY = n - 1;
        int num = 1;
        while (true)
        {
            for (int j = beginX; j <= endX; ++j)
                matrix[beginY][j] = num++;
            if (++beginY > endY)
                break;
            for (int i = beginY; i <= endY; ++i)
                matrix[i][endX] = num++;
            if (beginX > --endX)
                break;
            for (int j = endX; j >= beginX; --j)
                matrix[endY][j] = num++;
            if (beginY > --endY)
                break;
            for (int i = endY; i >= beginY; --i)
                matrix[i][beginX] = num++;
            if (++beginX > endX)
                break;
        }
        return matrix;
    }
};

int main()
{
    Solution s1;
    int n = 5;
    vector<vector<int>> result = s1.generateMatrix(n);
    show2DVector(result);
    return 0;
}