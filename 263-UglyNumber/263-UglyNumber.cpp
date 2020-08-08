#include <vector>
#include <iostream>
using namespace std;

// time: O(1)
// space: O(1)
class Solution0 {
  public:
    bool isUgly(int num) {
        int cur = num;
        vector<int> factor2;
        vector<int> factor3;
        vector<int> factor5;
        generateFactor(factor2, 2);
        generateFactor(factor3, 3);
        generateFactor(factor5, 5);
        cur = factorDivide(factor2, cur);
        cur = factorDivide(factor3, cur);
        cur = factorDivide(factor5, cur);
        return cur == 1;
    }
  private:
    using LL = long long;
    LL imax = (1LL << 31) - 1;
    void generateFactor(vector<int> &factor, int num) {
        LL cur = num;
        while (cur < imax) {
            factor.push_back(cur);
            cur *= num;
        }
    }
    int factorDivide(vector<int> &factor, int num) {
        for (int i = factor.size(); i >= 0; --i) {
            if (num >= factor[i] && num % factor[i] == 0) {
                num /= factor[i];
                break;
            }
        }
        return num;
    }
};

// 递归 - DFS的贪心搜索, 不需要带缓存
// time: O(1)
// space: O(1)
class Solution {
  public:
    bool isUgly(int num) {
        if (num < 1) return false;
        return searchUgly(num);
    }
  private:
    bool searchUgly(int num) {
        if (num == 1) return true;
        if (num % 2 != 0 && num % 3 != 0 && num % 5 != 0)
            return false;
        else    // 深度优先
            return (num % 2 == 0 ? searchUgly(num / 2) : false) || (num % 3 == 0 ? searchUgly(num / 3) : false) || (num % 5 == 0 ? searchUgly(num / 5) : false);
    }
};

// 迭代 - 贪心
// time: O(1)
// space: O(1)
class Solution2 {
  public:
    bool isUgly(int num) {
        if (num <= 0) return false;
        if (num == 1) return true;
        vector<int> factor = {2, 3, 5};
        for (int i = 0; i < factor.size(); ++i)
            while (num % factor[i] == 0)
                num /= factor[i];
        return num == 1;
    }
};

int main() {
    Solution s;
    cout << s.isUgly(6) << endl;
    cout << s.isUgly(8) << endl;
    cout << s.isUgly(14) << endl;
    return 0;
}
