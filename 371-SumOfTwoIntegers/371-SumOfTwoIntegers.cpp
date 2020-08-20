#include <iostream>
using namespace std;

// bit - 迭代
// ((a & b) << 1)得到两数相加产生的进位, a ^ b得到两数相加不进位的结果, 注意不能给带符号类型一个超出他范围的值
// time: O(1)
// space: O(1)
class Solution0 {
  public:
    int getSum(int a, int b) {
        while (b) { // a作为结果, b作为进位
            auto carry = (((unsigned int)(a & b)) << 1);    // a & b的结果是负数时, 左移会造成符号位溢出, 转换为uint避免左移越界
            a ^= b; // 异或 - 异为1
            b = carry;
        }
        return a;
    }
};

// bit - 递归
// ((a & b) << 1)得到两数相加产生的进位, a ^ b得到两数相加不进位的结果, 注意不能给带符号类型一个超出他范围的值
// time: O(1)
// space: O(1)
class Solution {
  public:
    int getSum(int a, int b) {
        return b == 0 ? a : getSum(a ^ b, ((unsigned int)(a & b)) << 1); // 进位和不进位
    }
};

int main() {
    Solution s;
    cout << s.getSum(1, 2) << endl;
    cout << s.getSum(-2, 3) << endl;
    return 0;
}
