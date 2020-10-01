#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// DP - 状态转移 - 标识状态 - 类似于股票题
// 状态0和2表示前面和后面的红色部分, 状态1表示黄色部分
// f[i][j]表示对第0-i片叶子进行操作, 并且第i片叶子处于状态j时的最小操作次数
// j = 0, 需要将第i片叶子变成红色, 并且第i - 1片叶子也只能处于j = 0的状态(没有编号更小的状态了)
// f[i][0] = f[i - 1][0] + isYellow(i); isYellow(i)当第i片叶子为黄色时为1, 红色时为0
// j = 1, 需要将i片叶子变成黄色, 而第i - 1片叶子既可以处于j = 1的状态也可以处于j = 0的状态
// f[i][1] = min(f[i - 1][0], f[i - 1][1]) + isRed(i); isRed(i)当第i片叶子为红色时为1, 黄色时为0
// j = 2, 需要将第i片叶子变成红色, 而第i - 1片叶子既可以处于j = 2的状态, 也可以处于j = 1的状态(不能处于j = 0的状态, 因为每一种状态包含的叶子数量至少为1)
// f[i][2] = min(f[i - 1][1], f[i - 1][2]) + isYellow(i); isYellow(i)当第i片叶子为黄色时为1, 红色时为0
// j = 2时叶子数量必须大于等于状态数量, f[0][0] = isYellow(0);表示第0个是红色则为0
// time: O(n)
// space: O(n)
class Solution0 {
  public:
    int minimumOperations(string leaves) {
        int n = leaves.size();
        vector<vector<int>> idp(n, vector<int>(3));
        idp[0][0] = (leaves[0] == 'y');   // 初始状态
        idp[0][1] = idp[0][2] = idp[1][2] = INT_MAX;  // 非法状态
        for (int i = 1; i < n; ++i) {
            int isRed = (leaves[i] == 'r');
            int isYellow = (leaves[i] == 'y');
            idp[i][0] = idp[i - 1][0] + isYellow;
            idp[i][1] = min(idp[i - 1][0], idp[i - 1][1]) + isRed;
            if (i >= 2)
                idp[i][2] = min(idp[i - 1][1], idp[i - 1][2]) + isYellow;
        }
        return idp[n - 1][2];
    }
};

// DP - 前缀和 + 状态转移
// 将leaves[0...x], leaves[x + 1...y], leaves[y + 1...n - 1]分别作为每一部分, 那么需要的操作为
// ∑_0¯x isYellow(i) + ∑_x+1¯y isRed(i) + ∑_y+1¯n-1 isYellow(i)
// 枚举x和y, 使用前缀和的思路快速计算出上面的三项累加和, 时间复杂度为O(n^2)
// 枚举一个位置(例如y)并找出让上述累加和达到最小值的x, preR表示isRed的前缀和, preY表示isYellow的前缀和, 枚举y时考虑这三项:
// 第一项即为 preY(x);
// 第二项即为 preR(y) - preR(x);
// 第三项即为 preY(n - 1) - preY(y);
// 即 preY(n - 1) + (preY(x) - preR(x)) + (preR(y) - preY(y))
// 其中preY(n - 1)是固定值, (preY(x) - preR(x))和y无关, (preR(y) - preY(y))和y相关
// 因此只需要预处理preR和preY即可, 另外preY(i) + preR(i) = i + 1恒成立
// preY(x) - preR(x) = preY(x) - (x + 1 - preY(x)) = 2 * preY(x) - (x + 1)
// 令g(x) = 2 * preY(x) - (x + 1), 累加和为 preY(n - 1) + g(x) - g(y)
// g(x + 1) - g(x) = (2 * preY(x + 1) - (x + 2)) - (2 * preY(x) - (x + 1))
// = 2 * (preY(x + 1) - preY(x)) - 1 = 2 * isYellow(x + 1) - 1; 即为g的递推式
// 我们只需要在枚举y的时候同时计算g即可, 并且preY(n - 1)这一常数项留在最后累加
// preY(n - 1) = (g(n - 1) + n) / 2
// time: O(n)
// space: O(1)
class Solution {
  public:
    int minimumOperations(string leaves) {
        int n = leaves.size();
        int g = (leaves[0] == 'y' ? 1 : -1);
        int gmin = g;   // gx
        int ans = INT_MAX;
        for (int i = 1; i < n; ++i) {   // 对y进行枚举
            int isYellow = (leaves[i] == 'y');
            g += 2 * isYellow - 1;  // g的递推式
            if (i != n - 1)
                ans = min(ans, gmin - g);   // 累加和递推式 g(x) - g(y)
            gmin = min(gmin, g);    // 记录x的值
        }
        return ans + (g + n) / 2;   // 累加和
    }
};

int main() {
    Solution s;
    string leaves = "rrryyyrryyyrr";
    cout << s.minimumOperations(leaves) << endl;
    return 0;
}