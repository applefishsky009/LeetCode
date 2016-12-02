#include <climits>
#include <iostream>
using namespace std;

class Solution
{
  public:
    int reverse(int x)
    {
		long long temp = 0;
		bool sign = x > 0 ? true : false; //先判断正负再反转，不然x反转存入temp，x=0;
		for (; x; x /= 10)		  //巧妙的反转
			temp = temp * 10 + x % 10;    //将x的低位给temp的高位
		if (sign && temp <= INT_MAX)
			return temp;
		if (!sign && temp >= INT_MIN)
			return temp;
		return 0;
    }
};

int main()
{
    int intIn = -123;
    Solution s1;
    cout << s1.reverse(intIn) << endl;
    return 0;
}