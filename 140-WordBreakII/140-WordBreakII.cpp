#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <E:\RylModule\vector.h>
using namespace std;

//DP，参考wordBreak的思路,注意n+1个隔板
class Solution
{
  public:
    vector<string> wordBreak(string s, unordered_set<string> &wordDict)
    {
        vector<bool> f(s.size() + 1, false);
        f[0] = true;                                                            //n+1个隔板
        vector<vector<bool>> prev(s.size() + 1, vector<bool>(s.size(), false)); //记录路径
        for (int i = 1; i <= s.size(); ++i)
            for (int j = i - 1; j >= 0; --j)
                if (f[j] && wordDict.count(s.substr(j, i - j)))
                {
                    f[i] = true;
                    prev[i][j] = true;
                }
        vector<string> result;
        vector<string> path;
        dfsPath(s, prev, result, path, s.size());
        return result;
    }

  private:
    void dfsPath(const string s, const vector<vector<bool>> &prev, vector<string> &result, vector<string> path, int step)
    {
        if (step == 0)
        {
            string tmp;
            for (auto p = path.rbegin(); p != path.rend(); ++p)
                tmp += *p + " ";
            tmp.pop_back();
            result.push_back(tmp);
            return;
        }
        for (int j = 0; j < s.size(); ++j)
            if (prev[step][j])
            {
                path.push_back(s.substr(j, step - j));
                dfsPath(s, prev, result, path, j);
                path.pop_back();
            }
    }
};

int main()
{
    Solution s1;
    string s("catsanddog");
    unordered_set<string> wordDict{"cat", "cats", "and", "sand", "dog"};
    vector<string> result = s1.wordBreak(s, wordDict);
    cout << result.size() << endl;
    show1DVector(result);
    return 0;
}