#include <string>
#include <vector>
#include <iostream>
using namespace std;

//一个非常有意思的现象，string[string.size()] == '\0'而不会抛出异常。
//因此可以优化代码
class Solution
{
  public:
    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.empty())
            return "";
        for (int idx = 0; idx < strs[0].size(); ++idx) //纵向扫描
            for (int i = 1; i < strs.size(); ++i)
                if (strs[i][idx] != strs[0][idx])
                    return strs[0].substr(0, idx);
        return strs[0];
    }
};

int main()
{
    Solution s1;
    vector<string> strs{"abcffff", "abc", "abcdkk", "abcdeffg"};
    cout << s1.longestCommonPrefix(strs) << endl;
    return 0;
}