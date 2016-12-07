#include <string>
#include <cctype>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int lengthOfLastWord(string s)
    {
        auto first = find_if(s.rbegin(), s.rend(), ::isalpha);
        auto last = find_if_not(first, s.rend(), ::isalpha);
        return distance(first, last);
    }
};

class Solution1
{
  public:
    int lengthOfLastWord(string s)
    {
        assert(!s.empty());
        int first = -1;
        int last = 0;
        bool isWord = false;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (!isWord && isalpha(s[i]))
            {
                last = i;
                isWord = true;
            }
            else if (isWord && !isalpha(s[i]))
            {
                first = i;
                break;
            }
        }
        if (!isWord)
            return 0;
        return last - first;
    }
};

class Solution2
{
  public:
    int lengthOfLastWord(const string &s)
    {
        return lengthOfLastWord(s.c_str());
    }

  private:
    int lengthOfLastWord(const char *s)
    {
        int len = 0;
        while (*s)
        {
            if (*s++ != ' ')
                ++len;
            else if (*s && *s != ' ')
                len = 0;
        }
        return len;
    }
};

int main()
{
    string s = "Hello W orld";
    Solution2 s1;
    cout << s1.lengthOfLastWord(s) << endl;
    return 0;
}