#include <cmath>
#include <climits>
#include <iostream>
using namespace std;

//>Magic Number>牛顿迭代法>二分查找法
//9						1：4 ：7
//100.23				2：6 ：8
//1000.147				2：8 ：15
//3654.8963				2：9 ：17
//21473.95600			2：10：19
//456789123.456			3: 18: 31
//这是因为牛顿迭代法只从右侧逼近(只对开方这个运算，复杂的f(x)对应复杂曲线会有不同，详情查看维基百科牛顿法)
//而二分查找从右侧左侧同时逼近。Magic Number不管任何数字用三次迭代，可以精确到小数点后两位
//Magic number的原理是与浮点数的位存储相关。

static int lable = 0;

//二分
class Solution1
{
  public:
    double mySqrt(double x)
    {
		return biSearch(1, x / 2, x);
    }

  private:
    double biSearch(double low, double high, double x)
    {
		lable++;
		double mid = low + (high - low) / 2;
		if (low <= high)
		{ //(mid+delta)*(mid+delta) = x;	delta^2<<delta	delta = (x-mid^2)/(2*mid)
			if (fabs(x - mid * mid) / (2 * mid) < 0.01)
				return mid; //计算误差在0.01以内，即使这样，小数点后第一位也不一定可靠
			else if (x / mid < mid)
				return biSearch(low, mid, x);
			else if (x / mid > mid)
				return biSearch(mid, high, x);
		}
    }
};

//牛顿迭代法
class Solution2
{
  public:
    double mySqrt(double x)
    {
		double xk = 1;
		do //使用do while保证xk=1进入循环
		{
			lable++;
			xk = xk / 2 + x / xk / 2;
		} while (abs((x - xk * xk) / (2 * xk)) > 0.01);
		return xk;
    }
};

//Magic Number
class Solution3
{
  public:
    float mySqrt(float number)
    {
		int i;
		float x, y;
		const float f = 1.5F;
		x = number * 0.5F;
		y = number;
		i = *(int *)&y;
		i = 0x5f375a86 - (i >> 1);
		y = *(float *)&i;
		y = y * (f - (x * y * y) );
		y = y * (f - (x * y * y) );
		y = y * (f - (x * y * y) ); //Newton Step,Repeating Increases Accuracy
		return number * y;	
    }
};

//最精简1.f/sqrt()算法
class Solution4
{
  public:
    float mySqrt(float x)
    {
		float xhalf = 0.5F * x;
		int i = *(int *)&x;		//get bits for floating value
		i = 0x5f375a86 - (i >> 1);      //give initial guess y0
		x = *(float *)&i;		//convert bits BACK tofloat
		x = x * (1.5F - xhalf * x * x); //Newton Step,Repeating Increases Accuracy
		return x;
    }
};

int main()
{
    Solution3 s1;
    float x = 100.23;
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << s1.mySqrt(x) << endl;
    cout << lable << endl;
    return 0;
}