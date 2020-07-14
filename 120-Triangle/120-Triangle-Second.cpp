#include <cmath>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// inplace dp
// f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j]
// f[0][0] = triangle[0][0]
// time: O(n^2)
// space: O(1)
class Solution1 {
  public:
    int minimumTotal(vector<vector<int>>& triangle) {
        for (int i = triangle.size() - 2; i >= 0; --i)
            for (int j = triangle[i].size() - 1; j >= 0; --j)
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
        return triangle[0][0];
    }
};

// dp - 滚动数组 - 带备忘
// time: O(n^2)
// space: O(n)
class Solution2 {
  public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        int nlen = triangle.size();
        vector<int> idp(nlen);
        idp[0] = triangle[0][0];
        for (int i = 1; i < nlen; ++i) {
            idp[i] = idp[i - 1] + triangle[i][i];   // 对角线元素赋值
            for (int j = i - 1; j > 0; --j)      // 必须从后往前, 否则不满足无后效性
                idp[j] = min(idp[j] , idp[j - 1]) + triangle[i][j];
            idp[0] += triangle[i][0];   // 第一个元素赋值
        }
        return *min_element(idp.begin(), idp.end());
    }
};

// dp - 滚动数组 - 带备忘
// f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j], 可以观察到j和j - 1状态相关,因为滚动数组必须先计算j再计算j-1
// f[0][0] = triangle[0][0]
// time: O(n^2)
// space: O(n)
class Solution {
  public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        int nlen = triangle.size();
        vector<int> idp(nlen + 1, INT_MAX);
        idp[1] = triangle[0][0];
        for (int i = 1; i < nlen; ++i)
            for (int j = i + 1; j > 0; --j) // 无后效性 - 为了处理边界条件, 数组前塞INT_MAX
                idp[j] = min(idp[j] , idp[j - 1]) + triangle[i][j - 1]; // idp的j对应triangle的j - 1
        return *min_element(idp.begin(), idp.end());
    }
};

int main() {
  Solution s;
  vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
  cout << s.minimumTotal(triangle) << endl;
  return 0;
}