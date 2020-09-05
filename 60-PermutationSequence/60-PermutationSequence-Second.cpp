#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <D:\Github\RylModule\list.h>
using namespace std;

// 数学 + 缩小问题规模 康托编码 base = 1
// 第k个排列的首个数字是 [(k - 1) / (n - 1)!] + 1, k' = (k - 1) mod (n - 1)! + 1 康托编码从0开始
// ((k - base) / n + base)表示, 以[0, n - 1]表示区间, k在第几个区间内(从第base个开始计数)
// ((k - base) % n + base)表示, 以[0, n - 1]表示区间, k表示区间内的第几个数(从base开始计数)
// time : O(n^2)
// space : O(n)
class Solution {
  public:
    string getPermutation(int n, int k) {
        vector<int> factorial(n, 1);
        for (int i = 1; i < n; i++) factorial[i] = factorial[i - 1] * i;    // 计算n的阶乘
        --k;    // 转换为从0开始计数, 康托编码从0开始因为余数范围是[0, k - 1], 所以计算整除区间需要映射
        string ans;
        vector<int> valid(n + 1, 1);
        for (int i = 1; i <= n ; ++i) { // 找第i个字符
            int order = k / factorial[n - i] + 1;   // 寻找排列中的首个元素, 元素从1开始, 因此要+1, base = 1
            for (int j = 1; j <= n; ++j) {  // 元素从1开始
                order -= valid[j];  // 寻找这个数字, 1计数0不计数
                if (!order) {
                    ans += (j + '0');
                    valid[j] = 0;
                    break;
                }
            }
            k %= factorial[n - i];  // 余数方便找下一个, 这是计算k是[0, n - 1]区间内的下标, 没有base, 如说是计算第几个数的base = 1
        }
        return ans;
    }
};

int main() {
    Solution s1;
    int n = 4, k = 9;
    string result = s1.getPermutation(n, k);
    cout << result << endl;
    return 0;
}