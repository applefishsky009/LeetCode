#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// dp, 无论dungeon[i][j]为正为负, 都表示转移到这里所付出的代价
// time: O(N * M)
// space: O(N * M)
class Solution1 {
  public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size();
        if (n == 0) return 1;
        int m = dungeon[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));   // dp[i]表示走到这一步所需要的最小生命值
        dp[n][m - 1] = dp[n - 1][m] = 1;    // 走过终点后HP为1
        for (int i = n - 1; i >= 0; --i)
            for (int j = m - 1; j >= 0; --j)
                dp[i][j] = max(min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j], 1); // 最小HP初始值, 负数无效截断
        return dp[0][0];
    }
};

// dp, 无论dungeon[i][j]为正为负, 都表示转移到这里所付出的代价
// 滚动数组优化
// time: O(N * M)
// space: O(N * M)
class Solution {
  public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size();
        if (n == 0) return 1;
        int m = dungeon[0].size();
        vector<int> dp(m + 1, INT_MAX);   // dp[i]表示走到这一步所需要的最小生命值
        dp[m - 1] = 1;  // 走过终点后HP为1, bottom
        for (int i = n - 1; i >= 0; --i)
            for (int j = m - 1; j >= 0; --j)
                dp[j] = max(min(dp[j], dp[j + 1]) - dungeon[i][j], 1); // 最小HP初始值, 负数无效截断
        return dp[0];
    }
};

// dp带备忘的自顶向下法和自底向上法是等价的, 递归和迭代的区别, 区别在于不同的问题使用不同方法更简单, 如何判断选择什么方法更简单呢?
// 个人认为主要在于待求解状态和现有明确状态的位置关系, 从明确状态转移到待求解状态总是最简洁的方式而不论自顶向下和自底向上.
// 而状态转移的重点总是要明确所属状态的种类以及转移条件!!!

int main() {
    Solution s;
    vector<vector<int>> dungeon = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
    cout << s.calculateMinimumHP(dungeon) << endl;
    return 0;
}