#include <cmath>
#include <iostream>
using namespace std;

// 等差数列
// k * (k + 1) / 2 = n的根取整
// time: O(1)
// space: O(1)
class Solution0 {
  public:
    int arrangeCoins(int n) {
        return (int)(sqrt(1.0 + (double)8 * n) - 1) >> 1;
    }
};

// BS
// time: O(lgn)
// space: O(1)
class Solution {
  public:
    int arrangeCoins(int n) {
        int l = 0, r = n;
        while (l < r) {
            long long mid = ((r - l) >> 1) + l + 1; // mid行, + 1表示将mid ceil到r, 通过r = mid - 1的r收敛到l
            long long cost = ((mid + 1) * mid) >> 1;    // 填满1-mid行所需要的硬币
            if (cost == n) return int(mid); // 刚好填满mid行, 返回mid, 二分提前剪枝
            else if (cost > n) r = (int)mid - 1;    // 填不满mid行, 返回值为[1, mid - 1]
            else l = (int)mid;  // 填满mid行还多, 返回值为[mid, n]
        }
        return r;
    }
};

int main() {
    Solution s;
    cout << s.arrangeCoins(5) << endl;  // 2
    cout << s.arrangeCoins(8) << endl;  // 3
    return 0;
}