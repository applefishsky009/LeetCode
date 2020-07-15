#include <iostream>
using namespace std;

// 要考虑5的因子分解, 比如25,125
// time: O(logn)
// space: O(1)
class Solution1 {
  public:
    int trailingZeroes(int n) {
        int count = 0;
        while (n >= 5) {
            n /= 5; // 多少个5, 多少个25, 多少个125
            count += n;
        }
        return count;
    }
};

// 递归版本
// time: O(logn)
// space: O(1)
class Solution {
  public:
    int trailingZeroes(int n) {
        if (n < 5) return 0;
        return trailingZeroes(n / 5) + n / 5;   // 多少个5, 多少个25, 多少个125
    }
};

int main() {
    Solution s;
    cout << s.trailingZeroes(3) << endl;
    cout << s.trailingZeroes(5) << endl;
    cout << s.trailingZeroes(10) << endl;
    cout << s.trailingZeroes(30) << endl;
    cout << s.trailingZeroes(125) << endl;
    return 0;
}