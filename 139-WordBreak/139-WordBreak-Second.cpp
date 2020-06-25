#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;

// DFS超时-使用unordered_set也会超时
class Solution1 {
  public:
    bool wordBreak(string s, vector<string> &wordDict) {
        return dfs(s, 0, wordDict);
    }
  private:
    bool dfs(const string &s, int pos, const vector<string> &wordDict) {
        if (pos == s.size()) return true;
        for (int i = 0; i < wordDict.size(); i++) {
            if (!isSame(s, pos, wordDict[i])) continue;
            bool now = dfs(s, pos + wordDict[i].size(), wordDict);
            if (!now) continue;
            return true;
        }
        return false;
    }
    bool isSame(const string &s, int pos, const string &word) {
        int len = word.size();
        for (int i = 0; i < len; i++)
            if (word[i] != s[pos++])
                return false;
        return true;
    }
};

// 与n相关的DP,f(i)表示可分词,f(i) = any(f(j) && s[j + 1, i]) ∈ wordDict i > j
class Solution2 {
  public:
    bool wordBreak(string s, vector<string> &wordDict) {
        vector<int> f(s.size() + 1, 0);
        f[0] = 1;
        for (int i = 1; i < f.size(); i++)
            for (int j = 0; j < i; j++)
                if (f[j] && isInDict(s, j, i - 1, wordDict))  // 带初始状态DP,f(j+1,i)->s(j,i - 1)
                    f[i] = 1;
        return f[f.size() - 1];
    }
  private:
    bool isInDict(const string &s, int start, int end, const vector<string> &wordDict) {
        for (int i = 0; i < wordDict.size(); i++)
            if (isSame(s, start, end, wordDict[i]))
                return true;
        return false;
    }    
    bool isSame(const string &s, int start, int end, const string &word) {
        if (end - start + 1 != word.size()) return false;   // 长度不对,直接返回false
        int j = 0;
        for (int i = start; i <= end; i++)
            if (s[i] != word[j++])
                return false;
        return true;
    }
};

// 与n相关的DP,f(i)表示可分词,f(i) = any(f(j) && s[j + 1, i]) ∈ wordDict i > j, 改变遍历顺序,贪心遍历,优先短字符串
class Solution3 {
  public:
    bool wordBreak(string s, vector<string> &wordDict) {
        vector<int> f(s.size() + 1, 0);
        f[0] = 1;
        for (int i = 1; i < f.size(); i++)
            for (int j = i - 1; j >= 0; j--)
                if (f[j] && isInDict(s, j, i - 1, wordDict))  // 带初始状态DP,f(j+1,i)->s(j,i - 1)
                    f[i] = 1;
        return f[f.size() - 1];
    }
  private:
    bool isInDict(const string &s, int start, int end, const vector<string> &wordDict) {
        for (int i = 0; i < wordDict.size(); i++)
            if (isSame(s, start, end, wordDict[i]))
                return true;
        return false;
    }    
    bool isSame(const string &s, int start, int end, const string &word) {
        if (end - start + 1 != word.size()) return false;   // 长度不对,直接返回false
        int j = 0;
        for (int i = start; i <= end; i++)
            if (s[i] != word[j++])
                return false;
        return true;
    }
};

// 与n相关的DP,f(i)表示可分词,f(i) = any(f(j) && s[j + 1, i]) ∈ wordDict i > j, 改变遍历顺序,贪心遍历,优先短字符串
// unordered_set优化
class Solution {
  public:
    bool wordBreak(string s, vector<string> &wordDict) {
        vector<int> f(s.size() + 1, false);
        f[0] = true;
        unordered_set<string> wordSet;
        for (auto &x : wordDict)
            wordSet.insert(x);
        for (int i = 1; i < f.size(); i++)
            for (int j = i - 1; j >= 0; j--)
                if (f[j] && wordSet.count(s.substr(j, i - j)))  // 带初始状态DP,f(j+1,i)->s(j,i - 1)
                    f[i] = true;
        return f[s.size()];
    }
};

int main() {
    Solution s;
    string str0 = "leetcode";
    string str1 = "applepenapple";
    string str2 = "catsandog";
    string str3 = "cars";
    vector<string> wordDict0 = {"leet", "code"};
    vector<string> wordDict1 = {"apple", "pen"};
    vector<string> wordDict2 = {"cats", "dog", "sand", "and", "cat"};
    vector<string> wordDict3 = {"car", "ca", "rs"};
    cout << s.wordBreak(str0, wordDict0) << endl;
    cout << s.wordBreak(str1, wordDict1) << endl;
    cout << s.wordBreak(str2, wordDict2) << endl;
    cout << s.wordBreak(str3, wordDict3) << endl;
    return 1;
}