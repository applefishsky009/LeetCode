#include <iostream>
using namespace std;

// 不能使用乘除法,for,while,if,else,switch,case等关键字
// 递归代替循环
class Solution1 {
  public:
    int sumNums(int n) {
        n && (n += sumNums(n - 1));
        return n;
    }
};

// 俄罗斯农夫乘法
class Solution2 {
  public:
    int sumNums(int n) {
        int ans = 0;
        ans += (n & -(1 & ((n + 1) >> 0))) << 0;    // 和-1取与为原数,和0取与为0
        ans += (n & -(1 & ((n + 1) >> 1))) << 1;
        ans += (n & -(1 & ((n + 1) >> 2))) << 2;
        ans += (n & -(1 & ((n + 1) >> 3))) << 3;
        ans += (n & -(1 & ((n + 1) >> 4))) << 4;
        ans += (n & -(1 & ((n + 1) >> 5))) << 5;
        ans += (n & -(1 & ((n + 1) >> 6))) << 6;
        ans += (n & -(1 & ((n + 1) >> 7))) << 7;
        ans += (n & -(1 & ((n + 1) >> 8))) << 8;
        ans += (n & -(1 & ((n + 1) >> 9))) << 9;
        ans += (n & -(1 & ((n + 1) >> 10))) << 10;
        ans += (n & -(1 & ((n + 1) >> 11))) << 11;
        ans += (n & -(1 & ((n + 1) >> 12))) << 12;
        ans += (n & -(1 & ((n + 1) >> 13))) << 13;
        ans += (n & -(1 & ((n + 1) >> 14))) << 14;
        return ans >> 1;
    }
};

// 俄罗斯农夫乘法
class Solution {
  public:
    int sumNums(int n) {
        int ans = 0, a = n, b = n + 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;    // 减半的数字-偶数删除,奇数相加
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        (b & 1) && (ans += a); a <<= 1; b >>= 1;
        return ans >> 1;
    }
};

int main() {
    Solution s;
    cout << s.sumNums(3) << endl;
    cout << s.sumNums(9) << endl;
    return 1;
}