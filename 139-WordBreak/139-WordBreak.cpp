#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

//DFS，超时
class Solution
{
  public:
    bool wordBreak(string s, unordered_set<string> &wordDict)
    {
        return wordBreak(s, 0, wordDict);
    }

  private:
    bool wordBreak(string s, int start, unordered_set<string> &wordDict)
    {
        if (start == s.size())
            return true;
        for (int i = 1; i <= s.size(); ++i)
        {
            string temp = s.substr(start, i);
            if (wordDict.count(temp))
                if (wordBreak(s, start + i, wordDict))
                    return true;
        }
        return false;
    }
};

//DP,f(i)标识s[0，i]是否可以分词
//f(i) = any(f(j)&&s[j+1,i]∈wordDict)
class Solution1
{
  public:
    bool wordBreak(string s, unordered_set<string> &wordDict)
    {
        //长度为n的字符串n+1个隔板，第一个初始化。
        vector<bool> f(s.size() + 1, false);
        f[0] = true;
        for (int i = 1; i <= s.size(); ++i) //求f(i)
            for (int j = 0; j < i; ++j) //遍历f(0)-f(i-1)
                //f(j)表示前边j个元素已经分好，substr()从string下标j开始，f（i）对应下标i-1，一共i-j个元素
                if (f[j] && wordDict.count(s.substr(j, i - j)))
                {
                    f[i] = true;
                    break;
                }
        return f[s.size()];
    }
};

//别人的答案，遍历顺序变了速度提升明显，猜测：在这个顺序下尽可能先匹配长的字符串，
//比如"a",“aaaa”,可以匹配为4个”a“或者1个”aaaa“，显然后者效率高于前者
class Solution2
{
  public:
    bool wordBreak(string s, unordered_set<string> &dict)
    {
        vector<bool> f(s.size() + 1, false);
        f[0] = true;
        for (int i = 1; i <= s.size(); ++i)
            for (int j = i - 1; j >= 0; --j)
                if (f[j] && dict.find(s.substr(j, i - j)) != dict.end())
                {
                    f[i] = true;
                    break;
                }
        return f[s.size()];
    }
};

int main()
{
    Solution1 s1;
    string s("leetcode");
    unordered_set<string> wordDict{"leet", "code"};
    bool result = s1.wordBreak(s, wordDict);
    cout << result << endl;
    return 0;
}