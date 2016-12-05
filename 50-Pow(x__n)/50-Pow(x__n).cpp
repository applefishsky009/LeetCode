#include <cmath>
#include <climits>
#include <iostream>
using namespace std;

//magic num
class Solution
{
  public:
    double myPow(double x, int n)
    {
		if (n == 0 || x == 1)
			return 1;
		if (n == -2147483648)
			return (double)1 / (x * myPow(x, 2147483647));
		if (n < 0)
			return (double)1 / myPow(x, 0 - n);
		if (n % 2 == 0)
			return myPow(x * x, n / 2);
		return x * myPow(x, n - 1);
    }
};

class Solution1
{
  public:
    //基本数据类型按值传递
    double myPow(double x, int n)
    {
		if (n == INT_MIN)
			return 1.0 / (x * myPow(x, INT_MAX));
		if (n < 0)
			return 1.0 / pow(x, -n);
		return pow(x, n);
    }

  private:
    double power(double x, int n)
    {
		if (n == 0 || x == 1) //if (n == 1)
			return 1;	 //return x;
		double v = power(x, n / 2);
		if (n % 2 == 0)
			return v * v;
		return v * v * x;
    }
};

int main()
{
    Solution s1;
    int n = INT_MIN;
    double doubleIn = 2.0;
    double doubleOut = s1.myPow(doubleIn, n);
    cout << doubleOut << endl;
    return 0;
}
