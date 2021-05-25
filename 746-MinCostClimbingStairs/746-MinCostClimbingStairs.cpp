#include <vector>
#include <iostream>
using namespace std;

// DP 可以使用滚动数组进一步优化代码
// time: O(n)
// space: O(n)
class Solution {
  public:
    int minCostClimbingStairs(vector<int> &cost) {
        int i = 0;
        vector<int> idp(cost.size() + 1, 0);    // 到达i所需要的努力
        for (i = 2; i < idp.size(); ++i) {
            idp[i] = min(idp[i - 1] + cost[i - 1], idp[i - 2] + cost[i - 2]);
        }
        return idp.back();
    }
};

int main() {
    Solution s;
    vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    cout << s.minCostClimbingStairs(cost) << endl;
    return 0;
}