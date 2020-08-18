#include <vector>
#include <iostream>
using namespace std;

// BS
// time: O(lgn)
// space: O(1)
class Solution0 {
  public:
    bool isPerfectSquare(int num) { // 给定了num为正整数
        // if (num < 0) return false;
        if (num == 1) return true;
        int l = 1, r = num >> 1;
        while (l < r) {
            int mid = l + ((r - l) >> 1);
            if (num / mid > mid)    // 防溢出
                l = mid + 1;
            else
                r = mid;
        }
        return (long long)l * r == num;    // 防溢出
    }
};

// 牛顿迭代法 f(x) = x^2 - num = 0的根, 取x_k作为根的近似初始值, 在(x_k, f(x_k))处做切线与x轴相交经过x_k+1, f(x_k) / (x_k - x_k+1) = f'(x_k) =>
// x_k+1 = x_k - f(x_k)/f'(x_k)而f'(x_k) = 2x_k那么x_k+1 = 1/2(x_k + num/ x_k), 取初始值为num / 2, x*x>num时用牛顿迭代
// time: O(lgn)
// space: O(1)
class Solution {
  public:
    bool isPerfectSquare(int num) {
        if (num == 1) return true;
        int x = (num >> 1);
        while (num / x < x)
            x = ((x + num / x) >> 1);
        return x * x == num;    // 不存在溢出的问题
    }
};

int main() {
    Solution s;
    cout << 2147483647 << ends << s.isPerfectSquare(2147483647) << endl;
    cout << 2000105819 << ends << s.isPerfectSquare(2000105819) << endl;
    cout << 1 << ends << s.isPerfectSquare(1) << endl;
    cout << 2 << ends << s.isPerfectSquare(2) << endl;
    cout << 3 << ends << s.isPerfectSquare(3) << endl;
    cout << 4 << ends << s.isPerfectSquare(4) << endl;
    cout << 5 << ends << s.isPerfectSquare(5) << endl;
    cout << 6 << ends << s.isPerfectSquare(6) << endl;
    cout << 7 << ends << s.isPerfectSquare(7) << endl;
    cout << 8 << ends << s.isPerfectSquare(8) << endl;
    cout << 9 << ends << s.isPerfectSquare(9) << endl;
    cout << 10 << ends << s.isPerfectSquare(10) << endl;
    cout << 11 << ends << s.isPerfectSquare(11) << endl;
    cout << 12 << ends << s.isPerfectSquare(12) << endl;
    cout << 13 << ends << s.isPerfectSquare(13) << endl;
    cout << 14 << ends << s.isPerfectSquare(14) << endl;
    cout << 15 << ends << s.isPerfectSquare(15) << endl;
    cout << 16 << ends << s.isPerfectSquare(16) << endl;
    return 0;
}