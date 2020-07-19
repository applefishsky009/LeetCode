#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// DP - 自底向上
// dp[i][j]表示填满开区间(i,j)能得到的最多硬币数,边界条件i >= j - 1(区间数为0), 此时dp[i][j] = 0
// dp[i][i] = max-k[i + 1, j - 1] val[i] * val[k] * val[j] + dp[i][k] + dp[k][j] if i < j - 1, 
// 其中k是[i + 1, j - 1]区间中第一个添加的气球或者最后一个戳破的气球, 因为左右边界确定, 变量只有一个k
// dp[i][j] = 0 if i >= j - 1
// time: O(n^3)
// space: O(n^2)
class Solution1 {
  public:
    int maxCoins(vector<int> &nums) {
        int len = nums.size();
        vector<vector<int>> idp(len + 2, vector<int>(len + 2, 0));
        vector<int> val(len + 2, 0);
        val[0] = val[len + 1] = 1;
        for (int i = 1; i < len + 1; ++i)
            val[i] = nums[i - 1];
        for (int i = len - 1; i >= 0; --i)  // idp[k][j]-自底向上
            for (int j = i + 2; j <= len + 1; ++j)  // 边界条件
                for (int k = i + 1; k < j; ++k) // 和[i, j]区间状态相关的dp, idp[i][k]-自左而右
                    idp[i][j] = max(idp[i][j], val[i] * val[k] * val[j] + idp[i][k] + idp[k][j]);
        return idp[0][len + 1];
    }
};

// DP - 带缓存的自顶向下
// dp[i][j]表示填满开区间(i,j)能得到的最多硬币数,边界条件i >= j - 1(区间数为0), 此时dp[i][j] = 0
// dp[i][i] = max-k[i + 1, j - 1] val[i] * val[k] * val[j] + dp[i][k] + dp[k][j] if i < j - 1, 
// 其中k是[i + 1, j - 1]区间中第一个添加的气球或者最后一个戳破的气球, 因为左右边界确定, 变量只有一个k
// dp[i][j] = 0 if i >= j - 1
// time: O(n^3)
// space: O(n^2)
class Solution {
  public:
    int maxCoins(vector<int> &nums) {
        int len = nums.size();
        vector<int> val(len + 2, 0);
        vector<vector<int>> idp(len + 2, vector<int>(len + 2, -1));
        val[0] = val[len + 1] = 1;
        for (int i = 1; i < len + 1; ++i)   
            val[i] = nums[i - 1];
        return solve(0, len + 1, val, idp); // 两侧补了1, 均为开区间
    }
  private:
    int solve(int left, int right, vector<int> &val, vector<vector<int>> &idp) {
        if (left >= right - 1) return 0;    // 开区间边界
        if (idp[left][right] != -1) return idp[left][right];    // 没有计算过
        for (int i = left + 1; i < right; ++i)  // 最后一个戳破
            idp[left][right] = max(idp[left][right], val[left] * val[i] * val[right] + solve(left, i, val, idp) + solve(i, right, val, idp));
        return idp[left][right];
    }
};

int main() {
    Solution s;
    vector<int> nums = {3, 1, 5, 8};
    cout << s.maxCoins(nums) << endl;
    return 0;
};
