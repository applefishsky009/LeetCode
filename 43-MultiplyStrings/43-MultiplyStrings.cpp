#include <string>
#include <iostream>
using namespace std;

//分解123*456=（100+20+3）*（400+50+6）观察规律(按结果逐位计算)：
//某一位上的数字是进位与(两个字符串下标和是这个位数)的字符乘积之和
//先转置字符串，容易计算，将结果再转置一次容易计算很多(应该更快，因为头插多次，每一次都是O(n))
class Solution
{
  public:
    string multiply(string num1, string num2)
    {
		if (num1 == "0" || num2 == "0")
			return "0";
		string result;
		const int n = num1.size();
		const int m = num2.size();
		int index = 0;
		int carry = 0; //进位
		while ((index < n + m - 1) || carry != 0)
		{ //注意一定在n + m - 2上有值
			if (index >= n + m - 1)
			{						    //只剩余数
				result.insert(result.begin(), carry + '0'); //头插
				break;
			}
			int i = index < n ? index : n - 1; //num1访问不越界
			int temp = carry;
			for (int k = i; k >= 0; --k)						 //每个可能的num1元素对应一个num2元素(只要不越界)
				if (m + k >= index + 1)							 //num2访问不越界
					temp += (num1[n - 1 - k] - '0') * (num2[m - 1 - (index - k)] - '0'); //没有翻转字符串，对称访问
			result.insert(result.begin(), temp % 10 + '0');				 //头插
			carry = temp / 10;								 //进位
			++index;
		}
		return result;
    }
};

//OJ上的解法，最重要的一点：固定字符串取消头插操作
//注意，原理也不同，上述自写方案是按结果逐位计算，这里是按num1逐位与num2整体计算并叠加结果
//（100+20+3）*（400+50+6） = 100*（400+50+6）+20*（400+50+6）+3*（400+50+6）
class Solution1
{
  public:
    string multiply(string num1, string num2)
    {
		string sum(num1.size() + num2.size(), '0');

		for (int i = num1.size() - 1; 0 <= i; --i)
		{
			int carry = 0;
			for (int j = num2.size() - 1; 0 <= j; --j)
			{										    //j - 1就等于*10
				int tmp = sum[i + j + 1] - '0' + (num1[i] - '0') * (num2[j] - '0') + carry; //原位数字和
				sum[i + j + 1] = tmp % 10 + '0';					    //求进位和余数
				carry = tmp / 10;
			}
			sum[i] += carry;
		}

		size_t startpos = sum.find_first_not_of("0"); //找第一个不是0的字符去掉头部的0
		if (string::npos != startpos)
			return sum.substr(startpos);
		return "0";
    }
};

int main()
{
    Solution1 s1;
    string num1 = "123";
    string num2 = "456";
    cout << s1.multiply(num1, num2) << endl;
    return 0;
}