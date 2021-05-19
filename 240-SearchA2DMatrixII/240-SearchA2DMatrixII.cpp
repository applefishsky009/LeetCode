#include <vector>
#include <iostream>
using namespace std;


// https://blog.csdn.net/weixin_43314519/article/details/107828040
// BS, BST
// time: O(mlgn), 如果m >> n, 二分的优化差别较大，因此对角线迭代或选择min(m,n)的维度迭代可以解决这个问题
// space: O(1)
class Solution {
  public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int i = 0, m = matrix.size(), n = matrix[0].size();
        for (i = 0; i < m; ++i)
            if (mBinarySearch(matrix[i], 0, n - 1, target)) // 注意是左闭右闭区间
                return true;
        return false;
    }
  private:
    bool mBinarySearch(vector<int> &ivector, int start, int end, int target) {
        while (end >= start) {
            int mid = start + ((end - start) >> 1);
            if (ivector[mid] == target) {
                return true;
            } else if (ivector[mid] > target) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    // vector<vector<int>> matrix = {
    //     {1, 4, 7, 11, 15},
    //     {2, 5, 8, 12, 19},
    //     {3, 6, 9, 16, 22},
    //     {10, 13, 14, 17, 24},
    //     {18, 21, 23, 26, 30},
    // };
    // cout << s.searchMatrix(matrix, 5) << endl;
    vector<vector<int>> matrix = {
        {-5},
    };
    cout << s.searchMatrix(matrix, -2) << endl;
    return 0;
}