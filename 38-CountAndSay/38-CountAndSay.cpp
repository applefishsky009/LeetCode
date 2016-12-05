#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

//我擦，这个题目说的太不清楚了，以下写法是按顺序读出几个几的代码
class Solution
{
  public:
    string countAndSay(int n)
    {
        stack<char> s;
        int count = 1; //至少一个数字
        int pre = n % 10;
        n = n / 10;
        int cur = (n) % 10;
        while (n != 0)
        {
            if (cur == pre)
                ++count;
            else
            {
                s.push(pre + '0');
                s.push(count + '0');
                pre = cur;
                count = 1; //记录这一个数字
            }
            n = n / 10;
            cur = n % 10;
        }
        s.push(pre + '0');
        s.push(count + '0');
        string result;
        while (!s.empty())
        {
            result.push_back(s.top());
            s.pop();
        }
        return result;
    }
};

class Solution1
{
  public:
    string countAndSay(int n)
    {
        string result("1");
        for (int num = 1; num < n; ++num)
        {
            string temp;
            int count = 1; //初始一定有一个数字
            for (int i = 0; i < result.size(); ++i)
            {
                if (result[i] == result[i + 1])
                    ++count;
                else
                {
                    temp.push_back(count + '0');
                    temp.push_back(result[i]);
                    count = 1; //记录新出现的次数
                }
            }
            result = temp;
        }
        return result;
    }
};

class Solution2
{
  public:
    string countAndSay(int n)
    {
        string s("1");
        while (--n)
            s = getNext(s);
        return s;
    }

  private:
    string getNext(const string &s)
    {
        stringstream ss;
        for (auto i = s.begin(); i != s.end();)
        {
            auto j = find_if(i, s.end(), bind1st(not_equal_to<char>(), *i));
            ss << distance(i, j) << *i;
            i = j;
        }
        return ss.str();
    }
};

int main()
{
    int n = 5;
    Solution2 s1;
    string result = s1.countAndSay(n);
    cout << result << endl;
    return 0;
}