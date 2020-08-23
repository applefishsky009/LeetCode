#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

// Bit
// 假设二进制的前i位均相同, 第i + 1位开始不同, 由于m, n连续, 那么第i+1位在[m, n]范围内一定是前面全是0, 后面全是1
// 并且一定存在连续的两个数x和x + 1, 满足x的第i + 1位为0, 后面全为1, x + 1的第i + 1位为1, 后面全为0,
// 问题转化为给定两个数字, 找到他们对应的二进制字符串的公共前缀
// time: O(lgn)
// space: O(1)
class Solution0 {
  public:
    int rangeBitwiseAnd(int m, int n) {
        int ishift = 0;
        while (m < n) {    // 找公共前缀
            m >>= 1;
            n >>= 1;
            ++ishift;
        }
        return m << ishift;
    }
};

// Brian Kernighan - 清除二进制串中最右边的1
// 假设二进制的前i位均相同, 第i + 1位开始不同, 由于m, n连续, 那么第i+1位在[m, n]范围内一定是前面全是0, 后面全是1
// 并且一定存在连续的两个数x和x + 1, 满足x的第i + 1位为0, 后面全为1, x + 1的第i + 1位为1, 后面全为0,
// 问题转化为给定两个数字, 找到他们对应的二进制字符串的公共前缀
// time: O(lgn)
// space: O(1)
class Solution {
  public:
    int rangeBitwiseAnd(int m, int n) {
        while (m < n)       // 找公共前缀
            n = n & (n - 1);    // 抹去最右边的1, n & (n - 1) == 0可以判断是否为2的幂
        return n;
    }
};

int main() {
    Solution s;
    cout << s.rangeBitwiseAnd(5, 7) << endl;
    return 0;
}