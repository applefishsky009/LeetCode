#include <vector>
#include <iostream>
using namespace std;

// 假设dp[x]为她手上牌面为x时，能获胜的概率，那么这个概率应该是：dp[x] = 1/w * (dp[x+1] + dp[x+2] + dp[x+3]... + dp[x+w])
// https://leetcode-cn.com/problems/new-21-game/solution/huan-you-bi-zhe-geng-jian-dan-de-ti-jie-ma-tian-ge/
class Solution {
  public:
    double new21Game(int N, int K, int W) {
        int i = 0;
        double posib = 1.0 / W, sum = 0;
        vector<double> dp(K + W, 0);
        for (i = K; i < K + W; i++) {   // 初始状态
            dp[i] = (i <= N ? 1 : 0);   // 不超过N获胜
            sum += dp[i];
        }
        for (i = K - 1; i >= 0; i--) {  // 递归公式
            dp[i] = sum * posib;
            sum += (dp[i] - dp[i + W]);
        }
        return dp[0];
    }
};

int main() {
    Solution s1;
    cout << s1.new21Game(10, 1, 10) << endl;
    cout << s1.new21Game(6, 1, 10) << endl;
    cout << s1.new21Game(21, 17, 10) << endl;
    return 1;
}