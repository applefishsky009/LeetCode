#include <iostream>
using namespace std;

// 移位
// time: O(1)
// space: O(1)
class Solution0 {
  public:
    int hammingDistance(int x, int y) {
        int ixor = x ^ y, ans = 0;
        while (ixor != 0) {
            ans += (ixor & 1);
            ixor >>= 1;
        }
        return ans;
    }
};

// Brian Kernighan Algorithm 布莱恩克尼根算法
// 其实就是利用LowBit计算, 跳过了移位中的0
// time: O(1)
// space: O(1)
class Solution {
  public:
    int hammingDistance(int x, int y) {
        int ixor = x ^ y, ans = 0;
        while (ixor) {
            ++ans;
            ixor &= (ixor - 1);
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.hammingDistance(1, 4) << endl;
    return 0;
}