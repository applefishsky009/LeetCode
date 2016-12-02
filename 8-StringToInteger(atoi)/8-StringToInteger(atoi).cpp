//非常重要
//遇到有效输入开始读取，直到碰到无效输入

//"   -123f123" = -123
//"   -1 234"   = 0;	注意这个是无效的
//注意溢出

#include <string>
#include <cctype>
#include <climits>
#include <iostream>
using namespace std;

//在自己解答这道题的时候，将情况想的太过复杂,注意atoi的本质
//第20行代码中去掉flag == 0 &&，可以将数字中的空格也去掉
class Solution
{
  public:
    int myAtoi(string str)
	{
		long long sum = 0;
		int flag = 0;
		for (int i = 0; i < str.size(); ++i)
		{
			if (flag == 0 && str[i] == ' ') //去掉数字之前的空格
				continue;
			else if (flag == 0 && (str[i] == '-' || str[i] == '+' || isdigit(str[i])))
			{ //判断符号位
				flag = str[i] == '-' ? -1 : 1;
				if (isdigit(str[i]))
					sum = sum * 10 + (str[i] - '0');
			}
			else if (isdigit(str[i])) //开始数字累计
				sum = sum * 10 + (str[i] - '0');
			else if (!isdigit(str[i])) //无效输入，跳出
				break;
			if (abs(sum) >= INT_MAX)
				break; //判断溢出
		}
		sum = sum * flag;
		if (sum >= INT_MAX)
			return INT_MAX;
		if (sum <= INT_MIN)
			return INT_MIN;
		return sum;
	}
};

	//有效输入之前的判断卸载循环之外降低判断次数
class Solution1
{
  public:
	int myAtoi(const string &str)
	{
		long long sum = 0;
		int sign = 1;
		int i = 0;
		while (str[i] == ' ' && i < str.length())
			i++;	   //有限输入之前
		if (str[i] == '+') //判断符号位
			i++;
		else if (str[i] == '-')
		{
			sign = -1;
			i++;
		}
		for (; i < str.length(); i++)
		{ //有效输入
			if (!isdigit(str[i]))
				break; //无效输入
			sum = sum * 10 + (str[i] - '0');
			if (abs(sum) > INT_MAX)
				break; //溢出
		}
		sum = sum * sign;
		if (sum >= INT_MAX)
			return INT_MAX;
		if (sum <= INT_MIN)
			return INT_MIN;
		return sum;
    }
};

int main()
{
    Solution s1;
    string str = "1234567";
    cout << s1.myAtoi(str) << endl;
    return 0;
}