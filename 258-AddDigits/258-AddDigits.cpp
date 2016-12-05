#include <iostream>
using namespace std;

//利用模九同余的性质：任何一个整数模9同余于它的各数位上数字之和
//输入为non-negative integer
//注意除0之外,余数为0输出为9

class Solution1
{
  public:
    int addDigits(int num)
    {
		int k = num % 9;
		if (num != 0 && k == 0)
			return 9;
		return k;
    }
};

//合并成一行
//num的余数为 0 1 2 3 4 5 6 7 8	(num-1)%9
//			  8 0 1 2 3 4 5 6 7	(num-1)%9+1
//		      9 1 2 3 4 5 6 7 8
//对于0:	  (0-1)%9 = -1;(num-1)%9+1=0;符合条件。
class Solution
{
  public:
    int addDigits(int num)
    {
		return (num - 1) % 9 + 1;
    }
};

int main()
{
    Solution s1;
    int num = 54465;
    cout << s1.addDigits(num) << endl;
    return 0;
}