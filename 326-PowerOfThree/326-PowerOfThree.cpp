#include <cmath>
#include <iostream>
using namespace std;

// 迭代
// time: O(lgn)
// space: O(1)
class Solution0 {
  public:
    bool isPowerOfThree(int n) {
        // while (n >= 3) {
        //     if (n % 3 != 0)
        //         return false;
        //     n /= 3;
        // }
        if (n < 1) return false;
        while (n % 3 == 0)
            n /= 3;
        return n == 1;
    }
};

// 递归
// time: O(lgn)
// space: O(lgn)
class Solution1 {
  public:
    bool isPowerOfThree(int n) {
        if (n == 1) return true;
        if (n % 3 != 0 || n == 0) return false;
        return isPowerOfThree(n / 3);
    }
};

// 整数限制
// time: O(1)
// space: O(1)
class Solution {
  public:
    bool isPowerOfThree(int n) {
        int maxn = log(INT_MAX) / log(3);   // C++的对数函数
        int maxk = pow(3, maxn);    // C++的指数函数
        return n > 0 && maxk % n == 0;
    }
};

int main() {
    Solution s;
    cout << s.isPowerOfThree(27) << endl;   // 1
    cout << s.isPowerOfThree(28) << endl;   // 0
    cout << s.isPowerOfThree(0) << endl;    // 0
    cout << s.isPowerOfThree(9) << endl;    // 1
    cout << s.isPowerOfThree(45) << endl;   // 0
    return 0;
}