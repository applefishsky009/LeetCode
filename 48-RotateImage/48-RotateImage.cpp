#include <vector>
#include <cassert>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

//图像(二维矩阵)的旋转只不过是一个下标变换的过程，使用旋转的方式效率太低。
//顺时针旋转90°：[i, j] -> [j, n-i-1];    水平翻转 -> 主对角线翻转
//逆时针旋转90°：[i, j] -> [n-j-1, i];    主对角线翻转 -> 水平翻转
//简化为一个组合翻转的过程。规则如下：
/*
原坐标[i,j]
水平：[n-i-1,j];
竖直：[i,n-j-1];
主对角线：[j,i];
副对角线: [n-j-1,n-i-1]; 从上可以看出，任何三个操作都可以得到第四个操作
*/

#define IMAGE_SIZE 3

class Solution
{
  public:
    void rotate(vector<vector<int>> &matrix)
    {
        assert(IMAGE_SIZE != 0);
        //水平翻转
        for (int i = 0; i < IMAGE_SIZE / 2; i++)
            for (int j = 0; j < IMAGE_SIZE; j++)
                swap(matrix[i][j], matrix[IMAGE_SIZE - i - 1][j]);
        //主对角线翻转
        for (int i = 0; i < IMAGE_SIZE; ++i)
            for (int j = 0; j < i; ++j)
                swap(matrix[i][j], matrix[j][i]);
    }
};

int main()
{
    assert(IMAGE_SIZE != 0); //等于0直接返回了
    Solution s1;
    vector<vector<int>> matrix =
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 9}};
    s1.rotate(matrix);
    show2DVector(matrix);
    return 0;
}