#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

// dp[i] = dp[i - 1] + dp[i - 2]
class Solution1 {
  public:
    int climbStairs(int n) {
        int i = 0, dp_pre1 = 2, dp_pre2 = 1, dp_cur = 0;
        for (i = 0; i < n - 2; i++) {
            dp_cur = dp_pre1 + dp_pre2;
            dp_pre2 = dp_pre1;
            dp_pre1 = dp_cur;
        }
        return n < 2 ? 1 : dp_pre1;
    }
};

// dp[i] = dp[i - 1] + dp[i - 2], 1 1 2 3 5 8 ……
// 特征方程x^2=x+1,解x1=(1+sqrt(5))/2,x2=(1-sqrt(5))/2,通解f(n)=c1*x1^n+c2*x2^n
// 带入初始条件f(1)=1,f(2)=1,c1=1/sqrt(5),c2=-1/sqrt(5)
class Solution2 {
  public:
    int climbStairs(int n) {
        double sqrt5 = sqrt(5);
        double fibn = pow((1 + sqrt5) / 2, n + 1) - pow((1 - sqrt5) / 2, n + 1); // 答案下标从0开始,因此求n+1
        return (int)(fibn / sqrt5 + 0.5);   // 取整风险
    }
};

// 矩阵快速幂,求[1, 1; 1, 0]^n
//[f(n+1); f(n)] = [1, 1; 1, 0][f(n); f(n - 1)]->[f(n+1); f(n)] = [1, 1; 1, 0]^n[f(1), f(0)]
class Solution {
  public:
    int climbStairs(int n) {
        vector<vector<long long>> q = {{1, 1}, {1, 0}};
        vector<vector<long long>> res = matrixPow(q, n);
        return res[0][0];
    }
  private:
    vector<vector<long long>> matrixPow(vector<vector<long long>> &a, int n) {
        vector<vector<long long>> ret = {{1, 0}, {0, 1}}; // 初始状态
        while (n > 0) {
            if ((n & 1) == 1)   // 按位取值
                ret = matrixMultiply(ret, a);
            n >>= 1;
            a = matrixMultiply(a, a);   // 计算下一位的矩阵值,这里决定数据类型必须用longlong,否则越界风险
        }
        return ret;
    }
    vector<vector<long long>> matrixMultiply(vector<vector<long long>> &a, vector<vector<long long>> &b) {
        int i = 0, j = 0;
        vector<vector<long long>> c = {{0, 0}, {0, 0}};
        for (i = 0; i < 2; i++)
            for (j = 0; j < 2; j++)
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
        return c;
    }
};

int main() {
    Solution s;
    Solution1 s1;
    Solution2 s2;
    cout << s.climbStairs(35) << endl;
    cout << s1.climbStairs(35) << endl;
    cout << s2.climbStairs(35) << endl;
    cout << s.climbStairs(0) << endl;
    cout << s1.climbStairs(0) << endl;
    cout << s2.climbStairs(0) << endl;
    cout << s.climbStairs(1) << endl;
    cout << s1.climbStairs(1) << endl;
    cout << s2.climbStairs(1) << endl;
    cout << s.climbStairs(2) << endl;
    cout << s1.climbStairs(2) << endl;
    cout << s2.climbStairs(2) << endl;
    cout << s.climbStairs(3) << endl;
    cout << s1.climbStairs(3) << endl;
    cout << s2.climbStairs(3) << endl;
    return 1;
}