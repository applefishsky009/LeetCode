#include <cmath>
#include <climits>
#include <iostream>
using namespace std;

//自己写的，逐差，但是会超时，需要优化
class Solution
{
  public:
    int divide(int dividend, int divisor)
    {
        if (0 == divisor)
            return INT_MAX; //非法值
        if (INT_MIN == dividend)
        { //边界处理
            if (divisor == -1)
                return INT_MAX;
            return INT_MIN;
        }
        if (dividend < 0 || divisor < 0)
        { //正负号处理
            if (dividend < 0 && divisor < 0)
                return divide(-dividend, -divisor);
            return -divide(abs(dividend), abs(divisor));
        }
        int step = 0;
        while (dividend - divisor >= 0)
        {
            ++step;
            dividend -= divisor;
        }
        return step;
    }
};

//在逐差的基础上每次将除数翻倍(左移)，完成优化
class Solution1
{
  public:
    int divide(int dividend, int divisor)
    {
        if (0 == divisor)
            return INT_MAX; //非法值
        if (INT_MIN == dividend && -1 == divisor)
            return INT_MAX; //特殊情况，否则转化截短之后返回INT_MIN
        //用long long做溢出处理
        long long a = dividend >= 0 ? dividend : -(long long)dividend;
        long long b = divisor >= 0 ? divisor : -(long long)divisor;
        //用long long 保存结果，因为正常除法依然有一种可能(-INT_MIN,-1)溢出
        long long result = 0;
        while (a >= b)
        {
            long long c = b;
            for (int i = 0; a >= c; ++i, c <<= 1)
            { //i表示除数翻得倍数
                a -= c;
                result += 1 << i;
            }
        }
        return ((dividend ^ divisor) >> 31) ? (-result) : (result); //是否需要返回负号
    }
};

// LeetCode, Divide Two Integers
// 时间复杂度 O(logn) 空间复杂度 O(1)
class Solution2
{
  public:
    int divide(int dividend, int divisor)
    {
        if (0 == divisor)
            return INT_MAX; //非法值
        if (INT_MIN == dividend && -1 == divisor)
            return INT_MAX;                                                               //特殊情况，否则转化截短之后返回INT_MIN
        int result = 0;                                                                   // (-INT_MIN,-1)溢出
        const bool sign = (dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0); //异号
        // 当 dividend = INT_MIN 时 -dividend 会溢出 所以用unsigned int
        unsigned int a = dividend >= 0 ? dividend : -dividend;
        unsigned int b = divisor >= 0 ? divisor : -divisor;
        while (a >= b)
        {
            int multi = 1;
            unsigned int bb = b;
            while (a >= bb)
            {
                a -= bb;
                result += multi;
                if (bb<INT_MAX>> 1)
                {             // 防止溢出，即保证除数(翻倍后)太大时跳出循环
                    bb += bb; //除数翻倍'
                    multi += multi;
                }
            }
        }
        if (sign)
            return -result;
        else
            return result;
    }
};

int main()
{
    Solution2 s1;
    int dividend = 10;
    int divisor = 0;
    int k = s1.divide(dividend, divisor);
    cout << k << endl;
    return 0;
}