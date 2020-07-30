#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// DP
// f[i] = max_1<=j<i(max(j * (i - j), j * f[i - j]))  // 将i拆分成j和i - j的和, 继续拆分？
// time: O(n^2)
// space: O(n)
class Solution1 {
  public:
    int integerBreak(int n) {
        vector<int> idp(n + 1, 0);  // 初始化
        for (int i = 2; i <= n; ++i) {
            int cur_max = 0;
            for (int j = 1; j < i; ++j)
                cur_max = max(cur_max, max(j * (i - j), j * idp[i - j]));
            idp[i] = cur_max;
        }
        return idp[n];
    }
};

// DP
// f[i] = max_1<=j<i(max(j * (i - j), j * f[i - j]))  // 将i拆分成j和i - j的和, 继续拆分？
// 对i进行奇偶分解f[i] >= i, i >= 4, 所以优化点j * (i - j); 又f[i] >= 2 * f[i - 2] >= 4 * f[i - 4], 所以只需要考虑j = 2和j = 3的情况
// f[i] = max(2 * (i - 2), 2 * f[i - 2], 3 * (i - 3), 3 * f[i - 3])
// f[1] = 0, f[2] = 1, f[3] = 2;
// time: O(n)
// space: O(n)
class Solution2 {
  public:
    int integerBreak(int n) {
        if (n < 4) return n - 1;
        vector<int> idp(n + 1, 0);  // 初始化
        idp[2] = 1;
        for (int i = 3; i <= n; ++i)
            idp[i] = max(max(2 * (i - 2), 2 * idp[i - 2]), max(3 * (i - 3), 3 * idp[i - 3]));
        return idp[n];
    }
};

// Math
// f(x) = x* exp(n/x) = x * exp(n * lnx / x)求函数极值, 驻点为x = e, 即x = e时极大值点e* exp(n/e), 和e最接近的整数2,3中f(3)/f(2) = e * exp(n / 6 * (ln 9 - ln8)) > 1, 所以极值点为3.
// 余数为0: 全分为3; 余数为1, 借个3,分为2 * 2; 余数为2, 全分为3剩个2
// time: O(1)
// space: O(1)
class Solution {
  public:
    int integerBreak(int n) {
        if (n < 4) return n - 1;
        int quotient = n / 3;
        int reminder = n % 3;
        if (reminder == 0)
            return (int)pow(3, quotient);
        else if(reminder == 1)
            return (int)pow(3, quotient - 1) * 4;
        else
            return (int)pow(3, quotient) * 2;
    }
};

int main() {
    Solution s;
    cout << s.integerBreak(10) << endl;
    return 0;
}