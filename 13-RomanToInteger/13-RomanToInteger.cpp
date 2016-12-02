#include <vector>
#include <string>
#include <iostream>
using namespace std;

//参考Int ot Roman,Hash Table,除数留余，但是substr方法会导致速度比较慢
class Solution
{
  public:
    int romanToInt(string s)
    {
        const vector<string> symbol{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"}; //0-12
        const int radix[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};                         //0-12
        int result = 0;
        int i = 0, j = 0;
        while (i < s.size())
        {
            if (s.substr(i, symbol[j].size()) == symbol[j])
            {
                result += radix[j];
                i += symbol[j].size();
            }
            else
                ++j;
        }
        return result;
    }
};

// LeetCode, Roman to Integer
// 从前往后扫描，如果当前比前一个大，说明这一段的值应该是当前这个值减去上一个值，IV = 4;否则，将当前值加入结果，然后开始下一段记录，VI，II
//没有substr的Hash Table
class Solution1
{
  public:
    int romanToInt(const string &s)
    {
        int result = 0;
        for (size_t i = 0; i < s.size(); i++)
        {
            if (i > 0 && map(s[i]) > map(s[i - 1])) //与前一个状态有关，简单DP
                result += (map(s[i]) - 2 * map(s[i - 1]));
            else
                result += map(s[i]);
        }
        return result;
    }

  private:
    inline int map(const char c)
    {
        switch (c)
        {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
        }
    }
};

int main()
{
    Solution s1;
    string s("II");
    cout << s1.romanToInt(s) << endl;
    return 0;
}