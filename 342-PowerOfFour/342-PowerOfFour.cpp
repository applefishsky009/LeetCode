#include <cmath>
#include <iostream>
using namespace std;

// 迭代 8 ? 以0开始计算 奇数位上不能有1, 1也是4的幂
// time: O(lgn)
// space: O(1)
class Solution0 {
  public:
    bool isPowerOfFour(int num) {
        if (num < 1) return false;
        while (num % 4 == 0)
            num /= 4;
        return num == 1;
    }
};

// 数学 x = 4^a, a = log4_x = 1 / 2 * log2^x, 那么判断a为整数即可
// time: O(1)
// space: O(1)
class Solution1 {
  public:
    bool isPowerOfFour(int num) {
        if (num < 1) return false;
        auto numn = log(num) / log(2);
        if (numn - int(numn) > 0.0001) return false;
        return num > 0 && ((int)(log(num) / log(2)) % 2 == 0);
    }
};

// 数学 奇数位上不能有1 (101010...10)_{2} 用十六进制表示为 : (aaaaaaaa)_{16}
// time: O(1)
// space: O(1)
class Solution2 {
  public:
    bool isPowerOfFour(int num) {
        return (num > 0) && ((num & (num - 1)) == 0) && ((num & (int)0xaaaaaaaa) == 0); // 注意判断是否是2的幂, 否则包含1的结果不对
    }
};

// 数学 - 位运算 x=((3+1)^k mod 3)中对k进行数学归纳分解, x=((3+1)^1 mod 3) = 1
// time: O(1)
// space: O(1)
class Solution {
  public:
    bool isPowerOfFour(int num) {
        return (num > 0) && ((num & (num - 1)) == 0) && (num % 3 == 1);
    }
};

int main() {
    Solution s;
    cout << s.isPowerOfFour(16) << endl;    // 1
    cout << s.isPowerOfFour(5) << endl; // 0
    cout << s.isPowerOfFour(8) << endl;    // 0
    return 0;
}
