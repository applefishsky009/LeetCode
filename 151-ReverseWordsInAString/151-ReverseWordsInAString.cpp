#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

//in place why not?
class Solution
{
  public:
    void reverseWords(string &s)
    {
        // assert(!s.empty());
        if (s.empty())
            return;
        reverse(s.begin(), s.end());
        int cur = 0;
        for (int pre = 0; pre < s.size(); pre++)
        {
            int start = cur;
            while (pre < s.size() && s[pre] == ' ')
                pre++;
            int adv = pre;
            if (pre == s.size()) //strip,prevent the last possible loop
                break;
            while (adv < s.size() && s[adv] != ' ')
                s[cur++] = s[adv++];
            reverse(s.begin() + start, s.begin() + cur);
            s[cur++] = ' ';
            pre = adv;
        }
        cur == 0 ? s.resize(0) : s.resize(cur - 1); //no word?
    }
};

class Solution1
{
  public:
    void reverseWords(string &s)
    {
        string rs;
        for (int i = s.length() - 1; i >= 0;)
        {
            while (i >= 0 && s[i] == ' ')
                i--;
            if (i < 0)
                break;
            if (!rs.empty()) //remove the first space
                rs.push_back(' ');
            string t;
            while (i >= 0 && s[i] != ' ')
                t.push_back(s[i--]);
            reverse(t.begin(), t.end());
            rs.append(t);
        }
        s = rs;
    }
};

int main()
{
    Solution1 s1;
    // string s = "a   ";
    string s = "   the sky is   blue   ";
    // string s = "blue";
    // string s = "    ";
    s1.reverseWords(s);
    cout << s << '*' << endl;
    return 0;
}