#include <iostream>
using namespace std;

//通过d(当前位数最小值10000??),
//得到最高位 x / d;
//得到最低位 x % 10;
//快速除去最高位  x % d;
//快速除去最低位  x / 10;
//其实还是用到 / 和 % 的概念，留数和余数
class Solution
{
  public:
    bool isPalindrome(int x)
    {
		if (x < 0)
			return false;
		int d = 1;
		while (x / d >= 10)
			d *= 10; //快速计算d
		while (x > 0)
		{
			int low = x % 10;
			int high = x / d;
			if (low != high)
				return false;
			x = x % d / 10;
			d /= 100;
		}
		return true;
    }
};

int main()
{
    Solution s1;
    int x = 94549;
    cout << s1.isPalindrome(x) << endl;
    return 0;
}