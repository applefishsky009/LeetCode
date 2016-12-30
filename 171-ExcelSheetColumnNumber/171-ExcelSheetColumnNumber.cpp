#include <string>
#include <iostream>
using namespace std;

class Solution
{
  public:
    int titleToNumber(string s)
    {
        long number = 0;
        long factor;
        int i, n;
        for (i = s.size() - 1, n = 0, factor = 1; i >= 0; i--, n++, factor = factor * 26)
            number += (s[i] - '@') * factor;
        return number;
    }
};

int main()
{
    Solution s1;
    string s = "AB";
    cout << s1.titleToNumber(s) << endl;
    return 0;
}