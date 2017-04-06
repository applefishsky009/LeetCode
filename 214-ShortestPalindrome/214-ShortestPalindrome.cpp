#include <string>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//O(n^2) Solution, it is easy.
class Solution
{
  public:
    string shortestPalindrome(string s)
    {
        const int n = s.size();
        string sReverse(s);
        reverse(sReverse.begin(), sReverse.end());
        int i = n - 1, j = 0;
        for (; i > 0; i--, j++)
            if (s.substr(0, i) == sReverse.substr(j, i))
                break;
        sReverse += s.substr(i + 1);
        return sReverse;
    }
};

//由O(n^2)引出的前后缀匹配问题，即可用KMP来解决
class Solution1
{
  public:
    string shortestPalindrome(string s)
    {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        string l = s + "#" + rev_s;

        vector<int> next(l.size(), 0);
        for (int i = 1; i < l.size(); i++)
        {
            int j = next[i - 1];           // 前一状态，同时这个值也是相同的真前缀长度
            while (j > 0 && l[i] != l[j])  //失配
                j = next[j - 1];           //回溯，因为next[j]记录了匹配位置
            next[i] = (j += l[i] == l[j]); //回溯后再判断是否匹配
        }
        show1DVector(next);        
        return rev_s.substr(0, s.size() - next[l.size() - 1]) + s; //将转置串截掉已回文部分接在原串前
    }
};

//使用改进的KMP
class Solution2
{
  public:
    string shortestPalindrome(string s)
    {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        string l = s + "#" + rev_s + "$";
        cout << l << endl;

        vector<int> nextVal(l.size(), 0);
        int j = -1, i = 0;
        nextVal[0] = -1;
        while (i < l.size() - 1)
        {
            if (j == -1 || l[i] == l[j])
            {
                i++;
                j++;
                if (l[i] != l[j])
                    nextVal[i] = j;
                else
                    nextVal[i] = nextVal[j];
            }
            else
                j = nextVal[j];
        }
        show1DVector(nextVal);
        return rev_s.substr(0, s.size() - nextVal[l.size() - 1]) + s;
    }
};

int main()
{
    Solution2 s1;
    string s = "ba";
    cout << s1.shortestPalindrome(s) << endl;
    return 0;
}