#include <string>
#include <iostream>
using namespace std;

//连续倒N型排列，分类
class Solution
{
  public:
    string convert(const string text, int numRows)
    {
        const int n = text.size();
        if (n < 2 || numRows < 2)
            return text;               //边界条件
        const int m = 2 * numRows - 2; //辅助空间
        string result;
        for (int i = 0; i < numRows; ++i)
        { //numRows行
            int start = i;
            //对每一行跳跃添加
            if (start == 0)
                while (start < n)
                {
                    result.push_back(text[start]);
                    start += m;
                }
            else
            {
                while (start < n)
                {
                    result.push_back(text[start]);
                    int k = start + m - 2 * (start % m); //找对称元素
                    if (k != start && k < n)
                        result.push_back(text[k]);
                    start += m;
                }
            }
        }
        return result;
    }
};

//将分类组合
class Solution1
{
  public:
    string convert(const string text, int numRows)
    {
        const int n = text.size();
        if (n < 2 || numRows < 2)
            return text;               //注意边界条件
        const int m = 2 * numRows - 2; //辅助空间
        string result;
        for (int i = 0; i < numRows; ++i)
        { //numRows行
            int start = i;
            //对每一行跳跃添加
            while (start < n)
            {
                result.push_back(text[start]);
                if (start % m == 0)
                {
                    start += m;
                    continue;
                }
                int k = start + m - 2 * (start % m); //找对称元素
                if (k != start && k < n)             //对称元素合法
                    result.push_back(text[k]);
                start += m;
            }
        }
        return result;
    }
};

//记录两个递增变量
class Solution2
{
  public:
    string convert(string s, int nRows)
    {
        if (nRows <= 1 || s.size() <= 1)
            return s;
        string result;
        for (int i = 0; i < nRows; i++)
        {
            for (int j = 0, index = i; index < s.size(); j++, index = (2 * nRows - 2) * j + i)
            {
                result.append(1, s[index]); //垂直元素
                if (i == 0 || i == nRows - 1)
                    continue; //斜对角元素
                if (index + (nRows - i - 1) * 2 < s.size())
                    result.append(1, s[index + (nRows - i - 1) * 2]);
            }
        }
        return result;
    }
};

int main()
{
    Solution1 s1;
    string s("A");
    int numRows = 1;
    cout << s << endl;
    string result = s1.convert(s, numRows);
    cout << result << endl;
    return 0;
}