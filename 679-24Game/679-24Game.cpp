#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

// Math - 从4个数字中有序选择2个数字, 4*3=12种选择, 并选择1/4个运算, 3个选2个, 3*2=6并选择1/4个运算, 最后两个选择1/4运算
// => (4*3*4)*(3*2*4)*(2*4) = 9216种, 注意并不是所有运算都是有序的, 对加和乘可以进行剪枝
// time: O(1)
// space: O(1)
class Solution {
  public:
    bool judgePoint24(vector<int> &nums) {
        vector<double> idbl;
        for (const int &num: nums) idbl.emplace_back(static_cast<double>(num));
        return solve(idbl);
    }
  private:
    static constexpr int TARGET = 24; 
    static constexpr double EPSILON = 1e-6;
    static constexpr int ADD = 0, MULTIPLY = 1, SUBTRACT = 2, DIVIDE = 3;
    bool solve(vector<double> &idbl) {
        if (idbl.size() == 0) return false; // 递归终止, 无法实现
        if (idbl.size() == 1) return fabs(idbl[0] - TARGET) < EPSILON;  // 递归完成
        int len = idbl.size();
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                if (i == j) continue;   // 不能选同一个数字
                vector<double> idbl_tmp = vector<double> ();    
                for (int k = 0; k < len; ++k)   // 选了两个数字之后的剩余数字
                    if (k != i && k != j)
                        idbl_tmp.emplace_back(idbl[k]);
                for (int k = 0; k < 4; ++k) {   // 将选出的两个数字进行运算后递归
                    if (k < 2 && i > j) continue;   // 加法乘法满足交换律, 剪枝
                    if (k == ADD)
                        idbl_tmp.emplace_back(idbl[i] + idbl[j]);
                    else if (k == MULTIPLY)
                        idbl_tmp.emplace_back(idbl[i] * idbl[j]);
                    else if (k == SUBTRACT)
                        idbl_tmp.emplace_back(idbl[i] - idbl[j]);
                    else if (k == DIVIDE) {
                        if (idbl[j] < EPSILON) continue;    // 除零保护
                        idbl_tmp.emplace_back(idbl[i] / idbl[j]);
                    }
                    if (solve(idbl_tmp)) return true;
                    idbl_tmp.pop_back();    // 弹出以便进行下一次运算
                }
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> nums = {4, 1, 7, 8};
    cout << s.judgePoint24(nums) << endl;
    return 0;
}