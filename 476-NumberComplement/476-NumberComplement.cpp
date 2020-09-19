#include <vector>
#include <iostream>
using namespace std;

// Bit Manipulation
// time: O(1)
// space: O(1)
// x & (-x)为lowbit, x & (x - 1)可以将最低位的1置为0.
// https://blog.csdn.net/b10221001/article/details/102118216 
// __builtin_parity(unsigned int x) 统计二进制中1个个数是偶数还是奇数	失效 ?
// __builtin_ffs(unsigned int x) 找出一个数的二进制中从末尾开始到遇见第一个1的位置	失效 ? 
// __builtin_popcount(unsigned int x) 统计二进制中1的个数
// __builtin_clz(unsigned int x) 返回一个二进制数中前导0的个数
// __builtin_ctz(unsigned int x) 返回一个二进制数中后导0的个数
class Solution0 {
  public:
    int findComplement(int num) {
        unsigned int cnt = __builtin_clz(num);
        unsigned int ans = num ^ 0xffffffff;
        return ((ans << cnt) >> cnt);
    }
};

// Bit Manipulation 原理: 计算00000011111序列然后取异或, 这个序列也可以很容易得到前导零的个数
// time: O(1)
// space: O(1)
class Solution1 {
  public:
    int findComplement(int num) {
        int n = num, cnt = 0;
        while(n) {  // 计算有效位
            ++cnt;
            n >>= 1;
        }
        return num ^ ((long)(1 << cnt) - 1);
    }
};

// Bit Manipulation 原理: 通过x & (x - 1)只保留高位的1, 得到00000011111序列取异或, 这个序列也可以很容易得到前导零的个数
// time: O(1)
// space: O(1)
class Solution {
  public:
    int findComplement(int num) {
        unsigned int n = num;
        while ((n & (n - 1)) != 0) n &= (n - 1);
        return num ^ ((n << 1) - 1);
    }
};

int main() {
    Solution s;
    cout << s.findComplement(5) << endl;    // 2
    cout << s.findComplement(1) << endl;    // 0
    return 0;
}
