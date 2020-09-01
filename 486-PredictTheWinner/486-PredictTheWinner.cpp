#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// DP
// f[i][j]表示数组剩下下标i到下标j时, 当前玩家和另一个玩家的分数之差最大值, 注意当前玩家不一定是先手
// f[i][j] = 0, i > j; f[i][i] = nums[i];
// f[i][j] = max(nums[i] - f[i + 1][j], nums[j] - f[i][j - 1]); 
// time: O(n^2)
// space: O(n)
class Solution0 {
  public:
    bool PredictTheWinner(vector<int> &nums) {
        int len = nums.size();
        auto idp = vector<vector<int>> (len, vector<int>(len, 0));
        for (int i = 0; i < len; ++i)   // 初始化
            idp[i][i] = nums[i];
        for (int i = len - 2; i >= 0; --i) // 从下到上填充上三角形
            for (int j = i + 1; j < len; ++j)   // 从左到右填充上三角形的每一行
                idp[i][j] = max(nums[i] - idp[i + 1][j], nums[j] - idp[i][j - 1]);  // 当前玩家的得分, 计算另一个玩家的分数时, 取负加值
        return idp[0][len - 1] >= 0;    // 差值DP
    }
};

// DP - 滚动数组优化
// f[i][j]表示数组剩下下标i到下标j时, 当前玩家和另一个玩家的分数之差最大值
// f[i][j] = 0, i > j; f[i][i] = nums[i];
// f[i][j] = max(nums[i] - f[i + 1][j], nums[j] - f[i][j - 1]); 
// time: O(n^2)
// space: O(n)
class Solution2 {
  public:
    bool PredictTheWinner(vector<int> &nums) {
        int len = nums.size();
        auto idp = vector<int> (len, 0);
        for (int i = 0; i < len; ++i)   // 初始化
            idp[i] = nums[i];
        for (int i = len - 2; i >= 0; --i)
            for (int j = i + 1; j < len; ++j)
                idp[j] = max(nums[i] - idp[j], nums[j] - idp[j - 1]);   // 这里只是将idp的i拍平了, 其他地方都没有变
        return idp[len - 1] >= 0;
    }
};

// DFS - 二叉树 - 重复计算
// time: O(2^n)
// space: O(n)
class Solution {
  public:
    bool PredictTheWinner(vector<int> &nums) {
        return total(nums, 0, nums.size() - 1, 1) >= 0; // 先手为正, 后手为负
    }
  private:
    int total(vector<int> &nums, int start, int end, int turn) {
        if (start == end)
            return nums[start] * turn;
        int scoreStart = nums[start] * turn + total(nums, start + 1, end, -turn);   // turn分辨先手后手
        int scoreEnd = nums[end] * turn + total(nums, start, end - 1, -turn);
        return max(scoreStart * turn, scoreEnd * turn) * turn;  // 用正负表示先后手分数时, 优化目标是最大化先手, 最小化后手. 最小化后手等效为最大化后手的负值
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {1, 5, 2};  // 0
    vector<int> nums1 = {1, 5, 233, 7}; // 1
    cout << s.PredictTheWinner(nums0) << endl;
    cout << s.PredictTheWinner(nums1) << endl;
    return 0;
};