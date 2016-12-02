#include <string>
#include <iostream>
using namespace std;

//I（1）、V（5）、X（10）、L（50）、C（100）、D（500）和M（1000）

//使用Hash Table暴力破解要方便太多了
//除数留余法
class Solution
{
  public:
    string intToRoman(int num)
    {
		const int radix[] = {1000, 900, 500, 400, 100, 90,
					50, 40, 10, 9, 5, 4, 1};
		const string symbol[] = {"M", "CM", "D", "CD", "C", "XC",
					"L", "XL", "X", "IX", "V", "IV", "I"};
		string roman;
		for (size_t i = 0; num > 0; ++i)
		{
			int count = num / radix[i];
			num %= radix[i]; //计算余数，有多少余数就加入到字符串中
			for (; count > 0; --count)
				roman += symbol[i];
		}
		return roman;
    }
};

int main()
{
    Solution s1;
    int num = 2333;
    cout << s1.intToRoman(num) << endl;
    return 0;
}